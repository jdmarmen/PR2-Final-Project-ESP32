#include "MQTT.hpp"

WiFiClient MQTT::wifi_client;
PubSubClient MQTT::mqtt_client(wifi_client);
QueueHandle_t MQTT::queue = xQueueCreate(10, sizeof(MQTT::message));

void MQTT::init()
{
    mqtt_client.setServer(MQTT_SERVER, MQTT_PORT);
    mqtt_client.setCallback(mqtt_callback);
    MQTT::reconnect();
}

void MQTT::reconnect()
{
    while (!mqtt_client.connected())
    {
        Serial.print("Connecting to MQTT...");
        if (mqtt_client.connect(MQTT_CLIENT_ID))
        {
            Serial.println("Connected to MQTT!");
        }
        else
        {
            Serial.print("Error, rc=");
            Serial.print(mqtt_client.state());
            delay(2000);
        }
    }
}

void MQTT::subscribe(std::string topic)
{
    mqtt_client.subscribe(topic.c_str());
    Serial.print("Subscribed to topic: ");
    Serial.println(topic.c_str());
}

void MQTT::publish(std::string topic, std::string message)
{
    mqtt_client.publish(topic.c_str(), message.c_str());
}

void MQTT::mqtt_callback(char *topic, byte *payload, unsigned int length)
{
    Serial.println("Message arrived");

    message msg;

    strncpy(msg.topic, topic, sizeof(msg.topic) - 1);
    strncpy(msg.payload, (char*)payload, sizeof(msg.payload) - 1);
    msg.payload[length] = '\0';

    xQueueSend(MQTT::queue, &msg, 0);
}

void MQTT::check_queue()
{
    message msg;
    if (xQueueReceive(MQTT::queue, &msg, 0))
    {
        if (strcmp(msg.topic, SLAVE_TOPIC) == 0)
        {
            digitalWrite(GREEN_LED, LOW);
            digitalWrite(YELLOW_LED, HIGH);
            // HTTP::post(msg.payload);
            MQTT::publish(QR_TOPIC, msg.payload);
        }
        else if (strcmp(msg.topic, LED_STATUS_TOPIC) == 0)
        {
            digitalWrite(YELLOW_LED, LOW);
            digitalWrite(GREEN_LED, HIGH);
        }
    }
}

void MQTT::loop()
{
    reconnect();
    mqtt_client.loop();
    check_queue();
}
