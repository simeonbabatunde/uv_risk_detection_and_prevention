/*
  TEAM UV - pedometer
  Ben Coomes
  Simeon Babatunde
  Miriam Lozneanu
  Kristopher Kohm
 
*/ 

#include <SPI.h>
#include <ADXL362.h>

ADXL362 xl;

int16_t x, y, z, m, mOld;
int16_t count = 0;
int16_t stepCount = 0;
int16_t threshold = 1200;
boolean isHigh = false;
float alpha = 0.5;

void setup(){
  
  Serial.begin(9600);
  xl.begin(P3_0);                 // Setup SPI protocol, issue device soft reset
  xl.beginMeasure();              // Switch ADXL362 to measure mode  
	
  Serial.println("Start Demo: Simple Read");
}


void loop(){
  int16_t x, y, z, t;  
  // read all three axis in burst to ensure all measurements correspond to same sample time
  xl.readXYZTData(x, y, z, t);  
  
  int32_t xx = (int32_t)x*x;
  int32_t yy = (int32_t)y*y;
  int32_t zz = (int32_t)z*z;

  int32_t mag = sqrt(xx + yy + zz);
  //Smoothen the values using Exponential Weighted Moving Average 
  m = (float)(mag * alpha) + (float)(mOld * (1 - alpha));
  mOld = m;

  //Check if the nagnitude crosses the Threshold line
  if(isHigh && m < threshold){
    isHigh = false;
    stepCount++;
    Serial.print("Steps: ");
    Serial.println(stepCount);
  } else if(!isHigh && m > threshold){
    isHigh = true;
  }

  delay(50);}

