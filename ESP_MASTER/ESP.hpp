#pragma once
#include <ArduinoJson.h>
#include "Config.hpp"
#include "WIFI.hpp"
#include "MQTT.hpp"
#include "HTTP.hpp"

class ESP
{   
    static void add_key_value_pairs(JsonDocument &doc);

    template <typename t_key, typename t_value, typename... t_rest>
    static void add_key_value_pairs(JsonDocument &doc, t_key key, t_value value, t_rest... rest);

    static bool button_pressed;
    
public:
    static void init();
    static void update_button();

    template <typename... Args>
    static std::string create_json(Args... args);
    static JsonDocument get_json_data(String message); 

    static void button_callback();
    static void button_order();

    static void mqtt_periodic_task(void* args);
    static void button_periodic_task(void* args);
};

template <typename... Args>
std::string ESP::create_json(Args... args)
{
    JsonDocument doc;
    add_key_value_pairs(doc, args...);
    std::string msg_json;
    serializeJson(doc, msg_json);
    return msg_json;
}

template <typename t_key, typename t_value, typename... t_rest>
void ESP::add_key_value_pairs(JsonDocument &doc, t_key key, t_value value, t_rest... rest)
{
    doc[key] = value;
    add_key_value_pairs(doc, rest...);
}