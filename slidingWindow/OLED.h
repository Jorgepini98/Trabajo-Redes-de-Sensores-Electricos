#ifndef OLED_H
#define OLED_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>


void displayUp(String info);
void OLEDsetup();
void printStatus(int Status);

#endif
