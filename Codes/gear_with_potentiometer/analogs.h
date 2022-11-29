void pins_setup(){
  for (int i=0;i<button_numbers;i++){
    pinMode(button_pins[i], INPUT_PULLUP);
  }
  /*for (int i=0;i<=axis_numbers;i++){
    pinMode(axis_pins[i], INPUT_PULLUP);
  }*/
}

void get_analog_datas(){//
  battery_voltage = (float(analogRead(voltage_pin)) * 5.0) / 1023.0;
  //axis_states[0] = analogRead(axis_pins[0]);
  for (int i=0;i<2;i++){
    axis_states[i] = analogRead(axis_pins[i]);
  }
  for (int i=1;i<button_numbers;i++){
    button_states[i] = !digitalRead(button_pins[i]);
  }
}
