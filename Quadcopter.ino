#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include <Servo.h>
#include <PinChangeInt.h>

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 mpu;
#define OUTPUT_READABLE_YAWPITCHROLL
#define LED_PIN 13                                     
bool blinkState = false;

bool dmpReady = false; 
uint8_t mpuIntStatus;  
uint8_t devStatus;      
uint16_t packetSize;    
uint16_t fifoCount;     
uint8_t fifoBuffer[64]; 

Quaternion q;           
VectorInt16 aa;        
VectorInt16 aaReal;    
VectorInt16 aaWorld;   
VectorFloat gravity;   
float euler[3];        
float ypr[3];          

volatile bool mpuInterrupt = false;    
void dmpDataReady() 
{
    mpuInterrupt = true;
}


//++++++++++++++++++++++++++++++++++++++++++++   RX  Values    ++++++++++++++++++++++++++++++++++++++++++++++++++++=

volatile int rx_values[6]={1470,1470,1000,1470,1470,1470};
volatile int timer_start[6],last_interrupt_time;
uint8_t latest_interrupted_pin;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++   PID Variables   +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

double yaw=0,pitch=0,roll=0;
double motor_yaw_out = 0 , yaw_setpoint = 0;
double motor_pitch_out = 0 , pitch_setpoint = 0;
double motor_roll_out = 0 , roll_setpoint = 0 ; 

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Servo m1,m2,m3,m4;
float a1,a2,a3,a4;                                     //  Servo's inputs and variables
int th=1000,threq;



void setup() 
{
 Serial.begin(115200);
 m1.attach(8);
 m2.attach(9);
 m3.attach(10);
 m4.attach(11);
 MPU_initialise();
 MPU_update();
 //rx_initialise();
   
 m1.writeMicroseconds(1000);
 m2.writeMicroseconds(1000);
 m3.writeMicroseconds(1000);
 m4.writeMicroseconds(1000);

 while(!Serial.available());
 Serial.read();
}


void loop() 
{
  MPU_update();
  //rx_initialise();
  control_update();

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 

 
 int t1=100;
 int t2=100;
 if(Serial.available())
 {threq=Serial.parseInt();
  //rx_values[2]=threq;
  if(threq>1000 && threq<1800)
  {
   if(th==threq)
   {/*
     m1.writeMicroseconds(th);
     m2.writeMicroseconds(th);
     m3.writeMicroseconds(th);
     m4.writeMicroseconds(th);*/
   }
   
   else if(th<threq)
   {
     for( ;th<=threq;th++)
     {/*
       m1.writeMicroseconds(th);
       m2.writeMicroseconds(th);
       m3.writeMicroseconds(th);
       m4.writeMicroseconds(th);*/
       delay(t1);
     }
     Serial.print("Throttle = ");  Serial.println(th);
   }
   else if(th>threq)
   {
     for( ;th>=threq;th--)
     {/*
      m1.writeMicroseconds(th);
      m2.writeMicroseconds(th);
      m3.writeMicroseconds(th);
      m4.writeMicroseconds(th);*/
      delay(t2);
     }
     Serial.print("Throttle = ");  Serial.println(th);
   }
  
  }
  else
  {/*
   m1.writeMicroseconds(1000);
   m2.writeMicroseconds(1000);
   m3.writeMicroseconds(1000);
   m4.writeMicroseconds(1000);*/
   Serial.println("Motor Stopped");
  }
 }



 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 
}
