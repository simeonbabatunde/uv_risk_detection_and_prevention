/*
  uv_sensor.cpp - Library for reading uv value from ZOTP sensor.
  Created by Team UV, November 7, 2017.
  Released into the public domain.
*/
#include "Energia.h"
#include "uv_sensor.h"


UV_Sensor::UV_Sensor(byte zoptAddress){
  //This is the constructor
   Wire.begin();  
   sum = 0;
   count = 0;
   zoptAddress = zoptAddress;
   //enableUVBSensing(); //UVB + UV_COMP channels activated
}

//Setup the sensor with default zopt address of 0x53
boolean UV_Sensor::sensorSetup(){
  boolean result = zopt220xSetupWithAddress(zoptAddress); //Assume the default address
  return (result);
}

/*Attempts to talk to sensor. Returns false if sensor is not found
  If found, sets the sensor up with default UVB settings
  Call this function if you've changed the zopt I2C address */
boolean UV_Sensor::zopt220xSetupWithAddress(byte address){
  zoptAddress = address; //Do all the zopt I2C communications at this address
  
  byte deviceID = zoptReadRegister(ZOPT220x_PART_ID);
  if (deviceID != 0xB2)
  {
//    Serial.print("ID should be 0xB2. We heard 0x");
//    Serial.println(deviceID, HEX);
    return (false);
  }
  checkPowerOnStatus(); //Read the POS bit to clear it

  setMeasurementRate(2); //100ms default
  setResolution(0); //20 bit, 400ms, needed for best UVI calculations
  setGain(4); //Default for UVB

  return (true);
}

//Return the current UV index, assumes UVB sensor has been setup with default settings
float UV_Sensor::getUVIndex(void){
  byte counter = 0;
  while(!dataAvailable())
  {
    delay(10);
    if(counter++ > 50) //We should have a reading in 400ms
    {
      //We've timed out waiting for the data. Return error
      return(-1.0);
    }
  }

  long uvb = getUVB(); //Get new data
  float uvIndex = getAdjustedUVIndex(uvb, 4, 0); //Assumes default for UVI of gain:4, resolution:0
  return(uvIndex);
}


//Given UVB reading, and gain and resolution settings, outputs UV index
float UV_Sensor::getAdjustedUVIndex(long UVB, byte gain, byte resolution){
  byte gainMode = 0; //gain is 0 to 4, gainMode is mapped 1 to 18
  byte resolutionMode = 0; //resolution is 0 to 5, resolutionMode is mapped 20bit to 13bit

  //Convert the 5 gain settings to gainMode
  switch (gain)
  {
    case 0: gainMode = 1; break;
    case 1: gainMode = 3; break;
    case 2: gainMode = 6; break;
    case 3: gainMode = 9; break;
    case 4: gainMode = 18; break;
    default: gainMode = 18; break; //Unknown state
  }

  //Convert the 6 resolution settings to resolutionMode
  switch (resolution)
  {
    case 0: resolutionMode = 20; break; //20-bit
    case 1: resolutionMode = 19; break;
    case 2: resolutionMode = 18; break;
    case 3: resolutionMode = 17; break;
    case 4: resolutionMode = 16; break;
    case 5: resolutionMode = 13; break; //13-bit
    default: resolutionMode = 20; break; //Unknown state
  }

  long uvAdjusted = 18 / gainMode * pow(2, 20 - 20) * UVB;

  //The correction value is default 1. If you want to calculate the actual
  //solar angle you'll need lat/long/day/hh/mm
  float uviCorrection = 1.0;

  //First we need to calculation the elevation angle
  /*float elevationAngle = 

  //Let's calculate the correction!
  float c0 = 3.1543;
  float c1 = -0.06204;
  float c2 = 0.0002186;
  float c3 = 0.0000035516;
  uviCorrection = c0 * pow(elevation, 0);
  uviCorrection += c1 * pow(elevation, 1);
  uviCorrection += c2 * pow(elevation, 2);
  uviCorrection += c3 * pow(elevation, 3);*/  
  
  float uvIndex = uvAdjusted / (5500.0 * uviCorrection);

  return(uvIndex);
}

