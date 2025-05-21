#include "MQTT.hpp"

WiFiClient MQTT::wifi_client;
PubSubClient MQTT::mqtt_client(wifi_client);


void MQTT::init()
{
    mqtt_client.setServer(MQTT_SERVER, MQTT_PORT);
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

void MQTT::publish(std::string topic, std::string message)
{
    mqtt_client.publish(topic.c_str(), message.c_str());
}

void MQTT::loop()
{
    reconnect();
    mqtt_client.loop();
}
