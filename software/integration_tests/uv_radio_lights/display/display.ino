#include <cc1101.h>
#include <macros.h>
#include <pins.h>
#include <registers.h>

#include "LedBar.h"
#include "display_unit.h"

#define LED1 P4_2
#define LED2 P2_6
#define LED3 P2_5
#define LED4 P4_3
#define LED5 P2_4
#define LED6 P3_5
#define LED7 P1_2
#define LED8 P3_0
#define LED9 P1_5
#define LED10 P1_4

// Radio receiver setup
byte RX_buffer[2]={0};
byte sizerx;

// Led bar setup
int leds[] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10};
int ledCount = 10;
LedBar ledBar(leds, ledCount);

// display unit setup
Display_Unit du;

void setup()
{
  Serial.begin(9600);
  delay(1000);
  setupRadioReceiver();
}

void loop()
{
   if(Radio.CheckReceiveFlag())
  {
    sizerx=Radio.ReceiveData(RX_buffer);
    Serial.print("Received:[");
    Serial.print(RX_buffer[0],DEC);
    Serial.print(",");
    Serial.print(RX_buffer[1],DEC);
    Serial.println("]");
    Radio.RxOn();
  }

  int led = du.byteToLight(RX_buffer[0]);
  //ledBar.lightSingle(led);
  ledBar.lightRange(0,led);
}

void setupRadioReceiver(){
  Radio.Init();
  Radio.SetDataRate(4);
  Radio.SetLogicalChannel(1);
  Radio.RxOn();
}


