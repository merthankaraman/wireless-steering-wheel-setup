#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>


RF24 nrf(CE, CSN);     // nRF24L01 (CE, CSN)
RF24Network nrf_ag(nrf);


void nrf24_setup(){
  SPI.begin();
  nrf.begin();
  nrf_ag.begin(90, current_node);  //(channel, node address)
  nrf.setDataRate(RF24_2MBPS);
}
struct data_package {
  int axis_states[axis_numbers];
  boolean button_states[button_numbers];
  float battery_voltage;
};


data_package data_send;
data_package data_receive;




void nrf24_loop(){
  nrf_ag.update();
  for (int i=0;i<axis_numbers;i++){
    data_send.axis_states[i] = axis_states[i];
  }
  for (int i=0;i<button_numbers;i++){
    data_send.button_states[i] = button_states[i];
  }
  data_send.battery_voltage = battery_voltage;
  while ( nrf_ag.available() ) {
    RF24NetworkHeader data_origin;
    //nrf_ag.read(data_origin, &data_receive, sizeof(data_package));
    //feedback_pwm = data_receive.axis_states[0];
    nrf_ag.read(data_origin, &feedback_pwm, sizeof(feedback_pwm));
  }
  RF24NetworkHeader data_center(center_node);
  bool ok = nrf_ag.write(data_center, &data_send, sizeof(data_package));
  if (show_screen){
      ok ? Serial.println("Successful") : Serial.println("Failed");
    }
}
