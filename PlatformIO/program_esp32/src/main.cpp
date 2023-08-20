#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>
#include <WiFi.h>
#include "webServer.h"

// connecting to wifi
#ifndef STASSID
#define STASSID "Private"
#define STAPSK "Rumahmiruk_37"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
int ledState_1 = LOW;
int ledState_2 = LOW;
int ledState_3 = LOW;

AsyncWebServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);

  ledState_1 = EEPROM.read(pinRelay_1);
  ledState_2 = EEPROM.read(pinRelay_2);
  ledState_3 = EEPROM.read(pinRelay_3);

  Serial.println(F("\nState EEPROM"));
  Serial.print(F("EEPROM 1 : ")); Serial.println(ledState_1);
  Serial.print(F("EEPROM 2 : ")); Serial.println(ledState_2);
  Serial.print(F("EEPROM 3 : ")); Serial.println(ledState_3);

  pinMode(pinRelay_1, OUTPUT);
  pinMode(pinRelay_2, OUTPUT);
  pinMode(pinRelay_3, OUTPUT);
  digitalWrite(pinRelay_1, ledState_1);
  digitalWrite(pinRelay_2, ledState_2);
  digitalWrite(pinRelay_3, ledState_3);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(F("."));
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());
  webServerMain();
  // start server
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  // TODO
}