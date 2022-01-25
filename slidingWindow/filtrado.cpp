#include "filtrado.h";


 //funciones de filtrado

//filtro paso bajo
int LowPass(int valorActual,int valorAnterior, int alpha){
  return ((alpha * valorActual) + (1 - alpha) * valorAnterior);
}

//filtro paso alto
int HighPass(int valorActual,int lowPassValue){
  return (valorActual - lowPassValue);
}

//funciónb de filtro paso alto donde se implementa ya dentro de la misma el paso bajo
int HighPass1(int valorActual,int valorAnterior, int alpha){
  return (valorActual - LowPass(valorActual,valorAnterior,alpha));
}

//filtro con threshold
int ZeroIfLessThan(int threshold,int valor){ 
  if (abs(valor) < threshold){
         valor = 0;
     } 
     return valor;
}
