#pragma once
#include <string>
#include <PubSubClient.h>
#include <WiFi.h>
#include "Config.hpp"
#include "HTTP.hpp"

class MQTT
{
public:

    typedef struct
    {
        char topic[64];
        char payload [128];
    } message;

    static QueueHandle_t queue;

    static WiFiClient wifi_client;
    static PubSubClient mqtt_client;

    static void init();
    static void reconnect();
    static void subscribe(std::string topic);

    static void publish(std::string topic, std::string message);
    static void mqtt_callback(char *topic, byte *payload, unsigned int length);
    static void check_queue();
    
    static void loop();

};