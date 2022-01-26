#ifndef OLED_H
#define OLED_H

//#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

#define clear() fillScreen(0)

void displayUp(String info);
void OLEDsetup();
void printStatusOLED(int Status);

#endif
