#include <cc1101.h>
#include <macros.h>
#include <pins.h>
#include <registers.h>

#include <math.h>

//********* Pseduo UV sensor ***********
float uv_data[] = {
  1.0, 2.0, 2.0, 3.0, 4.0, 4.0, 3.0, 3.0, 4.0, 
  6.0, 7.0, 8.0, 9.0, 9.0, 8.0, 10.0, 11.0, 12.0, 
  12.0, 10.0, 8.0, 6.0, 4.0, 2.0, 0.0
};
int uvd_size = 25;
int uvd_index = 0;


float pseudoGetUVIndex(){
  float index = uv_data[uvd_index];
  uvd_index = (uvd_index + 1) % uvd_size;
  return index;
}
//**************************************


#define sizetx 2

byte TX_buffer[sizetx]={0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(2000);
  Serial.println("Begin.");

  setupRadio();

}

void loop() {
  // get uv data   
  float uvi = pseudoGetUVIndex();
  byte uvib = round(uvi);
  
  Serial.print("Transmitting ");
  Serial.print(uvib, DEC);
  Serial.println("...");

  // transmit uv data
  sendUVData(uvib, uvib);

  delay(1000);
}

void setupRadio(){
  Radio.Init();
  Radio.SetDataRate(4);
  Radio.SetLogicalChannel(1);
  Radio.SetTxPower(0);
  TX_buffer[0] = 0x00;
  TX_buffer[1] = 0x00;
}

void sendUVData(byte curr_uv, byte avg_uv){
  TX_buffer[0] = curr_uv;
  TX_buffer[1] = avg_uv;
  Radio.SendData(TX_buffer, sizetx);
}