/*Returns the current UV data with temp compensation applied
  Assumes LS data bit 3 has been set (MAIN_STATUS)
  Poll dataAvailable() before calling this function*/
long UV_Sensor::getUVB(){
  return (zoptRead3Registers(ZOPT220x_UVB_DATA));
}

void UV_Sensor::setMeasurementRate(byte rate){
  if (rate > 7) rate = 7; //Error check

  //Read, set, write
  byte value = zoptReadRegister(ZOPT220x_LS_MEAS_RATE); //Read
  value &= ~(0b00000111); //Clear bits 2/1/0
  value |= rate; //Mask in rate
  zoptWriteRegister(ZOPT220x_LS_MEAS_RATE, value); //Write
}

void UV_Sensor::setResolution(byte resolution){
  if (resolution > 5) resolution = 5; //Error check

  //Read, set, write
  byte value = zoptReadRegister(ZOPT220x_LS_MEAS_RATE); //Read
  value &= ~(0b01110000); //Clear bits 6/5/4
  value |= (resolution << 4); //Mask in resolution
  zoptWriteRegister(ZOPT220x_LS_MEAS_RATE, value); //Write
}

void UV_Sensor::setGain(byte gain){
  if (gain > 4) gain = 4; //Error check
  //Read, set, write
  byte value = zoptReadRegister(ZOPT220x_LS_GAIN); //Read
  value &= ~(0b00000111); //Clear bits 2/1/0
  value |= gain; //Mask in gain
  zoptWriteRegister(ZOPT220x_LS_GAIN, value); //Write
}

//Returns true if Bit 5 is set
boolean UV_Sensor::checkPowerOnStatus(){
  byte value = zoptReadRegister(ZOPT220x_MAIN_STATUS); //Read
  Serial.println(value,DEC);
  if (value & 1 << 5) return (true);
  return (false);
}

//Check if new data is available
//Returns true if Bit 3 is set
boolean UV_Sensor::dataAvailable(){
  byte value = zoptReadRegister(ZOPT220x_MAIN_STATUS); //Read
  if (value & 1 << 3) return (true);
  return (false);
}

//Turns on sensor
//Sets LS_EN bit
byte UV_Sensor::enableSensor(void){
  //Read, set, write
  byte success;
  byte value = zoptReadRegister(ZOPT220x_MAIN_CTRL); //Read
  value |= (1 << 1); //Set LS_EN bit
  success = zoptWriteRegister(ZOPT220x_MAIN_CTRL, value); //Write
  return success;
}

//Turns off sensor. Clears LS_EN bit
byte UV_Sensor::disableSensor(void){
  //Read, set, write
  byte success;
  byte value = zoptReadRegister(ZOPT220x_MAIN_CTRL); //Read
  value &= ~(1 << 1); //Clear LS_EN bit
  zoptWriteRegister(ZOPT220x_MAIN_CTRL, value); //Write
  return success;
}

void UV_Sensor::standby() {
  setMode(1);  //Turn off everything and standby for I2C
}

byte UV_Sensor::enableUVBSensing() {
  byte success;
  success = setMode(3);  //UVB + UV_COMP channels activated
  return success;
}


