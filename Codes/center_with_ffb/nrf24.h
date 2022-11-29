#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

RF24 nrf(CE, CSN);     // nRF24L01 (CE, CSN)
RF24Network nrf_ag(nrf);

void nrf24_setup(){
  memset(center_button_states, 0, sizeof(center_button_states));
  memset(axis_states, 0, sizeof(axis_states));
  memset(button_states, 0, sizeof(button_states));
  memset(battery_states, 0, sizeof(battery_states));
  SPI.begin();
  nrf.begin();
  nrf_ag.begin(90, nodes[center]);  //(channel, node address)
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
  if (not(nrf_ag.available())) {
    if (millis() - passed_time >= 500){
      memset(center_button_states, 0, sizeof(center_button_states));
      memset(axis_states, 0, sizeof(axis_states));
      memset(button_states, 0, sizeof(button_states));
      memset(battery_states, 0, sizeof(battery_states));
      passed_time = millis();
    }
  }  
  while ( nrf_ag.available() ) {
    RF24NetworkHeader data_origin;
    nrf_ag.read(data_origin, &data_receive, sizeof(data_package));
    for(i=1;i<=node_numbers;i++){
      if (data_origin.from_node == nodes[i]){
        battery_states[i] = data_receive.battery_voltage;
        for(j=0;j<axis_numbers;j++){
          axis_states[i][j] = data_receive.axis_states[j];
        }
        for(j=0;j<button_numbers;j++){
          button_states[i][j] = data_receive.button_states[j];
        }
      }
    }
  }
}
