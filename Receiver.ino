

void rx_initialise() 
{
  pinMode( 3   , INPUT); digitalWrite(3, HIGH);
  attachPinChangeInterrupt(  3     , change1, CHANGE);
  
  pinMode(  4  , INPUT); digitalWrite(4, HIGH);
  attachPinChangeInterrupt(   4    , change1, CHANGE);                                                       //  Enter the pin numbers
  
  pinMode(  5  , INPUT); digitalWrite(5, HIGH);
  attachPinChangeInterrupt(   5    , change1, CHANGE);
  
  pinMode( 6   , INPUT); digitalWrite(6, HIGH);
  attachPinChangeInterrupt(  6     , change1, CHANGE);
}


void change1()
{
 latest_interrupted_pin=PCintPort::arduinoPin;
 last_interrupt_time=micros();
 if(digitalRead(latest_interrupted_pin)==HIGH)
 {timer_start[latest_interrupted_pin - 3]=micros();}
 else
 {
  if(timer_start[latest_interrupted_pin - 3]!=0)
  {rx_values[latest_interrupted_pin - 3]=((volatile int)micros() - timer_start[latest_interrupted_pin - 3]);
   timer_start[latest_interrupted_pin - 3]=0;
  }
 }
}
