#ifndef SENSOR_UNIT_H_
#define SENSOR_UNIT_H_

#include "Energia.h"
//#include "uv_sensor.h"
//#include "radio.h"

class Sensor_Unit
{
  public:
    Sensor_Unit();
    int getState();
    void next();
  private:  
    int state;
    int readings;
    double avg_uv;
    double total_uv;
    double curr_uv;

   // UV_Sensor sensor;
   // Radio radio;
    
    void get_UV_level();
    void calculate_avg();
    void transmit();
    
    byte double_to_byte(double);
};


#endif

