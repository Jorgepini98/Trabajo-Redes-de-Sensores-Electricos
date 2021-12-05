#include "Accel.h";
#include "SdCard.h";
#include "interrupt.h";
#include "NTP.h";

extern int totalInterruptCounter;
extern MPU9250_asukiaaa mySensor;

extern const char* ntpServer;

char buf[50];
sensorData dataSensor;

File file;

char fileName[20];

String data2Write = "";

void setup() {

  Serial.begin(115200);

  NTP_Setup();

  String tiempo = getLocalTime();

  Serial.println(tiempo);
  
  sensorSetup();

  SdSetup();

  int frecuency = 50;

  timerInterruptSetup(frecuency);

  ("/" + tiempo + ".txt").toCharArray(fileName,20);
  
  deleteFile(SD, fileName);
  
}

void loop() {

  if(timerInterruptOn()){
    
     readData(totalInterruptCounter).toCharArray(buf, 50);
    
     appendFile(SD, fileName, buf);
 
}

//Serial.println(totalInterruptCounter);
//if( totalInterruptCounter >= 800){
//  //readFile(SD, "/data.txt");
//}
}
