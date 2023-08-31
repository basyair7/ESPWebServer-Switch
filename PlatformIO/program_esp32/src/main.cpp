#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>
#include <webServer.h>

AsyncWebServer server(80);
int ledState_1 = LOW, ledState_2 = LOW, ledState_3 = LOW;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    EEPROM.begin(EEPROM_SIZE);

    ledState_1 = EEPROM.read(pinRelay_1);
    ledState_2 = EEPROM.read(pinRelay_2);
    ledState_3 = EEPROM.read(pinRelay_3);

    Serial.println(F("\nState EEPROM"));
    Serial.print(F("EEPROM 1 : "));
    Serial.println(ledState_1);
    Serial.print(F("EEPROM 2 : "));
    Serial.println(ledState_2);
    Serial.print(F("EEPROM 3 : "));
    Serial.println(ledState_3);

    // pin sensor
    pinMode(pinSensor_1, INPUT);
    pinMode(pinSensor_2, INPUT);
    pinMode(pinSensor_3, INPUT);
    // pin relay
    pinMode(pinRelay_1, OUTPUT);
    pinMode(pinRelay_2, OUTPUT);
    pinMode(pinRelay_3, OUTPUT);
    digitalWrite(pinRelay_1, ledState_1);
    digitalWrite(pinRelay_2, ledState_2);
    digitalWrite(pinRelay_3, ledState_3);

    // connecting to wifi
    WiFi.begin(STASSID, STAPSK);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(F("."));
    }

    // Print ESP Local IP Address
    Serial.println(WiFi.localIP());
    webServerMain();
    // start server
    server.begin();
}

void loop()
{
    // put your main code here, to run repeatedly:
    // TODO
}