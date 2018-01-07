/*
  Test that the state machine code cycles as expected,
  without the states doing anything.
*/
#include "sensor_unit.h"


Sensor_Unit su;
void setup()
{  
  Serial.begin(9600);
  
}

void loop()
{
  // Test state 0  
  if(su.getState() != 0){
    Serial.print("ERROR: Expected: 0\tActual: ");
    Serial.print(su.getState());
  } else {
    Serial.println("SUCCESS: Expected: 0\tActual: 0");
  }
  su.next();

  // Test state 1
  if(su.getState() != 1){
    Serial.print("ERROR: Expected: 1\tActual: ");
    Serial.print(su.getState());
  } else {
    Serial.println("SUCCESS: Expected: 1\tActual: 1");
  }
  su.next();

  // Test state 2
  if(su.getState() != 2){
    Serial.print("ERROR: Expected: 2\tActual: ");
    Serial.print(su.getState());
  } else {
    Serial.println("SUCCESS: Expected: 2\tActual: 2");
  }
  su.next();

  Serial.println("\nTesting...");
  delay(1000);
}

