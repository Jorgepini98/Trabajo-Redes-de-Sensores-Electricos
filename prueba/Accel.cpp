#include "Accel.h";

MPU9250_asukiaaa mySensor;


void sensorSetup(){
  
  #ifdef _ESP32_HAL_I2C_H_ // For ESP32
  Wire.begin(SDA_PIN, SCL_PIN);
  mySensor.setWire(&Wire);
#endif

  mySensor.beginAccel();
  mySensor.beginMag();
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

     String A1 = String(counter) + "," + String(millis());
     String A2 = String(dataSensor.aX) + "," + String(dataSensor.aY) + "," +  String(dataSensor.aZ);
     String A3 = String(dataSensor.mX) + "," + String(dataSensor.mY) + "," +  String(dataSensor.mZ);
     String A4 = String(dataSensor.gX) + "," + String(dataSensor.gY) + "," +  String(dataSensor.gZ);
    
     return (A1 + "," + A2 + "," + A3 + "," + A4);
  
}


//hacer función que me pasa directamente los valores en string con comas.
