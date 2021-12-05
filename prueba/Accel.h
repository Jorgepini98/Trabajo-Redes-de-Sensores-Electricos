#ifndef ACCEL_H
#define ACCEL_H

#include <MPU9250_asukiaaa.h>

//defino los pines del I2C para el ESP32
#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif




struct sensorData
{
  double aX;
  double aY;
  double aZ;

  double mX;
  double mY;
  double mZ;

  double gX;
  double gY;
  double gZ;
};


void sensorSetup();

struct sensorData readDataRaw();

String readData(int counter);

#endif
