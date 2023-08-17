#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebSrv.h>

#ifndef STASSID
#define STASSID "JTEK-2"
#define STAPSK "elektro2"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";

AsyncWebServer server(80);

#define EEPROM_SIZE 125
int pinRelay_1 = 2, pinRelay_2 = 4, pinRelay_3 = 33;
int ledState_1 = LOW, ledState_2 = LOW, ledState_3 = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);

  ledState_1 = EEPROM.read(pinRelay_1);
  ledState_2 = EEPROM.read(pinRelay_2);
  ledState_3 = EEPROM.read(pinRelay_3);

  Serial.println(F("\nState EEPROM"));
  Serial.print(F("EEPROM 1 : ")); Serial.println(EEPROM.read(pinRelay_1));
  Serial.print(F("EEPROM 2 : ")); Serial.println(EEPROM.read(pinRelay_2));
  Serial.print(F("EEPROM 3 : ")); Serial.println(EEPROM.read(pinRelay_3));

  pinMode(pinRelay_1, OUTPUT);
  pinMode(pinRelay_2, OUTPUT);
  pinMode(pinRelay_3, OUTPUT);
  digitalWrite(pinRelay_1, ledState_1);
  digitalWrite(pinRelay_2, ledState_2);
  digitalWrite(pinRelay_3, ledState_3);

  WiFi.begin(ssid, password);
  Serial.println(F("Connecting to WiFi"));
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(F("."));
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());
  webServerMain();
  // Start server
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}
