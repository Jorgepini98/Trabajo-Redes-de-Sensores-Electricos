#ifndef reconocimiento_H
#define reconocimiento_H

#include <Arduino.h>

int reconocimiento(int actAnterior,int meanX_1,int meanX_2,int meanY,int L,int ener,int thres_En1,int thres_En2,int nPicos,int thres_nPicos);

int media (int vector[], int inicio, int final); 

int longitud(int vector[]);



#endif
