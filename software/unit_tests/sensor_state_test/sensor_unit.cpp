#include "sensor_unit.h"

Sensor_Unit::Sensor_Unit(){
  // set up sensor, set up radio
  state = 0;
  readings = 0;
}

void Sensor_Unit::get_UV_level(){
  //Serial.println("get_UV_level");
  // use sensor class to get UV value. eg: 
  // uv_curr = sersor.get_uvReading();
  // readings++;
  delay(200);
  state = 1;
}

void Sensor_Unit::calculate_avg(){
  //Serial.println("calculate_avg");
  // do average calculations
  // total_uv += curr_uv;
  // avg_uv = total_uv / readings;
  delay(200);
  state = 2;
}

void Sensor_Unit::transmit(){
  //Serial.println("transmit");
  // transmit curr_uv and avg_uv as bytes
  byte byte_curr_uv  = double_to_byte(curr_uv);
  byte byte_avg_uv = double_to_byte(avg_uv);
  delay(200);
  state = 0;
}

byte Sensor_Unit::double_to_byte(double){
  return 0;
}

void Sensor_Unit::next(){
  if(state == 0){
    get_UV_level();
  } else if (state == 1){
    calculate_avg();
  } else if (state == 2){
    transmit();
  }
}

int Sensor_Unit::getState(){
  return state;
}



