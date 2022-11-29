#include "variables.h"
#include "analogs.h"
#include "nrf24.h"

void setup(){
  Serial.begin(115200);
  pins_setup();
  nrf24_setup();
}
void loop(){
  get_analog_datas();
  nrf24_loop();
  if (Serial.available()){
    char data = Serial.read();
    if (data == 'd'){
      show_screen = !show_screen;
    }
  }
  if (show_screen) states();
  //Serial.print(axis_states[0]); Serial.print("\t"); Serial.println(axis_states[1]); 
  delay(1);
}
