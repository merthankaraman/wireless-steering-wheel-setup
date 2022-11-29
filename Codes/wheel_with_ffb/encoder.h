uint32_t lastEncoderTime;
int16_t  currentPosition, lastPosition, currentVelocity, lastVelocity, maxVelocity, currentAcceleration, maxAcceleration, positionChange, maxPositionChange;    
const int encoder_pins[2] = {2,3};
const float encoder_resolution = 600.0;
const int encoder_max_offset = 800;

const int encoder_reset_pin = 5;

long encoder_pulses = 0;

int feedback_pwm = 0;

void encoder_dec() {digitalRead(encoder_pins[1]) ? encoder_pulses++:encoder_pulses--;}
   
void encoder_inc() {digitalRead(encoder_pins[0]) ? encoder_pulses--:encoder_pulses++;}

void encoder_setup(){
  lastEncoderTime = (uint32_t) millis();
  lastVelocity = 0;
  lastPosition = 0;
  pinMode(encoder_reset_pin, INPUT_PULLUP);
  pinMode(encoder_pins[0], INPUT_PULLUP);
  pinMode(encoder_pins[1], INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoder_pins[0]), encoder_dec, RISING);

  attachInterrupt(digitalPinToInterrupt(encoder_pins[1]), encoder_inc, RISING);
}

void encoder_get_datas(){
  if (!digitalRead(encoder_reset_pin)) encoder_pulses = 0;
  //encoder_position = encoder_pulses * 2;
  encoder_position = int((float(encoder_pulses)/2.0) / (encoder_resolution / 360.0));
  positionChange = encoder_position - lastPosition;
  int16_t diffTime = (int16_t)(millis() - lastEncoderTime) ;
  if (diffTime > 0) {
    currentVelocity = positionChange / diffTime;
    currentAcceleration = (abs(currentVelocity) - abs(lastVelocity)) / diffTime;
    lastEncoderTime = millis();
    lastVelocity = currentVelocity;
  }
  lastPosition = encoder_position;
  axis_states[0] = encoder_position;
  axis_states[1] = positionChange;
  axis_states[2] = currentVelocity;
  axis_states[3] = currentAcceleration;
}
