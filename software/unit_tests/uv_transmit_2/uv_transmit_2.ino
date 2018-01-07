#include <cc1101.h>
#include <macros.h>
#include <pins.h>
#include <registers.h>

#define sizetx 2

byte TX_buffer[sizetx]={0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(2000);
  Serial.println("Begin.");

  setupRadio();
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

void loop() {
  // Send data for uv_receive_test. If uv_receive_test 
  // succeeds, success for this test as well.
  Serial.println("Transmitting..."); 
  sendUVData(5,6);
  
  delay(1000);
}


