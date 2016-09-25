void MPU_initialise()
{
   #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        TWBR = 24; 
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
   
    while (!Serial);
    Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
                                                                 
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();
    mpu.setXGyroOffset(68);
    mpu.setYGyroOffset(2);
    mpu.setZGyroOffset(-15);
    mpu.setZAccelOffset(1837);
    if (devStatus == 0) 
    {
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);  
        Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();
        Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;
        packetSize = mpu.dmpGetFIFOPacketSize();
    } 
    else 
    {
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }
    pinMode(LED_PIN, OUTPUT);
}




void MPU_update()
{
 if (!dmpReady) return;
    while (!mpuInterrupt && fifoCount < packetSize) 
    {
       
    } 
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();
    fifoCount = mpu.getFIFOCount(); 
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) 
    { 
        mpu.resetFIFO();
    } 
    else if (mpuIntStatus & 0x02) 
    { 
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();      
        mpu.getFIFOBytes(fifoBuffer, packetSize);       
        fifoCount -= packetSize;
        

        #ifdef OUTPUT_READABLE_YAWPITCHROLL
            
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            Serial.print("ypr\t");
            Serial.print(ypr[0] * 180/M_PI);
            Serial.print("\t");
            Serial.print(ypr[1] * 180/M_PI);
            Serial.print("\t");
            Serial.println(ypr[2] * 180/M_PI);
        #endif      
        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);
    }
}

