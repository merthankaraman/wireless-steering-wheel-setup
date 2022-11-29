//                           Empty    Button 1   Button 2    Button 3   Button 4   Button 5   Button 6   Button 7   Button 8
int gear_positions[10][2]= {{484,0}, {386,550}, {586,556}, {386,595}, {586,599}, {386,630}, {590,636}, {411,672}, {590,677}};
const int tolerance = 15;

void axis2button(){
  if (axis_states[gear][0] != 0){
    for (i=0;i<10;i++){
      if (((axis_states[gear][0] + tolerance > gear_positions[i][0]) and (axis_states[gear][0] - tolerance <= gear_positions[i][0]))
          and ((axis_states[gear][1] + tolerance > gear_positions[i][1]) and (axis_states[gear][1] - tolerance <= gear_positions[i][1]))){
        center_button_states[i+5] = 1;
      }
      else if( (axis_states[gear][0] + tolerance > gear_positions[0][0]) and (axis_states[gear][0] - tolerance <= gear_positions[0][0]) ){
        center_button_states[9+5] = 1;
      }
      else{
        center_button_states[i+5] = 0;
      }
    }
  }
}
