#include "Accel.h";
#include "SdCard.h";
#include "interrupt.h";
#include "NTP.h";
#include "OLED.h";

extern int totalInterruptCounter;
extern MPU9250_asukiaaa mySensor;

extern const char* ntpServer;

char buf[100];
sensorData dataSensor;

File file;

char fileName[20];

String data2Write = "";

String heading;

bool lee = false;

void setup() {

  Serial.begin(115200);

  NTP_Setup();

  String tiempo = getLocalTime();

  Serial.println(tiempo);

  delay(100);
  
  sensorSetup();

  delay(500);

  SdSetup();

  delay(500);

  OLEDsetup();

  delay(100);

  int frecuency = 50;

  timerInterruptSetup(frecuency);

  ("/" + tiempo + ".txt").toCharArray(fileName,20);

  Serial.println(String(fileName));

  heading = ("Ninterrupt,ms,aX,aY,aZ,mX,mY,mZ,gX,gY,gZ \n"); 

  heading.toCharArray(buf, 100);

  lee = writeFile(SD, fileName, buf);

  if (lee){
  displayUp("Bueno");
  }
  else {
  displayUp("Malo");
  }
  
}

void loop() {

  if(timerInterruptOn()){
    
     readData(totalInterruptCounter).toCharArray(buf, 100);
    
     appendFile(SD, fileName, buf);
 
}

//Serial.println(totalInterruptCounter);
//if( totalInterruptCounter >= 100){
//  readFile(SD, fileName);
//}
}
