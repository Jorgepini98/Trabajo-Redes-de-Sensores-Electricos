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

struct sensorData readData(){

  sensorData dat;
  
  if (mySensor.accelUpdate() == 0 && mySensor.magUpdate() == 0 && mySensor.gyroUpdate() == 0) {

    //obtengo los valores del acelerómetro
    dat.aX = mySensor.accelX()*10000;
    dat.aY = mySensor.accelY()*10000;
    dat.aZ = mySensor.accelZ()*10000;

    //obtengo los valores del magnetómetro
    dat.mX = mySensor.magX()*10000;
    dat.mY = mySensor.magY()*10000;
    dat.mZ = mySensor.magZ()*10000;

    //obtengo los valores del giroscopio
    dat.gX = mySensor.gyroX()*10000;
    dat.gY = mySensor.gyroY()*10000;
    dat.gZ = mySensor.gyroZ()*10000;
    
    } else {
    Serial.println("Cannod read data values");
    }
  
  return dat;
}