//Sets the mode of the sensor
//Mode 1: Standby (power on default)
//Mode 2: Ambient light sensing w/ compensation
//Mode 3: UVB sensing w/ compensation
//Mode 4: ALS/UVBS_Raw
byte UV_Sensor::setMode(byte mode){
  //Read, set, write
  byte success;
  byte value = zoptReadRegister(ZOPT220x_MAIN_CTRL); //Read

  if (mode == 0) value &= ~(1 << 1); //Not a valid mode. Standby. Clear LS_EN bit
  else if (mode == 1) value &= ~(1 << 1); //Standby. Clear LS_EN bit
  else if (mode == 2) //ALS
  {
    value |= (1 << 1); //Set LS_EN bit
    value &= ~(1 << 2); //Clear RawMode_SEL bit
    value &= ~(1 << 3); //Clear LS_Mode bit for ALS
  }
  else if (mode == 3) //UVB
  {
    value |= (1 << 1); //Set LS_EN bit
    value &= ~(1 << 2); //Clear RawMode_SEL bit
    value |= (1 << 3); //Set LS_Mode bit for UVB
  }
  else if (mode == 4) //RawMode
  {
    //Send magic twiddly bytes
    zoptWriteRegister(ZOPT220x_SPECIAL_MODE_2, 0xB5); //Write first special byte
    zoptWriteRegister(ZOPT220x_SPECIAL_MODE_1, 0xDF); //Write second special byte
    zoptWriteRegister(ZOPT220x_SPECIAL_MODE_2, 0x04); //Write third special byte

    value |= (1 << 1); //Set LS_EN bit
    value |= (1 << 2); //Set RawMode_SEL bit
    value &= ~(1 << 3); //Clear LS_Mode bit
  }

  success = zoptWriteRegister(ZOPT220x_MAIN_CTRL, value); 
  return success;
}

//Sets the I2C address to 0x53 (default)
void UV_Sensor::setI2CAdr53(){
  //Read, set, write
  byte value = zoptReadRegister(ZOPT220x_DEVICE_CONFIG); //Read
  value &= ~(1 << 1); //Clear I2C address bit = 0x53
  zoptWriteRegister(ZOPT220x_DEVICE_CONFIG, value); //Write
}

//Does a soft reset. Give sensor at least 1000ms to reset
void UV_Sensor::softReset(){
  //Read, set, write
  byte value = zoptReadRegister(ZOPT220x_MAIN_CTRL); //Read
  value |= (1 << 4); //Set RST bit
  zoptWriteRegister(ZOPT220x_MAIN_CTRL, value); //Write
}


//The ALS and UVB data come in three byte pack: low/mid/high
//Read all three and store in long
//Returns -1 if times out
//Max size is 20 bits so signed long is ok
long UV_Sensor::zoptRead3Registers(byte addr){
  Wire.beginTransmission(zoptAddress);
  Wire.write(addr);
  Wire.endTransmission();

  Wire.requestFrom(zoptAddress, 3);

  //Non-blocking wait for 3 bytes
  byte counter = 0;
  while (Wire.available() < 3)
  {
    delay(1);
    if (counter++ > 25) return (-1); //Error
  }

  byte lowValue = Wire.read();
  byte midValue = Wire.read();
  byte highValue = Wire.read();

  long value = (long)highValue << 16 | (long)midValue << 8 | lowValue;

  return (value);
}

//Reads from a give location from the ZOPT220x
byte UV_Sensor::zoptReadRegister(byte addr){
  Wire.beginTransmission(zoptAddress);
  Wire.write(addr);
  Wire.endTransmission();

  Wire.requestFrom(zoptAddress, 1);
  if (Wire.available()) return (Wire.read());

  //Serial.println("I2C Error");
  return (0xFF); //Error
}

//Write a value to a spot in the ZOPT220x
//Returns 0:success, 1:data too long to fit in transmit buffer, 4:other error
byte UV_Sensor::zoptWriteRegister(byte addr, byte val){
  byte success;
  Wire.beginTransmission(zoptAddress);
  Wire.write(addr);
  Wire.write(val);
  success = Wire.endTransmission();

  return success;
}

//conpute the average UV reading
double UV_Sensor::computeAverageUVIndex(int uvindex){
    double average;
    count++;
    
    sum = sum + uvindex;
    average = sum/count;
    
    return average;
  }

  
