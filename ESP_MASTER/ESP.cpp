#include "ESP.hpp"

bool ESP::button_pressed = false;

void ESP::init() {
  Serial.begin(BAUD);

  for (const auto& [pin, mode] : pin_map) {
    pinMode(pin, mode);
  }

  attachInterrupt(EMERGENCY_BUTTON, button_callback, FALLING);

  WIFI::init();
  MQTT::init();
  MQTT::subscribe(QR_TOPIC);
  MQTT::subscribe(LED_STATUS_TOPIC);
  MQTT::subscribe(SLAVE_TOPIC);

  xTaskCreate(mqtt_periodic_task, "mqtt_periodic_task", 4096, NULL, 1, NULL);
  xTaskCreate(button_periodic_task, "button_periodic_task", 4096, NULL, 1, NULL);
}

void ESP::mqtt_periodic_task(void* args) {
  for (;;) {
    MQTT::loop();
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void ESP::button_periodic_task(void* args) {
  for (;;) {
    if (button_pressed)
      button_order();
    
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void ESP::add_key_value_pairs(JsonDocument& doc) {  // does nothing when the recursion ends
}

JsonDocument ESP::get_json_data(String message) {
  JsonDocument doc;
  deserializeJson(doc, message);
  return doc;
}

void ESP::button_callback() {
  button_pressed = true;
}

void ESP::button_order() {
  button_pressed = false;
  std::string msg_json = create_json("button", "pressed");
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);

  MQTT::publish(BUTTON_STATUS_TOPIC, msg_json);
}