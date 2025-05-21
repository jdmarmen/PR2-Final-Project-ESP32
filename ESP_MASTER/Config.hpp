#pragma once
#include <unordered_map>
#include <Arduino.h>

//----------------WIFI----------------
#define WIFI_SSID  ""
#define WIFI_PASSWORD  ""

//----------------MQTT----------------
#define MQTT_CLIENT_ID "ESP32_S3_PR2_A1_MASTER"
#define MQTT_SERVER ""
#define MQTT_PORT 0

//topics
#define SLAVE_TOPIC         "PR2A1/avisos/slave"
#define BUTTON_STATUS_TOPIC "PR2A1/avisos/parada_emergencia"
#define QR_TOPIC            "PR2A1/avisos/QR"
#define LED_STATUS_TOPIC    "PR2A1/avisos/LED"

//----------------HTTP----------------
#define HTTP_SERVER_URL ""

//----------------BAUD----------------
#define BAUD 115200

//----------------PINOUT----------------
#define EMERGENCY_BUTTON 4
#define YELLOW_LED 6
#define GREEN_LED 15
#define RED_LED 17

inline std::unordered_map<uint8_t, uint8_t> pin_map = {
    {EMERGENCY_BUTTON, INPUT_PULLUP},
    {YELLOW_LED, OUTPUT},
    {GREEN_LED, OUTPUT},
    {RED_LED, OUTPUT}
};
