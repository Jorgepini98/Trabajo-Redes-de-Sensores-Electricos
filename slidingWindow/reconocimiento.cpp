#include "reconocimiento.h"

int reconocimiento(int actAnterior,int meanX_1,int meanX_2,int meanY,int L,int ener,int thres_En1,int thres_En2,int nPicos,int thres_nPicos){
  
  int meanX = (meanX_1 + meanX_2)/2;

  int actividad = 0;

  if (ener < thres_En1){//Actividad dinámica o estática

        if (meanY > -8500 && meanX < -8500) //si en el axis Y tenemos una aceleracion próxima a 10000(gravedad) se identificara como tumbado
        {
          actividad = 1;
          Serial.println("tumbado");
        }
        else if (meanY < -8500) //si estamos posicionados verticalmente
        {
          if ((actAnterior == 2 && meanX_2 < -1000) || (meanX_1 > 0 && meanX_2 < -1000)) //reconocimiento sentarse
          {
            Serial.println("sentado");
            actividad = 2;
          }
          else
          {
            Serial.println("pie");
            actividad = 3;
          }
        }
  }  
  else if(nPicos >= thres_nPicos) // si hay repetición
  {
      if (ener > thres_En2)// si supera el nivel de energia indicado
      {
      Serial.println("corriendo");
      actividad = 4;
      }
      else
      {
      Serial.println("andar");
      actividad = 5;
       }
  }
        
  return actividad;
}
