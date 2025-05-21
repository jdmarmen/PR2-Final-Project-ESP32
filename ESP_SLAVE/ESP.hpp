#pragma once
#include <ArduinoJson.h>
#include "Config.hpp"
#include "WIFI.hpp"
#include "MQTT.hpp"

class ESP
{   
    static void add_key_value_pairs(JsonDocument &doc);

    template <typename t_key, typename t_value, typename... t_rest>
    static void add_key_value_pairs(JsonDocument &doc, t_key key, t_value value, t_rest... rest);
    
public:
    static void init();

    template <typename... Args>
    static std::string create_json(Args... args);
    static JsonDocument get_json_data(String message); 

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