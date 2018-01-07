#include <msp430.h>
#include "LedBar.h"

#define LED1 P1_5
#define LED2 P1_4
#define LED3 P1_3
#define LED4 P1_7
#define LED5 P1_6
#define LED6 P3_0

/*
int leds[] = {LED1, LED2, LED3, LED4, LED5, LED6};
int ledCount = 6;
int led = 0;
LedBar ledBar(leds, ledCount);
*/

int leds[] = {LED1, LED2, LED3};
int ledCount = 3;
LedBar ledBar(leds, ledCount);

void setup() {
  // put your setup code here, to run once:
  
}

void rangeOfThree(){
  /*
int leds[] = {LED1, LED2, LED3};
int ledCount = 3;
LedBar ledBar(leds, ledCount);
   */

   ledBar.lightRange(0,3);
   delay(1000);
   ledBar.turnOffAll();
   delay(1000);
}

void oneOnOneBlink(){
/*
int leds1[] = {LED1};
int ledCount = 1;
int led1 = 0;
LedBar lb1(leds1, ledCount);

int leds2[] = {LED2};
int led2 = 0;
LedBar lb2(leds2, ledCount);

  
  lb1.lightSingle(led1);
  lb2.lightSingle(led2);
  delay(1000);

  lb1.turnOffAll();
  delay(1000);
*/
}

void loop() {
  // put your main code here, to run repeatedly: 
  rangeOfThree();
  
}
