#include <CircularBuffer.h>;
#include "Accel.h";
#include "interrupt.h";
#include "OLED.h";
#include "reconocimiento.h";

extern int totalInterruptCounter;
extern MPU9250_asukiaaa mySensor;

sensorData dataSensor;

CircularBuffer<int,200> HighPass_AcelX;
CircularBuffer<int,200> LowPass_AcelX;

CircularBuffer<int,200> HighPass_AcelY;
CircularBuffer<int,200> LowPass_AcelY;

CircularBuffer<int,200> HighPass_AcelZ;
CircularBuffer<int,200> LowPass_AcelZ;

CircularBuffer<int,200> HighPass_Total;

using index_t = decltype(HighPass_AcelX)::index_t;

int arraySize = 200;

int energia_aY = 0;

int energia = 0;

int numeroPicos = 0;

int tiempoActualPico = 0;
int tiempoAnteriorPico = 0;

int tiempoEntrePicos = 0;

int mediaTiempos = 0;

int desTyp = 0;

int var = 0;

int total = 0;

int aX_1 = 0;
int aY_1 = 0;
int aZ_1 = 0;

int aX_2 = 0;
int aY_2 = 0;
int aZ_2 = 0;

int meanX = 0;
int meanY = 0;

int meanX_1 = 0;
int meanX_2 = 0;

int saveCounter = 0;

int picoActual = 0;
int picoAnterior = 0;
int tiempoMax = 0;

int tiempos[] = {0};

int thresholdPico = 3000;

int thresholdTiempoZancada = 200;

int Actividad = 0;


//filtrado

double ALPHA = 0.6;

void setup() {

  Serial.begin(115200);


// 1 digito -> acelerometro
// 2 digito -> magnetómetro
// 3 digito -> giroscopio
  sensorSetup(1,1,1);

  OLEDsetup();

  int frecuency = 50;

  timerInterruptSetup(frecuency);

  Serial.println("Setup");

//antes de empezar el bucle lleno el array de datos

  while(!LowPass_AcelX.isFull()){

   // Serial.println(1);

    if(timerInterruptOn()){ //(saveCounter > totalInterruptCounter)

     // Serial.println(2);
    dataSensor = readAcel();
    
    aX_2 = aX_1;
    aY_2 = aY_1;
    aZ_2 = aZ_1;

    aX_1 = dataSensor.aX;
    aY_1 = dataSensor.aY;
    aZ_1 = dataSensor.aZ;

    if(totalInterruptCounter > 1){
      
    LowPass_AcelX.push(LowPass(aX_1,aX_2, ALPHA));
    HighPass_AcelX.push(HighPass(aX_1,LowPass_AcelX[200]));

    LowPass_AcelY.push(LowPass(aY_1,aY_2, ALPHA));
    HighPass_AcelY.push(HighPass(aY_1,LowPass_AcelY[200]));

    LowPass_AcelZ.push(LowPass(aZ_1,aZ_2, ALPHA));
    HighPass_AcelZ.push(HighPass(aZ_1,LowPass_AcelZ[200]));

    }
    
    }
    
  }

  
  
}

void loop() {

   

  if(timerInterruptOn()){
    
    dataSensor = readAcel();

    aX_2 = aX_1;
    aY_2 = aY_1;
    aZ_2 = aZ_1;

    aX_1 = dataSensor.aX;
    aY_1 = dataSensor.aY;
    aZ_1 = dataSensor.aZ;

    LowPass_AcelX.push(LowPass(aX_1,aX_2, ALPHA));
    HighPass_AcelX.push(HighPass(aX_1,LowPass_AcelX[200]));

    LowPass_AcelY.push(LowPass(aY_1,aY_2, ALPHA));
    HighPass_AcelY.push(HighPass(aY_1,LowPass_AcelY[200]));

    LowPass_AcelZ.push(LowPass(aZ_1,aZ_2, ALPHA));
    HighPass_AcelZ.push(HighPass(aZ_1,LowPass_AcelZ[200]));

    total = abs(HighPass_AcelX[200]) + abs(HighPass_AcelY[200]) + abs(HighPass_AcelZ[200]);


    //Serial.println(total);
    
    if (total < 3000)
    {
      HighPass_Total.push(0);
    }
    else
    {
      HighPass_Total.push(total);
    }

    //Serial.println(HighPass_AcelY[200]); 
    

    if(totalInterruptCounter%50 == 1){

        for(index_t i = 0; i < HighPass_Total.size(); i++) {

          energia = energia + HighPass_Total[i];

          meanY = meanY + LowPass_AcelY[i];

          if (i < 100)
          {
            meanX_1 = meanX_1 + LowPass_AcelX[i];
          }
          else
          {
            meanX_2 = meanX_2 + LowPass_AcelX[i];
          }

            if(HighPass_Total[i] > thresholdPico){

              picoActual = 1;
            
              tiempoActualPico = millis();

              tiempoEntrePicos = tiempoActualPico - tiempoAnteriorPico;

              if (tiempoMax < tiempoEntrePicos)
              {
              tiempoMax = tiempoEntrePicos;
              }

              if (picoActual == 1 && picoAnterior == 0 && tiempoEntrePicos > thresholdTiempoZancada)
              {
              mediaTiempos += tiempoEntrePicos;

              tiempos[numeroPicos] = tiempoEntrePicos;

              numeroPicos += numeroPicos;

              tiempoAnteriorPico = millis();
              }
              
            }
            
            picoAnterior = picoActual;           
            picoActual = 0;
            
        }
        

        meanX_1 = meanX_1/(arraySize/2);
        meanX_2 = meanX_2/(arraySize/2);

        meanY = meanY/arraySize;

        

        Actividad = reconocimiento(Actividad,meanX_1,meanX_2,meanY,arraySize,energia,1000,100000,numeroPicos,2);

//        Serial.print("MediaY: ");
//        Serial.println(meanY);
//
//        Serial.print("MediaX: ");
//        Serial.println(meanX_1);
//        
//        Serial.print("energia: ");
//        Serial.println(energia);
//
//        Serial.print("Npicos: ");
//        Serial.println(numeroPicos);
//        
//        Serial.print("Actividad: ");
//        Serial.println(Actividad);
//        Serial.println("");
        
        //Serial.println(10);

//        mediaTiempos = mediaTiempos/numeroPicos;
//        
//        //verificar que los tiempos entre picos es aprox similar
//
//        for(i = 0; i < numeroPicos; i++){
//
//          var = (tiempoEntrePicos[i] - mediaTiempos);
//          
//        }
//
//        desTyp = sqrt(var / numeroPicos);


        //funcióon reconocimiento actividad

        //inicializar a cero las variables

        energia = 0;

        numeroPicos = 0;
    
        tiempoActualPico = 0;
        
        tiempoAnteriorPico = 0;
        
        tiempoEntrePicos = 0;
        
        mediaTiempos = 0;
        
        //tiempos[] = {0};
        
    }
  }
}
 

int LowPass(int valorActual,int valorAnterior, int alpha){
  return ((ALPHA * valorActual) + (1 - ALPHA) * valorAnterior);
}

int HighPass(int valorActual,int lowPass){
  return (valorActual - lowPass);
}

int HighPass1(int valorActual,int valorAnterior, int alpha){
  return (valorActual - LowPass(valorActual,valorAnterior,alpha));
}

int ZeroIfLessThan(int threshold,int valor){ 
  if (abs(valor) <= threshold){
         valor = 0;
     } 
     return valor;
}
