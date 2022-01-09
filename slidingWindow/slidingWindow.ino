#include <CircularBuffer.h>;
#include "Accel.h";
#include "interrupt.h";
#include "OLED.h";

extern int totalInterruptCounter;
extern MPU9250_asukiaaa mySensor;

sensorData dataSensor;

CircularBuffer<int,200> HighPass_Acel;

CircularBuffer<int,200> aY;

using index_aY = decltype(HighPass_Acel)::index_t;



int arraySize = 200;




//int aX[100] = {0};
//int aY[100] = {0};
//int aZ[100] = {0};

//int gX[100] = {0};
//int gY[100] = {0};
//int gZ[100] = {0};

int saveCounter = 0;

//filtrado

double ALPHA = 0.6; //0-10

//int HighPass_Acel[100] = {0};
//
//int LowPass_Gyro[100] = {0};

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

  while(totalInterruptCounter <= arraySize){

   // Serial.println(1);

    if(timerInterruptOn()){ //(saveCounter > totalInterruptCounter)

     // Serial.println(2);
    dataSensor = readAcel();
    
    aY.push(dataSensor.aY);
    
    

//FILTER

    if(totalInterruptCounter > 1){
      
    HighPass_Acel.push(HighPass(aY[totalInterruptCounter - 1],aY[totalInterruptCounter - 2], ALPHA));

    }
    }
    
  }
  
}

void loop() {
   

  if(timerInterruptOn()){
    
    dataSensor = readAcel();

    aY.push(dataSensor.aY);

    HighPass_Acel.push(ZeroIfLessThan(1000,HighPass(aY[199],aY[198], ALPHA)));

   //LowPass_Gyro[arraySize - 1] = LowPass(gY[arraySize - 1],gY[arraySize - 2], ALPHA);



    Serial.println(HighPass_Acel[200]); 

    //Serial.println(ZeroIfLessThan(1500,HighPass(aY[200],aY[199], ALPHA)));
    
    //if(totalInterruptCounter % 10){}

    //Serial.println(aY[200]); 

  }
}
 

int LowPass(int valorActual,int valorAnterior, int alpha){
  return ((ALPHA * valorActual) + (1 - ALPHA) * valorAnterior);
}

int HighPass(int valorActual,int valorAnterior, int alpha){
  return (valorActual - LowPass(valorActual,valorAnterior,alpha));
}

int ZeroIfLessThan(int threshold,int valor){ 
  if (abs(valor) <= threshold){
         valor = 0;
     } 
     return valor;
}
