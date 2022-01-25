#ifndef filtrado_H
#define filtrado_H

#include <Arduino.h>

int LowPass(int valorActual,int valorAnterior, int alpha);

int HighPass(int valorActual,int lowPass);

int HighPass1(int valorActual,int valorAnterior, int alpha);

int ZeroIfLessThan(int threshold,int valor);


#endif
