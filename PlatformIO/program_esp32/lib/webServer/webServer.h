#include <Arduino.h>

#ifndef STASSID
#define STASSID "Private"
#define STAPSK "Rumahmiruk_37"
#endif

#ifndef WEBSERVER_H
#define WEBSERVER_H
#define EEPROM_SIZE 125
#define pinRelay_1 2
#define pinRelay_2 4
#define pinRelay_3 33
#define PARAM_INPUT_1 "output"
#define PARAM_INPUT_2 "state"

extern AsyncWebServer server;
extern void webServerMain(void);

#endif