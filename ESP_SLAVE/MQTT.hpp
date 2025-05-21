#pragma once
#include <string>
#include <PubSubClient.h>
#include <WiFi.h>
#include "Config.hpp"

class MQTT
{
public:
    static WiFiClient wifi_client;
    static PubSubClient mqtt_client;
    static void init();
    static void reconnect();
    static void publish(std::string topic, std::string message);
    static void loop();
};