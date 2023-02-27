#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
//#include "env.h"

#define pinkLED 18
#define redLED 19
#define blueLED 21

char * endpoint = "https://ecse-three-led-api.onrender.com/api/state";
const char * WIFI_SSID = "Wokwi-anandabee01234@gmail.com";
const char * WIFI_PASS = "";

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
  pinMode(pinkLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    String http_response;

    http.begin(endpoint);
    http.addHeader("X-API-Key", "Birdie#3739");

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response Code: ");
      Serial.println(httpResponseCode);
      
      Serial.print("Response from server: ");
      http_response = http.getString();
      Serial.println(http_response);
      }
      
      else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }

    http.end();

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, http_response);
    
    if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    
    return;
    }

    const char* user = doc["user"];
    const char* id = doc["_id"];

    //LED Update
    bool LED_light_1 = doc["LED_light_1"];
    bool LED_light_2 = doc["LED_light_2"];
    bool LED_light_3 = doc["LED_light_3"];
    
    Serial.println("");

    Serial.print("Pink Light: ");
    Serial.println(LED_light_1);

    Serial.print("Red Light: ");
    Serial.println(LED_light_2);

    Serial.print("Blue Light: ");
    Serial.println(LED_light_3);
    Serial.println("");

    if (LED_light_1 == 1) {
      digitalWrite(pinkLED, HIGH);
    }
    else {
      digitalWrite(pinkLED, LOW);
    }

    if (LED_light_2 == 1) {
      digitalWrite(redLED, HIGH);
    }
    else {
      digitalWrite(redLED, LOW);
    }

    if (LED_light_3 == 1) {
      digitalWrite(blueLED, HIGH);
    }
    else {
      digitalWrite(blueLED, LOW);
    }

  }

  else {
    return;
  }
}