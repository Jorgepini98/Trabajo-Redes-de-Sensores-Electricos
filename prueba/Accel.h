#include <MPU9250_asukiaaa.h>

//defino los pines del I2C para el ESP32
#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif

MPU9250_asukiaaa mySensor;

struct sensorData
{
  double aX;
  double aY;
  double aZ;

  double mX;
  double mY;
  double mZ;
};

void dataSetup(){
  
  #ifdef _ESP32_HAL_I2C_H_ // For ESP32
  Wire.begin(SDA_PIN, SCL_PIN);
  mySensor.setWire(&Wire);
#endif

  mySensor.beginAccel();
  mySensor.beginMag();
}

struct sensorData readData(){
  
  sensorData data;
  
  if (mySensor.accelUpdate() == 0 && mySensor.magUpdate() == 0) {

    //obtengo los valores del acelerómetro
    data.aX = mySensor.accelX();
    data.aY = mySensor.accelY();
    data.aZ = mySensor.accelZ();

    //obtengo los valores de la direcció del magnetómetro
    data.mX = mySensor.magX();
    data.mY = mySensor.magY();
    data.mZ = mySensor.magZ();
    
    } else {
    Serial.println("Cannod read data values");
    }
  
  return data;
  
}
