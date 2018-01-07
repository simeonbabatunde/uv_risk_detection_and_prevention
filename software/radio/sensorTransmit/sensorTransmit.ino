/*
  ZOPT2201 UV Sensor Reading and Transmission
  By: Team UV
  Date: Nov 7, 2017
  Licence: The ZOPT UV sensor implementation is an adaptation of Nathan Seidle's Code from 
  SparkFun Electronics, while the CC1101 Radio Implementation is an adaption of Josiah Hester's
  code from PERSIST LAB, Clemson University
  

  This example outputs the current UV Index (1 to 11+).
  According to the United States Environmental Protection Agency, The UV index scale is as follows:
  0 to 2  : LOW
  3 to 5  : MODERATE
  6 to 7  : HIGH
  8 to 10 : REY HIGH
  11+     : EXTREME

  The ZOPT2201 sensor detects UVB + Ambient Light Sensor (ALS) but for this project, we will utilize
  the UVB sensing feature.
*/

#include <Wire.h>       //Needed for I2C communication between Microcontroller and the UV sensor
#include <cc1101.h>
#include <macros.h>
#include <pins.h>
#include <registers.h>

#define sizetx 2

byte TX_buffer[sizetx]={0};
byte i;
double avgUVI, sum = 0;
long int count = 0;

void setup()
{  
  Serial.begin(9600);
  Radio.Init();
  Radio.SetDataRate(4); // Needs to be the same in Tx and Rx
  Radio.SetLogicalChannel(5); // Needs to be the same as receiver
  Radio.SetTxPower(0);
  for(i=0;i<sizetx;i++)
  {
     TX_buffer[i]=0;
  }
  
  while (!Serial);        //Ensure serial setup connection is complete
  Wire.begin();

  if (sensorSetup() == false)
  {
    Serial.println("Sensor failed to respond. Check wiring.");
    while (1); //Freeze!
  }
  Serial.println("Hurray, Sensor is online!");

  enableUVBSensing(); //UVB + UV_COMP channels activated

}

void loop()
{
  float uvIndex = getUVIndex();

  long uvb = getUVB(); //Get new data
  Serial.print("UVB Value is : ");
  Serial.println(uvb);
  
  Serial.print("UV Index is : ");
  Serial.println(uvIndex);

  ++count;  //Increment at every reading
  avgUVI = computeAverageUVIndex(uvIndex);
  Serial.print("Average UV Index is : ");
  Serial.println(avgUVI);

  if (uvIndex >= 0 && uvIndex <=2){
    Serial.println("LOW level of Exposure");
  }else if(uvIndex >= 3 && uvIndex <= 5){
    Serial.println("ODERATE level of Exposure");  
  }else if(uvIndex >= 6 && uvIndex <= 7){
    Serial.println("HIGH level of Exposure");  
  }else if(uvIndex >= 8 && uvIndex <= 10){
    Serial.println("VERY HIGH level of Exposure. ");  
  }else if(uvIndex >= 11){
    Serial.println("EXTREME level of Exposure, Take cover asap");  
  }

  // Fill the buffer with uv index and average  
  TX_buffer[0] = (byte) uvIndex; 
  TX_buffer[1] = (byte) avgUVI;
  Radio.SendData(TX_buffer,sizetx);
  
  Serial.println("\n");
  delay(100);
}

double computeAverageUVIndex(int uvindex){
    double average;
    sum = sum + uvindex;
    average = sum/count;
    
    return average;
  }
