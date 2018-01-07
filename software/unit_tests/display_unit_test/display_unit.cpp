#include "display_unit.h"

Display_Unit::Display_Unit() {
  state = 0;  
}

void Display_Unit::receive_UV_data(){
  //Serial.println("receive_UV_data");
  // get values from radio, store in curr_uv and avg_uv
  state = 1; //Change states
  delay(200);
}

void Display_Unit::change_LEDs(){
  //Serial.println("change_LEDs");
  // change uv values into led indexes to light up
  // int curr_led = byteToLight(curr_uv);
  // int avg_led = byteToLight(avg_uv);
  // curr_bar.lightSingle(curr_led);
  // avg_bar.lightSingle(avg_led);
  state = 0; //Change states
  delay(200);

}

void Display_Unit::next(){
  if(state == 0) {
    receive_UV_data();
  }
  else if (state == 1) {
    change_LEDs();
  } else {
    // reset machine if it gets off somehow
    state = 0;
    receive_UV_data();
  }
}

int Display_Unit::getState(){
  return state;
}

// convert a byte value to a light index, for a bar with 10 lights
int Display_Unit::byteToLight(const byte& toConvert){
  if(toConvert < 2){
    return 0;
  } else if (toConvert > 10){
     return 9;
  }
  else {
    return (int)toConvert - 1;
  }
}

