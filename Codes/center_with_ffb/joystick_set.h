#include <Joystick.h>

const int encoder_resolution = 600, maxAngle = 900, cPR = encoder_resolution * 4;
const int encoder_maxValue = 450;//(float)maxAngle / 2 / 360 * cPR;


const int x_axis_range[2] = {-450,450}, y_axis_range[2] = {0,1023}, z_axis_range[2] = {0,1023};
const int rx_axis_range[2] = {0,1023}, ry_axis_range[2] = {0,1023}, rz_axis_range[2] = {0,1023};
const int clutch_range[2] = {280,820}, gas_range[2] = {280,680}, brake_range[2] = {350,550};
const int rudder_range[2] = {0,1023}, throttle_range[2] = {0,1023};

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD ,//JOYSTICK_TYPE_JOYSTICK **JOYSTICK_TYPE_GAMEPAD **JOYSTICK_TYPE_MULTI_AXIS 
  joystick_button_numbers, 0,                  // Button Count, Hat Switch Count
  true, true, true,     // X, Y and  Z Axis
  true, true, true,   // Rx, Ry, or Rz
  true, true,          // rudder or throttle
  false, false, false);  // accelerator, Brake, or Steering

Gains feedback_gains[2];
EffectParams feedback_effects[2];
int32_t feedback_forces[2] = {0};
int32_t positionChange=0, currentVelocity=0, currentAcceleration=0;


void joystick_setup() {
  Joystick.setXAxisRange(x_axis_range[0], x_axis_range[1]);
  Joystick.setXAxis(0);
  Joystick.setYAxisRange(y_axis_range[0], y_axis_range[1]);
  Joystick.setYAxis((y_axis_range[1]+1)/2);
  Joystick.setZAxisRange(z_axis_range[0], z_axis_range[1]);
  Joystick.setZAxis(0);
  
  Joystick.setRxAxisRange(gas_range[0], gas_range[1]);
  Joystick.setRxAxis(512);
  Joystick.setRyAxisRange(brake_range[0], brake_range[1]);
  Joystick.setRyAxis(0);
  Joystick.setRzAxisRange(clutch_range[0], clutch_range[1]);
  Joystick.setRzAxis(0);

  /*Joystick.setRudderRange(rudder_range[0], rudder_range[1]);
  Joystick.setRudder((rudder_range[1]+1)/2);
  Joystick.setThrottleRange(throttle_range[0], throttle_range[1]);
  Joystick.setThrottle((throttle_range[1]+1)/2);*/
  
  for (i=0;i<joystick_button_numbers;i++){
    Joystick.setButton(i, 0);
  }
  if (feedback_on){
    feedback_gains[0].totalGain = 100;
    feedback_gains[0].constantGain = 100;
    feedback_gains[0].rampGain = 100;
    feedback_gains[0].squareGain = 100;
    feedback_gains[0].sineGain = 100;
    feedback_gains[0].triangleGain = 100;
    feedback_gains[0].sawtoothdownGain = 100;
    feedback_gains[0].sawtoothupGain = 100;
    feedback_gains[0].springGain = 100;
    feedback_gains[0].damperGain = 100;   //damperMaxVelocity 
    feedback_gains[0].inertiaGain = 100;  //inertiaMaxAcceleration
    feedback_gains[0].frictionGain = 100; //frictionMaxPositionChange 
    feedback_gains[0].customGain = 100;
    Joystick.setGains(feedback_gains);
  
    feedback_effects[0].springMaxPosition = 360;
    feedback_effects[0].frictionMaxPositionChange = 5;
    feedback_effects[0].inertiaMaxAcceleration = 5;
    feedback_effects[0].damperMaxVelocity  = 1;
    Joystick.setEffectParams(feedback_effects);
  }
  delay(1);
  Joystick.begin();
}
void set_buttons(){
  for (i=0;i<4;i++){
    center_button_states[i] = button_states[wheel][i];
  }
  center_button_states[4] = button_states[gear][3];
  for (i = 0;i<joystick_button_numbers;i++){
    Joystick.setButton(i, center_button_states[i]);
  }
}

void feedback_calculates(){
  encoder_position = axis_states[wheel][0];
  if (feedback_on){
    positionChange = axis_states[wheel][1];
    currentVelocity = axis_states[wheel][2];
    currentAcceleration = axis_states[wheel][3];
    feedback_effects[0].damperVelocity = currentVelocity;
    
    feedback_effects[0].inertiaAcceleration = currentAcceleration;
    
    feedback_effects[0].frictionPositionChange = positionChange;
    
    feedback_effects[0].springPosition = encoder_position;
    Joystick.getForce(feedback_forces);
    feedback_forces[0] = constrain(feedback_forces[0], -255, 255);
  }
  encoder_position >= encoder_maxValue ? feedback_forces[0] = -255 : (encoder_position <= -encoder_maxValue ? feedback_forces[0] = 255 : feedback_forces[0] = feedback_forces[0]);
  int feedback_pwm = feedback_forces[0];
  /*for(i=0;i<axis_numbers;i++){
    Serial.print(axis_states[wheel][i]); Serial.print(" ");
  }
  Serial.print ("\t");
  Serial.println(feedback_pwm);*/
  RF24NetworkHeader to_wheel(nodes[wheel]); bool ok = nrf_ag.write(to_wheel, &feedback_pwm, sizeof(feedback_pwm));
}

void set_axis(){
  feedback_calculates();
  Joystick.setXAxis(encoder_position);
  Joystick.setYAxis((y_axis_range[1]+1)/2);
  Joystick.setZAxis((z_axis_range[1]+1)/2);
  Joystick.setRxAxis(axis_states[pedals][0]);
  Joystick.setRyAxis(axis_states[pedals][1]);
  Joystick.setRzAxis(axis_states[pedals][2]);
  /*Joystick.setRudder((rudder_range[1]+1)/2);
  Joystick.setThrottle((throttle_range[1]+1)/2);*/
}

void joystick_config(){
  if(Serial.available()){
    char serial_data = Serial.read();
    if(serial_data >= 'a' && serial_data <= 'z') serial_data += 'A' - 'a';
    if(serial_data == 'S'){
      show_screen = !show_screen;
      private_show = false;
    }
    else if(serial_data == 'G'){
      show_number = gear;
      private_show = true;
    }
    else if(serial_data == 'P'){
      show_number = pedals;
      private_show = true;
    }
    else if(serial_data == 'W'){
      show_number = wheel;
      private_show = true;
    }
  }
}

void joystick_loop(){
  joystick_config();
  axis2button();
  set_axis();
  set_buttons();
  if (show_screen){
    states();
  }
  if (private_show){
    show_states(show_number);
  }
}
