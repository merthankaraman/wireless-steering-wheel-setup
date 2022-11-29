#include "variables.h"
#include "analogs.h"
#include "encoder.h"
#include "nrf24.h"
#include "DigitalWriteFast.h"
#include "PWM.h"
Pwm pwm;


void setup(){
  pwm.begin();
  pwm.setPWM(0);
  Serial.begin(115200);
  pins_setup();
  nrf24_setup();
  encoder_setup();
}

void loop(){
  encoder_get_datas();
  
  get_analog_datas();
  nrf24_loop();
  if (Serial.available()){
    char data = Serial.read();
    if (data == 'd'){
      show_screen = !show_screen;
      is_show_axis = false;
    }
    else if (data = 'a'){
      is_show_axis = !is_show_axis;
      show_screen = false;
    }
  }
  //Serial.print(!digitalRead(encoder_pins[0])); Serial.print("\t");  Serial.print(!digitalRead(encoder_pins[1])); Serial.print("\t"); Serial.println(encoder_position);
  if (is_show_axis) show_axis();
  if (show_screen) states();
  if ((encoder_position < encoder_max_offset) and (encoder_position > -encoder_max_offset)){
    feedback_pwm = feedback_pwm;
  }
  else {
    feedback_pwm = 0;
  }
  pwm.setPWM(feedback_pwm);
  Serial.println(feedback_pwm);
  delay(1);
}
