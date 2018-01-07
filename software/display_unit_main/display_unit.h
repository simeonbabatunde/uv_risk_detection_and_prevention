

#ifndef DISPLAY_UNIT_H_
#define DISPLAY_UNIT_H_

#include "Energia.h"

class Display_Unit
{
  public:
    Display_Unit();
    void receive_UV_data();
    void change_LEDs(); 
    void next();
    int getState();
    int byteToLight(const byte& toConvert);
  private:
    int state;
    byte curr_uv;
    byte avg_uv;

    //Led_Bar avg_bar();
    //Led_Bar curr_bar();
    
};


#endif

