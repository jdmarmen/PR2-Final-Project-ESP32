#include "HTTP.hpp"

void HTTP::post(std::string message) {
  HTTPClient http_client;
  http_client.begin(HTTP_SERVER_URL);
  http_client.addHeader("Content-Type", "application/json");

  int http_response_code = http_client.POST(message.c_str());
  if (http_response_code > 0) {
    String response = http_client.getString();
    JsonDocument doc = ESP::get_json_data(response);

    bool error = doc["error"];
    std::string ubi = doc["posicion"];

    if (error == false) {
        Serial.print("Posicion: ");
        Serial.println(ubi.c_str());
    }
  } else {
    Serial.print("Error en POST: ");
    Serial.println(http_response_code);
  }

  http_client.end();
}