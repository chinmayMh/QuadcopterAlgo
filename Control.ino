

void control_update()
{
  Setpoint();
  newpid();
  
   //th=rx_values[2];
// m1.writeMicroseconds(th + /* motor_yaw_out */ + motor_pitch_out + motor_roll_out);
// m2.writeMicroseconds(th - /* motor_yaw_out */ - motor_pitch_out + motor_roll_out);
// m3.writeMicroseconds(th + /* motor_yaw_out */ - motor_pitch_out - motor_roll_out);
// m4.writeMicroseconds(th - /* motor_yaw_out */ + motor_pitch_out - motor_roll_out);

 Serial.println(motor_yaw_out);
 Serial.println(motor_pitch_out);
 Serial.println(motor_roll_out);
}



void Setpoint()
{
  
 if(rx_values[3]>(1470-50)  &&  rx_values[3]<(1450+50)  )                      // &&   rx_values[0]>1000  &&  rx_values[0]<2000)
 {yaw_setpoint = 0;}
 else
 {yaw_setpoint = 170 + (double) (rx_values[3] -1960) * 34 / 96;}               //yaw_setpoint=map(rx_values[0],1015,1980,-170,170);


 if(rx_values[0]>(1470-50)  &&  rx_values[0]<(1450+50)  )                        // &&   rx_values[0]>1000  &&  rx_values[0]<2000)
 {pitch_setpoint = 0;}
 else
 {pitch_setpoint = 20 + (double) (rx_values[0] -1960) * 4 / 96;}                  //map(rx_values[0],1000,1960,-45,45)
 

 if(rx_values[1]>(1470-50)  &&  rx_values[1]<(1470+50))
 {roll_setpoint = 0;}
 else
 {roll_setpoint = 30 + (double) (rx_values[1] - 1960) * 6 / 96;}
 
}
