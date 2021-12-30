#include "Accel.h";

MPU9250_asukiaaa mySensor;

String DATA1;
String DATA2;
String DATA3;
String DATA4;



void sensorSetup(){
  
  #ifdef _ESP32_HAL_I2C_H_ // For ESP32
  Wire.begin(SDA_PIN, SCL_PIN);
  mySensor.setWire(&Wire);
#endif

  mySensor.beginAccel();
  mySensor.beginMag();
  mySensor.beginGyro();
}

struct sensorData readDataRaw(){

  sensorData dat;
  
  if (mySensor.accelUpdate() == 0 && mySensor.magUpdate() == 0 && mySensor.gyroUpdate() == 0) {

    //obtengo los valores del acelerómetro
    dat.aX = mySensor.accelX();
    dat.aY = mySensor.accelY();
    dat.aZ = mySensor.accelZ();

    //obtengo los valores del magnetómetro
    dat.mX = mySensor.magX();
    dat.mY = mySensor.magY();
    dat.mZ = mySensor.magZ();

    //obtengo los valores del giroscopio
    dat.gX = mySensor.gyroX();
    dat.gY = mySensor.gyroY();
    dat.gZ = mySensor.gyroZ();
    
    
    } else {
    Serial.println("Cannod read data values");
    }
  
  return dat;
  
}

String readData(int counter){

     sensorData dataSensor = readDataRaw();

     DATA1 = String(counter) + "," + String(millis());
     DATA2 = String(dataSensor.aX) + "," + String(dataSensor.aY) + "," +  String(dataSensor.aZ);
     DATA3 = String(dataSensor.mX) + "," + String(dataSensor.mY) + "," +  String(dataSensor.mZ);
     DATA4 = String(dataSensor.gX) + "," + String(dataSensor.gY) + "," +  String(dataSensor.gZ);
     //DATA4 = "2";
     //DATA3 = "1";

   //Serial.println(DATA1 + "," + DATA2 + "," + DATA3 + "," + DATA4 + "\n");
   
     return (DATA1 + "," + DATA2 + "," + DATA3 + "," + DATA4 + "\n");
  
}


//hacer función que me pasa directamente los valores en string con comas.
