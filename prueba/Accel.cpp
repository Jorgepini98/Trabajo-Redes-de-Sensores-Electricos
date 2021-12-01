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

struct sensorData readData(){
  
  sensorData data;
  
  if (mySensor.accelUpdate() == 0 && mySensor.magUpdate() == 0 && mySensor.gyroUpdate() == 0) {

    //obtengo los valores del acelerómetro
    data.aX = mySensor.accelX();
    data.aY = mySensor.accelY();
    data.aZ = mySensor.accelZ();

    //obtengo los valores del magnetómetro
    data.mX = mySensor.magX();
    data.mY = mySensor.magY();
    data.mZ = mySensor.magZ();

    //obtengo los valores del giroscopio
    data.gX = mySensor.gyroX();
    data.gY = mySensor.gyroY();
    data.gZ = mySensor.gyroZ();
    
    
    } else {
    Serial.println("Cannod read data values");
    }
  
  return data;
  
}


//hacer función que me pasa directamente los valores en string con comas.
