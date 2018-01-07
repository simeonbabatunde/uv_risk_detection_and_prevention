/*uv_sensor_test.ino - Test cases are wrtten here.
  Created by Team_UV, November 7, 2017.
*/
#include <Wire.h>
#include "uv_sensor.h"

/* Wiring
 * 3.3V - VCC 
 * SDA - P 3.6
 * SCL - P 3.5
 * GND - GND
 */

//Initialize variables for unit testing 
uint16_t counter = 0;
int tests_run = 0;
int tests_passed = 0;

//Instantiate sensor class with default zopt address of 0x53
UV_Sensor uvs(0x53);    

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("\nTests run: \n");
}

void loop() {
  // The following are the unit tests:
  simple_unit_test("test_checkPowerOnStatus", uvs.checkPowerOnStatus() == true, "Power setup failed");
  simple_unit_test("test_enableSensor",  uvs.enableSensor() != 0x04, "Sensor failed to enable");
  simple_unit_test("test_SetupWithAddress",  uvs.zopt220xSetupWithAddress(0x53) == true, "I2C communications address set up failed");
  simple_unit_test("test_sensorSetup",  uvs.sensorSetup() == true, "Sensor set up failed");
  simple_unit_test("test_enableUVBSensing", uvs.enableUVBSensing() != 0x04, "Transmission Error");  
  simple_unit_test("test_dataAvailable", uvs.dataAvailable() == true, "Data availability Failed");  
  simple_unit_test("test_getUVB", uvs.getUVB() >= 0, "UVB value should be substantial");  
  simple_unit_test("test_getAdjustedUVB", uvs.getAdjustedUVIndex(500, 18, 20) >= 0, "Adjusted UVB value should be substantial"); 
  simple_unit_test("test_getUVIndex", uvs.getUVIndex() >= 0, "UV Index value should be substantial"); 
  simple_unit_test("test_computeAverageUVIndex", uvs.computeAverageUVIndex(uvs.getUVIndex()) >= 0, "Average UV Index value should be substantial"); 
  
  Serial.print("\nTests run: ");
  Serial.println(tests_run);
  
  if (tests_run != tests_passed)
  {
    Serial.print("Tests passed: ");
    Serial.println(tests_passed);
  } else {
    Serial.println("ALL TESTS PASSED\n");
  }

  //Exit after the completion of first run. Press Reset button to re-run
  exit(0);
}

/*
  Below is a simple unit test class written for the uv_sensor module
*/
void simple_unit_test(String test_name, boolean condition, String message){
   tests_run++;
   String output;
  if(!condition){
      output = ": FAILED:  " + test_name + "\t*ERROR*:  " + message;
      Serial.print(tests_run);
      Serial.println(output);
   }else{
      tests_passed++;
      output = ": PASSED:  " + test_name;
      Serial.print(tests_run);
      Serial.println(output);
   }   
}
