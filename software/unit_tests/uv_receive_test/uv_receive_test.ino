#include <cc1101.h>
#include <macros.h>
#include <pins.h>
#include <registers.h>

/*
Connect these pins from microcontroller to radio:

VDD  -> VCC
SI   -> 15 / P1.6
SO   -> 14 / P1.7
CSn  -> 11 / P1.3
SCK  -> 7  / P2.2
GDO2 -> 10 / P3.6
GDO0 -> 8  / P3.4
GND  -> GND

*/

byte RX_buffer[2]={0};
byte sizerx;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  Radio.Init();
  Radio.SetDataRate(4); // Needs to be the same in Tx and Rx
  Radio.SetLogicalChannel(1); // Needs to be the same as transmitter
  Radio.RxOn();
}

void loop() {  // put your main code here, to run repeatedly: 
  if(Radio.CheckReceiveFlag())
  {
    sizerx=Radio.ReceiveData(RX_buffer);
    if((int)RX_buffer[0] == 5 && (int)RX_buffer[1] == 6){
      Serial.println("Success with Expected: [5,6] Received:[5,6]");
    }
    else{
      Serial.print("Failure with Expected: [5,6] Received:[");
      Serial.print(RX_buffer[0],DEC);
      Serial.print(",");
      Serial.print(RX_buffer[1],DEC);
      Serial.println("]");
    }
    Radio.RxOn();
  }
}
