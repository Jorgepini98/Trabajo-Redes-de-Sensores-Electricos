#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <esp32-hal-timer.h>

void timerInterruptSetup(int frecuency);

bool timerInterruptOn();

#endif 
