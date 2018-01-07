/*
  Receiver/Display Unit 
  By: Team UV
  Date: Nov 7, 2017
  License: The CC1101 Radio Implementation is an adaption of Josiah Hester's
  code from PERSIST LAB, Clemson University
*/
  
#include <cc1101.h>
#include <macros.h>
#include <pins.h>
#include <registers.h>

byte RX_buffer[2]={0};
byte sizerx,i,flag;

void setup()
{
  Serial.begin(9600);
  delay(1000);
  Radio.Init();
  Radio.SetDataRate(4); // Needs to be the same in Tx and Rx
  Radio.SetLogicalChannel(5); // Needs to be the same as receiver
  Radio.RxOn();
}

void loop()
{
  if(Radio.CheckReceiveFlag())
  {
    sizerx=Radio.ReceiveData(RX_buffer);
    //Serial.write(RX_buffer[0]);
    Serial.print("UV index: ");
    Serial.println(RX_buffer[0], DEC);
    Serial.print("Average UV index: ");
    Serial.println(RX_buffer[1], DEC);
    Radio.RxOn();
  }
}


