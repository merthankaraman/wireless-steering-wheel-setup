const int axis_numbers = 4, button_numbers = 4;
const int node_numbers = 4;
const short joystick_button_numbers = 16;

const uint16_t nodes[node_numbers] = {00,01,02,03};
const int center = 0;
const int wheel = 1;
const int gear = 2;
const int pedals = 3;
boolean feedback_on = false;

const char node_names[node_numbers][8] = {"Center", "Wheel", "Gear", "Pedals"};

int axis_states[node_numbers+1][axis_numbers+1];
int32_t encoder_position;

boolean center_button_states[joystick_button_numbers], button_states[node_numbers+1][button_numbers+1];

float battery_states[node_numbers+1];

unsigned long passed_time = 0;

boolean show_screen = false, private_show = false;

int8_t show_number = -1;
uint8_t i = 0, j = 0;

const int CE = 10, CSN = 9;

void show_states(int node){
  Serial.print(node_names[node]); Serial.print("\t");
  Serial.print("Battery: "); Serial.print(battery_states[node]); Serial.print("V\t"); 
  Serial.print("Axis_states: ");
  for(i=0;i<axis_numbers;i++){
    Serial.print(axis_states[node][i]); Serial.print(" ");
  }
  Serial.print ("\t");
  Serial.print("button_states: ");
  //Serial.println();
  for(i=0;i<button_numbers;i++){
    Serial.print(button_states[node][i]); Serial.print(" ");
  }
  Serial.println();
}

void states(){
  Serial.println("**************");
  for (i=1;i<=node_numbers;i++){
    show_states(i);
  }
  Serial.print("**************\n\n\n\n\n\n\n");
  Serial.println();
}
