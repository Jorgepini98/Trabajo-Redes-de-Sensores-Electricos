#include "Accel.h";
#include "SdCard.h";
#include "interrupt.h";

char buf[50];
sensorData dataSensor;

File file;

String filename = "cvs.txt";

String data2Write = "";

void setup() {

  Serial.begin(115200);
  
  dataSetup();

  SdSetup();

  int frecuency = 50;

  timerInterruptSetup(frecuency);
  
  deleteFile(SD, "/data.txt");
  
}

void loop() {

  if(timerInterruptOn()){
     
     dataSensor = readData();
    
     data2Write = (String(totalInterruptCounter) + "," + String(millis()) + "," + String(dataSensor.aX) + ","
     + String(dataSensor.aY) + "," +  String(dataSensor.aZ) + "," +  String(dataSensor.mX)
     + "," +  String(dataSensor.mY) + "," +  String(dataSensor.mZ) + '\n');
    
     data2Write.toCharArray(buf, 50);
    
     appendFile(SD, "/data.txt", buf);
 
}

Serial.println(totalInterruptCounter);
//if( totalInterruptCounter >= 800){
//  readFile(SD, "/data.txt");
//}
}
