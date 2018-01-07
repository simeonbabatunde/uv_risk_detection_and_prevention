/*
  uv_sensor.h - Library for reading UV value with ZOPT sensor.
  Created by Team_UV, November 7, 2017.
  Released into the public domain. The ZOPT UV sensor implementation is an adaptation of 
  Nathan Seidle's Code from SparkFun Electronics

  This example outputs the current UV Index (1 to 11+).
  According to the United States Environmental Protection Agency, The UV index scale is as follows:
  0 to 2  : LOW
  3 to 5  : MODERATE
  6 to 7  : HIGH
  8 to 10 : REY HIGH
  11+     : EXTREME

  The ZOPT2201 sensor detects UVB + Ambient Light Sensor (ALS) but for this project, we will utilize
  the UVB sensing feature
*/
#ifndef UV_SENSOR_H_
#define UV_SENSOR_H_

//Register addresses
#define ZOPT220x_MAIN_CTRL 0x00
#define ZOPT220x_LS_MEAS_RATE 0x04
#define ZOPT220x_LS_GAIN 0x05
#define ZOPT220x_PART_ID 0x06
#define ZOPT220x_MAIN_STATUS 0x07
#define ZOPT220x_ALS_DATA 0x0D
#define ZOPT220x_UVB_DATA 0x10
#define ZOPT220x_UV_COMP_DATA 0x13
#define ZOPT220x_COMP_DATA 0x16
#define ZOPT220x_INT_CFG 0x19
#define ZOPT220x_INT_PST 0x1A
#define ZOPT220x_DEVICE_CONFIG 0x2F
#define ZOPT220x_SPECIAL_MODE_1 0x30
#define ZOPT220x_SPECIAL_MODE_2 0x31
#define SENSORTYPE_ZOPT2201 0xB2
#define SENSORTYPE_ZOPT2202 0xB2
//#define zoptAddress 0x53   //Default I2C address. Can be changed via software

#include <Wire.h>       //Needed for I2C communication 
#include "Energia.h"

class UV_Sensor{
  public:
    UV_Sensor(byte zoptAddress);
    boolean sensorSetup();
    boolean zopt220xSetupWithAddress(byte address);
    float getUVIndex();
    float getAdjustedUVIndex(long UVB, byte gain, byte resolution);
    long getUVB();
    void setMeasurementRate(byte rate);
    void setResolution(byte resolution);
    void setGain(byte gain);
    boolean checkPowerOnStatus();
    boolean dataAvailable();
    byte enableSensor();
    byte disableSensor();
    void standby();
    byte enableUVBSensing();
    byte setMode(byte mode);
    void setI2CAdr53();
    void softReset();
    long zoptRead3Registers(byte addr);
    byte zoptReadRegister(byte addr);
    byte zoptWriteRegister(byte addr, byte val); 
    double computeAverageUVIndex(int uvindex);  
     

  private:
    byte zoptAddress; 
    double sum;
    long count;   
};

#endif
