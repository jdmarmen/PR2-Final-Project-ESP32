#include "ESP.hpp"

void ESP::init()
{
    Serial.begin(BAUD);

    WIFI::init();
    MQTT::init();
}

void ESP::add_key_value_pairs(JsonDocument &doc)
{ // does nothing when the recursion ends
}

JsonDocument ESP::get_json_data(String message){
    JsonDocument doc;
    deserializeJson(doc,message);
    return doc;
}