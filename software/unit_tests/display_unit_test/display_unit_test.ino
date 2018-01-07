/*
  Test that the display state machine code cycles as expected,
  without the states doing anything.
*/
#include "display_unit.h"




Display_Unit du;
void setup()
{  
  Serial.begin(9600);
  delay(2000); // let serial monitor get ready.

  Serial.println("Testing byteToLight function...");
  byteToLightTest();
  delay(1000);
  
  Serial.println("\nStart state machine test...\n");
}

void byteToLightTest(){
  int n;

  Serial.print("Testing btl(0) -> 0... ");
  n = du.byteToLight(0);
  if(n == 0){
    Serial.println("SUCCESS");
  } else {
    Serial.print("ERROR. Expected: 0\tActual: ");
    Serial.println(n);
  }

  Serial.print("Testing btl(2) -> 1... ");
  n = du.byteToLight(2);
  if(n == 1){
    Serial.println("SUCCESS");
  } else {
    Serial.print("ERROR. Expected: 1\tActual: ");
    Serial.println(n);
  }

  Serial.print("Testing btl(5) -> 4... ");
  n = du.byteToLight(5);
  if(n == 4){
    Serial.println("SUCCESS");
  } else {
    Serial.print("ERROR. Expected: 4\tActual: ");
    Serial.println(n);
  }

  Serial.print("Testing btl(10) -> 9... ");
  n = du.byteToLight(10);
  if(n == 9){
    Serial.println("SUCCESS");
  } else {
    Serial.print("ERROR. Expected: 9\tActual: ");
    Serial.println(n);
  }

  Serial.print("Testing btl(12) -> 9... ");
  n = du.byteToLight(12);
  if(n == 9){
    Serial.println("SUCCESS");
  } else {
    Serial.print("ERROR. Expected: 0\tActual: ");
    Serial.println(n);
  }

  Serial.print("Testing btl(100) -> 0... ");
  n = du.byteToLight(100);
  if(n == 9){
    Serial.println("SUCCESS");
  } else {
    Serial.print("ERROR. Expected: 9\tActual: ");
    Serial.println(n);
  }
}

void loop()
{
  // Test state 0  
  if(du.getState() != 0){
    Serial.print("ERROR: Expected: 0\tActual: ");
    Serial.print(du.getState());
  } else {
    Serial.println("SUCCESS: Expected: 0\tActual: 0");
  }
  du.next();

  // Test state 1
  if(du.getState() != 1){
    Serial.print("ERROR: Expected: 1\tActual: ");
    Serial.print(du.getState());
  } else {
    Serial.println("SUCCESS: Expected: 1\tActual: 1");
  }
  du.next();

  Serial.println("\nTesting...");
  delay(1000);
}

