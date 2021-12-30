#ifndef NTP_H
#define NTP_H


// Import required libraries
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>


String getLocalTime();
void NTP_Setup();


#endif
