#include <Arduino.h>

#ifndef STASSID
// #define STASSID "Private"
// #define STAPSK "Rumahmiruk_37"
#define STASSID "@Wifi.com"
#define STAPSK "Hostpot_ahul7"
#endif

#ifndef WEBSERVER_H
#define WEBSERVER_H
#define EEPROM_SIZE 125
#define pinRelay_1 2
#define pinRelay_2 4
#define pinRelay_3 33
#define pinSensor_1 25
#define pinSensor_2 26
#define pinSensor_3 27
#define PARAM_INPUT_1 "output"
#define PARAM_INPUT_2 "state"

extern bool stateManualSwitch_1, stateManualSwitch_2, stateManualSwitch_3;
extern AsyncWebServer server;
extern void webServerMain(void);

#endif