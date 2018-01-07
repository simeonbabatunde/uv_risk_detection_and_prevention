#ifndef LEDBAR_H_
#define LEDBAR_H_

#include "Energia.h"

class LedBar{
  public:
    LedBar(int leds_in[], int count);
    void lightSingle(int ndx);
    void lightMultiple(int ndxs[], int count);
    void lightRange(int lo, int high);
    void turnOffAll();
   private:
    int *leds;
    int ledCount;
};

#endif
