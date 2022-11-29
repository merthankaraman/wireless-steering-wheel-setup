const int axis_numbers = 4, button_numbers = 4;
int axis_states[axis_numbers] = {};
int encoder_position = 0;
boolean button_states[button_numbers] = {};

boolean show_screen = false, is_show_axis = false;

const uint16_t center_node = 00;
const uint16_t current_node = 01;

const int axis_pins[axis_numbers] ={A0,A0,A0,A0};

const int button_pins[button_numbers] ={A1,A2,A3,A4};

#define voltage_pin A5
float battery_voltage = 0.0;

const int CE = 8, CSN = 7;

void show_axis(){
  //Serial.print(encoder_position); Serial.print("\t");
  for(int i = 0;i <axis_numbers ;i++){
    Serial.print(axis_states[i]); Serial.print("\t");
  }
  Serial.println();
}

void states(){
  Serial.print("\n\n\n\n");
  Serial.print("Voltage: "); Serial.print(battery_voltage); Serial.println("V");
  for (int i=0;i<axis_numbers;i++){
    Serial.print("axis_states: "); Serial.print(i); Serial.print(": "); Serial.print(axis_states[i]); Serial.print("\t");
  }
  Serial.println("\n\n");
  for (int i=0;i<button_numbers;i++){
    Serial.print("button_states: "); Serial.print(i); Serial.print(": "); Serial.println(button_states[i]);
  }
  Serial.print("\n\n");
}
