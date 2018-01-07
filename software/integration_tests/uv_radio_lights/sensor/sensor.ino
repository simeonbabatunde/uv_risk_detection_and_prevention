#include <cc1101.h>
#include <macros.h>
#include <pins.h>
#include <registers.h>
#include <Wire.h>
#include "uv_sensor.h"

#include <math.h>

#define sizetx 2

byte TX_buffer[sizetx]={0};

//Instantiate sensor class with default zopt address of 0x53
UV_Sensor uvs(0x53);

void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("Begin.");
  
  //Prepare Sensor for UVB reading
  uvs.enableUVBSensing();

  setupRadio();
}

void loop() {
  //collect  uv data   
  float uvi = uvs.getUVIndex();
  double auvi = uvs.computeAverageUVIndex(uvi);
  
  byte uvib = (byte)round(uvi);
  byte auvib = (byte)round(auvi);
  
  Serial.print("Transmitting ");
  Serial.print(uvib, DEC);
  Serial.print(" and ");
  Serial.print(auvib, DEC);
  Serial.println("...");

  // transmit uv data
  sendUVData(uvib, auvib);

  delay(1000);
}

void setupRadio(){
  Radio.Init();
  Radio.SetDataRate(4);
  Radio.SetLogicalChannel(1);
  Radio.SetTxPower(0);
  TX_buffer[0] = 0x00;
  TX_buffer[1] = 0x00;
}

void sendUVData(byte curr_uv, byte avg_uv){
  TX_buffer[0] = curr_uv;
  TX_buffer[1] = avg_uv;
  Radio.SendData(TX_buffer, sizetx);
}
