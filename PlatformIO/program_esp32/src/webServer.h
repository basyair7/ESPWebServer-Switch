#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#ifndef WEBSERVER_H
#define WEBSERVER_H
#define EEPROM_SIZE 125
#define pinRelay_1 2
#define pinRelay_2 4
#define pinRelay_3 33
#define PARAM_INPUT_1 "output"
#define PARAM_INPUT_2 "state"

extern AsyncWebServer server;
extern int ledState_1;
extern int ledState_2;
extern int ledState_3;
extern void webServerMain(void);

#endif
