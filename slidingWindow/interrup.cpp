#include "interrupt.h"

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

volatile int interruptCounter;
int totalInterruptCounter;

 void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&timerMux);
}

void timerInterruptSetup(int f){
  //el cpunter del esp32 es de 80Mhz, de forma que se utiliza un preescaler de 80 consiguiendo un reloj de 10Mhz
  // el la frecuencia de la interrupción vendra definida por
  // f = 1000000/counter; por tanto counter = 1000000/f
  // timerAlarmWrite(timer, us, true);
  
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000/f, true);
  timerAlarmEnable(timer);
}

bool timerInterruptOn(){

  bool salida = false;
  
  if (interruptCounter > 0) {

    portENTER_CRITICAL(&timerMux);
    interruptCounter = 0;
    portEXIT_CRITICAL(&timerMux);
 
    totalInterruptCounter++;

    salida = true;
  }

  return salida;
}
