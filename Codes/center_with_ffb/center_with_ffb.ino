#include "variables.h"
#include "nrf24.h"
#include "analog2button.h"
#include "joystick_set.h"


void setup(){
  feedback_on = false;
  Serial.begin(115200);
  delay(800);
  joystick_setup();
  nrf24_setup();
}

void loop() {
  nrf24_loop();
  joystick_loop();
}
