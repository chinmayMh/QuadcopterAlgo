int e1=0,e2=0,e3=0;

void newpid()
{ 
  yaw = ypr[0] * 180/M_PI;
  pitch = ypr[1] * 180/M_PI;
  roll = ypr[2] * 180/M_PI;
  
  motor_yaw_out = 0.5 *(yaw - yaw_setpoint) + 0.25 * (e1 - yaw_setpoint + yaw);
  e1 = yaw_setpoint - yaw;
 
  motor_pitch_out = 0.5 *(pitch - pitch_setpoint) + 0.25 * (e2 - pitch_setpoint + pitch);
  e2 = pitch_setpoint - pitch;

  motor_roll_out = 1 *(roll - roll_setpoint) + 0 * (e3 - roll_setpoint + roll);
  e3 = roll_setpoint + roll;
}

