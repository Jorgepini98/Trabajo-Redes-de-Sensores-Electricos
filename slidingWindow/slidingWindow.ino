#include "Accel.h";
#include "interrupt.h";
#include "OLED.h";

extern int totalInterruptCounter;
extern MPU9250_asukiaaa mySensor;

sensorData dataSensor;

int arraySize = 100;

//int aX[100] = {0};
int aY[100] = {0};
//int aZ[100] = {0};

//int gX[100] = {0};
//int gY[100] = {0};
//int gZ[100] = {0};

int saveCounter = 0;

//filtrado

double ALPHA = 0.6; //0-10

int HighPass_Acel[100] = {0};

int LowPass_Gyro[100] = {0};

void setup() {

  Serial.begin(115200);


// 1 digito -> acelerometro
// 2 digito -> magnetómetro
// 3 digito -> giroscopio
  sensorSetup(1,0,0);

  OLEDsetup();

  int frecuency = 50;

  timerInterruptSetup(frecuency);

  while(totalInterruptCounter < arraySize - 1){

    if(timerInterruptOn()){ //(saveCounter > totalInterruptCounter)
    saveCounter = totalInterruptCounter;
    dataSensor = readAcel();
    //dataSensor = readGyro();

    //aX[totalInterruptCounter + 1] = dataSensor.aX;
    aY[totalInterruptCounter + 1] = dataSensor.aY;
    //aZ[totalInterruptCounter + 1] = dataSensor.aZ;

    //gX[totalInterruptCounter + 1] = dataSensor.gX;
    //gY[totalInterruptCounter + 1] = dataSensor.gY;
    //gZ[totalInterruptCounter + 1] = dataSensor.gZ;
    
    

//FILTER
    
    HighPass_Acel[totalInterruptCounter + 1] = HighPass(aY[totalInterruptCounter + 1],aY[totalInterruptCounter], ALPHA);

    //LowPass_Gyro[totalInterruptCounter + 1] = LowPass(gY[totalInterruptCounter + 1],gY[totalInterruptCounter], ALPHA);

//    Serial.print("1");
//    Serial.println(aY[totalInterruptCounter]);
//    Serial.print("2");
//    Serial.println(HighPass_Acel[totalInterruptCounter]);

    //Serial.print(gY[totalInterruptCounter]);
    //Serial.print(" gyro  ");
    //Serial.println(LowPass_Gyro[totalInterruptCounter]);
    
    }
    
  }
  
}

void loop() {

  if(timerInterruptOn()){

    //Serial.println(1);
    
    dataSensor = readAcel();

    //Serial.println(2);

    //desplazarArrays();

    for(int i = 0; i < 100; i++){
      //aY[i] <<= 1;
      //HighPass_Acel[i] <<= 1;
      
      //aY[i] = aY[i + 1];
      //HighPass_Acel[totalInterruptCounter] = HighPass_Acel[totalInterruptCounter + 1];
    }
    
    //aX[arraySize - 1] = dataSensor.aX;
    aY[arraySize - 1] = dataSensor.aY;
    //aZ[arraySize - 1] = dataSensor.aZ;

    //gX[arraySize - 1] = dataSensor.gX;
    //gY[arraySize - 1] = dataSensor.gY;
    //gZ[arraySize - 1] = dataSensor.gZ;

    HighPass_Acel[arraySize - 1] = ZeroIfLessThan(1500,HighPass(aY[arraySize - 1],aY[arraySize - 2], ALPHA));

    //LowPass_Gyro[arraySize - 1] = LowPass(gY[arraySize - 1],gY[arraySize - 2], ALPHA);

    //Serial.println(1);
    Serial.println(HighPass_Acel[arraySize - 1]); 
    
    //if(totalInterruptCounter % 10){}

  }
  }
 

void desplazarArrays(){
  
    for(int i = 0; i < 100; i++){ //cambiar a 200

    //aX[i] = aX[i + 1];
    aY[i] = aY[i + 1];
    //aZ[i] = aZ[i + 1];

    //gX[i] = gX[i + 1];
    //gY[i] = gY[i + 1];
    //gZ[i] = gZ[i + 1];

    HighPass_Acel[totalInterruptCounter] = HighPass_Acel[totalInterruptCounter + 1];

    //LowPass_Gyro[totalInterruptCounter] = LowPass_Gyro[totalInterruptCounter + 1];
   
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
