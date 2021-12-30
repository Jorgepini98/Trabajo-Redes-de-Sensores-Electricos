#include "Accel.h";
#include "interrupt.h";
#include "OLED.h";

extern int totalInterruptCounter;
extern MPU9250_asukiaaa mySensor;

sensorData dataSensor;

int arraySize = 200;

int aX[200];
int aY[200];
int aZ[200];
 

void setup() {

  Serial.begin(115200);
  
  sensorSetup();

  OLEDsetup();

  int frecuency = 50;

  timerInterruptSetup(frecuency);
  
}

void loop() {

  if(timerInterruptOn()){
    dataSensor = readData();

  if(totalInterruptCounter < arraySize){
    aX[totalInterruptCounter] = dataSensor.aX;
    aY[totalInterruptCounter] = dataSensor.aY;
    aZ[totalInterruptCounter] = dataSensor.aZ;
    Serial.println(aX[totalInterruptCounter]);
  }
  else{

Serial.println("prueba1");

    desplazarArrays();

    aX[arraySize - 1] = dataSensor.aX;
    aY[arraySize - 1] = dataSensor.aY;
    aZ[arraySize - 1] = dataSensor.aZ;
    
    Serial.println(aX[199]); 
    
    
    
    }

  }
  }
 


void desplazarArrays(){

    for(int i = 0; i < 199; i++){
    
    aX[i] = aX[i + 1];
    aY[i] = aY[i + 1];
    aZ[i] = aZ[i + 1];
    
    }

}
