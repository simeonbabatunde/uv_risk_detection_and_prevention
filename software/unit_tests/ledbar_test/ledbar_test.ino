#include <msp430.h>
#include "LedBar.h"

/*
Connect these pins:

P4_2 -> P1_2
P2_6 -> P3_0
P2_4 -> P1_6
P2_2 -> P1_7
P3_4 -> P1_5
P3_5 -> P1_4
P3_5 -> P1_3


Test will run only once, press reset to run again.
*/


#define LED1 P4_2
#define LED2 P2_6
#define LED3 P2_4
#define LED4 P2_2
#define LED5 P3_4
#define LED6 P3_5
#define LED7 P3_6

#define OUT1 P1_2
#define OUT2 P3_0
#define OUT3 P1_6
#define OUT4 P1_7
#define OUT5 P1_5
#define OUT6 P1_4
#define OUT7 P1_3


// initialize the led bar
int leds[] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7};
int ledCount = 7;
int led = 0;
LedBar ledBar(leds, ledCount);

// MUST be same size as led bar
int outs[] = {OUT1, OUT2, OUT3, OUT4, OUT5, OUT6, OUT7};

void setup() {
  Serial.begin(9600);
  // let serial monitor get ready
  delay(2000);
  
  // setup output
  int i;
  for(i=0;i<ledCount;i++){
    pinMode(outs[i], INPUT_PULLDOWN);
  } 

  // test led interface, one pin at a time
  for(i=0;i<ledCount;i++){
    singleTest(i);
  }

  // test lighting ranges of lights
  for(i=0;i<ledCount;i++){
    rangeTest(0,i+1);
  }

  // test turning off all lights
  turnOffAllTest();

  Serial.print("Tests concluded");
}

// test the led at index 'led' 
// with the output pin at index 'out'
void singleTest(int led){
  int errors = 0;
  Serial.print("Testing single LED at index ");
  Serial.print(led);
  Serial.println("... ");
  ledBar.lightSingle(led);
  delay(50);

  int i;
  for(i=0;i<ledCount;i++){
    if(i==led && digitalRead(outs[i]) != HIGH){
      Serial.println("\tERROR: Lit pin was not HIGH.");
      errors = 1;
    }
    if (i != led && digitalRead(outs[i] != LOW)){
      Serial.println("\tERROR: Unlit pin was HIGH");
      errors = 1;
    }
  }

  if(!errors){
    Serial.println("\tSUCCESS");
  }
}

void rangeTest(int start, int finish){
  int errors = 0;
  Serial.print("Testing range of LEDs from index ");
  Serial.print(start);
  Serial.print(" to index ");
  Serial.print(finish);
  Serial.println("... ");
  ledBar.lightRange(start, finish);
  delay(50);

  int i;
  for(i=0;i<ledCount;i++){
    if((i>=start && i < finish) && digitalRead(outs[i]) != HIGH){
      Serial.println("\tERROR: Lit pin was not HIGH.");
      errors = 1;
    }
    if ((i < start || i >= finish) && digitalRead(outs[i] != LOW)){
      Serial.println("\tERROR: Unlit pin was HIGH");
      errors = 1;
    }
  }
  if(!errors){
    Serial.println("\tSUCCESS");
  }  
}

void turnOffAllTest(){
  int errors = 0;
  Serial.println("Testing turn off all function... ");
  ledBar.turnOffAll();
  delay(50);

  int i;
  for(i=0;i<ledCount;i++){
    if (digitalRead(outs[i] != LOW)){
      Serial.println("\tERROR: Unlit pin was HIGH");
      errors = 1;
    }
  }

  if(!errors){
    Serial.println("\tSUCCESS");
  }
}


void loop() {
  // put your main code here, to run repeatedly: 
  Serial.print(".");
  delay(10000);
  
}
