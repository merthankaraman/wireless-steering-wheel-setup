const int axis_numbers = 4, button_numbers = 4;
int axis_states[axis_numbers] = {};
boolean button_states[button_numbers] = {};

boolean show_screen = false;

const uint16_t center_node = 00;
const uint16_t current_node = 03;


const int axis_pins[axis_numbers] ={A0,A1,A2,A3};

const int button_pins[button_numbers] ={4,5,6,7};

#define voltage_pin A5
float battery_voltage = 0.0;

const int CE = 2, CSN = 3;

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
  Serial.print("\n\n\n\n");
}
