#include "LedBar.h"

LedBar::LedBar(int leds_in[], int count){
  ledCount = count;
  leds = (int*) malloc(sizeof(int) * ledCount);

  int i = 0;
  for(int i = 0; i < ledCount; i++){
    leds[i] = leds_in[i];
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
}

void LedBar::lightSingle(int ndx){
  // turn off all LEDS
  LedBar::turnOffAll();

  // turn on selected LED
  digitalWrite(leds[ndx], HIGH);
}

void LedBar::lightMultiple(int* ndxs, int count){
  //TODO: implement
}

void LedBar::turnOffAll(){
  int i; 
  for(i = 0; i < ledCount; i++){
    digitalWrite(leds[i], LOW);
  }
}

// light up indexes in range [lo, high)
void LedBar::lightRange(int lo, int high){
  LedBar::turnOffAll();

  int i;
  for(int i = lo; i < high; i++){
    digitalWrite(leds[i], HIGH);
  }
}

