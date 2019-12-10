/*  ------------------------------------------------------------------------
    AUTHOR:         Abidan Brito Clavijo
    FILE:           GPS_A2235.h
    DATE:           05/11/2019
    STATE:          DONE
    FUNCTIONALITY:  Describe what this file is used for.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */

//// USAGE INSTRUCTIONS ////
/**************
// GND - GND
// VCC - VCC
// SDA - Pin 2
// SCL - Pin 14
***************/

#ifndef INTERRUPTIONS_H
#define INTERRUPTIONS_H

//// DEPENDENCIES ////
#include <Wire.h>       // I2C communication protocol library

//// MACROS ////
#define MPU9250_ADDRESS    0x68    // Accelerometer Address
#define MAG_ADDRESS        0x0C
#define ACC_INTERRUPT_PIN  4

#define GYRO_FULL_SCALE_250_DPS  0x00
#define GYRO_FULL_SCALE_500_DPS  0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18

#define ACC_FULL_SCALE_2_G  0x00
#define ACC_FULL_SCALE_4_G  0x08
#define ACC_FULL_SCALE_8_G  0x10
#define ACC_FULL_SCALE_16_G 0x18

//// FUNCTION PROTOTYPES ////
void ICACHE_RAM_ATTR handleInterrupt();

void I2Cread(uint8_t accAddress, uint8_t register, uint8_t numBytes, uint8_t *Data) {
   Wire.beginTransmission(accAddress);
   Wire.write(register);
   Wire.endTransmission();

   Wire.requestFrom(accAddress, numBytes);
   uint8_t index = 0;
   while (Wire.available()) {
      Data[index++] = Wire.read();
   }
} // I2Cread()

void I2CwriteByte(uint8_t accAddress, uint8_t register, uint8_t Data) {
   Wire.beginTransmission(accAddress);
   Wire.write(register);
   Wire.write(Data);
   Wire.endTransmission();
} // I2CwriteByte()

void setupAccelerometer(int accAddress) {
   Serial.println("Setting up the acelerometer...");

   // Acelerometer setup
   uint8_t reg = 28;
   I2CwriteByte(accAddress, reg, ACC_FULL_SCALE_16_G);
} // setupAccelerometer()

void accWakeOnMotionConfig(int accAddress) {
   // Wake on Motion configuration (accelerometer)
   I2CwriteByte(accAddress, 0x6B, 0);
   I2CwriteByte(accAddress, 0x6C, 7);
   I2CwriteByte(accAddress, 0x1D, 9);
   I2CwriteByte(accAddress, 0x38, 64);
   I2CwriteByte(accAddress, 0x69, 192);
   I2CwriteByte(accAddress, 0x1F, 10);    // [0 - 255] -> 8 bits
   I2CwriteByte(accAddress, 0x1E, 3);     // [0 - 16]  -> 4 bits
   I2CwriteByte(accAddress, 0x6B, 32);
   I2CwriteByte(accAddress, 0x37, 128);   // Don't change this register

   // Read from intStatus in order to deactivate the interruption
   uint8_t intStatus[1];
   I2Cread(accAddress, 0x3A, 1, intStatus);
} // accWakeOnMotionConfig()

void interruptionConfig(int interruptionPin) {
   // Set interruption pin (to be monitored)
   pinMode(interruptionPin, INPUT_PULLUP);

   // Link interruption to the pin, function and threshold (trigger upon CHANGE)
   attachInterrupt(digitalPinToInterrupt(interruptionPin), handleInterruption, CHANGE);
} // interruptionConfig()

void handleInterruption() {
   // Read from intStatus to deactivate the interruption
   uint8_t intStatus[1];
   I2Cread(AcelerometerInterruptionAddress, 0x3A, 1, intStatus);
} // handleInterruption()

void wakeOnMotion_setup() {
   Wire.begin();
   interruptionConfig(ACC_INTERRUPT_PIN);
   setupAccelerometer(MPU9250_ADDRESS);
   accWakeOnMotionConfig(MPU9250_ADDRESS);
} // wakeOnMotion_setup()

void deepSleep_loop(unsigned int sleepTime) {
   Serial.println("Hibernation mode! (10 s)");
   ESP.deepSleep(sleepTime * 1000000);
} // deepSleep_loop()

#endif