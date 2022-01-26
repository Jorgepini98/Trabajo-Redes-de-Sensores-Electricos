#include "reconocimiento.h"

int reconocimiento(int actAnterior,int meanX_1,int meanX_2,int meanY,int L,int ener,int thres_En1,int thres_En2,int nPicos,int thres_nPicos){
  
  int meanX = (meanX_1 + meanX_2)/2;

  int actividad = 0;

  if (ener < thres_En1){

        if (meanY > -8500 && meanX < -8500)
        {
          actividad = 1;
          Serial.println("tumbado");
        }
        else if (meanY < -8500) 
        {
          if ((actAnterior == 2 && meanX_2 < -1000) || (meanX_1 > 0 && meanX_2 < -1000))
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
  else if(nPicos >= thres_nPicos)
  {
      if (ener > thres_En2)
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
