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
  int aX;
  int aY;
  int aZ;

  int mX;
  int mY;
  int mZ;

  int gX;
  int gY;
  int gZ;
};


void sensorSetup(int acel,int magne,int gyro);

struct sensorData readAcel();
struct sensorData readMag();
struct sensorData readGyro();

#endif
