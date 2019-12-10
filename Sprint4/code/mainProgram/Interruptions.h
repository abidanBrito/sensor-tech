/*  ------------------------------------------------------------------------
    AUTHOR:         Abidan Brito Clavijo
    FILE:           Interruptions.h
    DATE:           10/12/2019
    STATE:          DONE
    FUNCTIONALITY:  Internal library to set up all interruptions (Wake on
                    Motion and Hibernation Mode).
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
#ifndef WIRE_H
#define WIRE_H

#include <Wire.h>     // I2C communication protocol library

#endif

//// MACROS ////
#define MPU9250_ADDRESS             0x68
#define WAKE_ON_MOTION_THRESHOLD    0x1F

#define POWER_MANAGEMENT_1          0x6B
#define POWER_MANAGEMENT_2          0x6C

#define INTERRUPTION_PIN_CFG        0x37
#define INTERRUPTION_ENABLE         0x38

#define MOTION_DETECTION_CTRL       0x69
#define ACC_FULL_SCALE_16_G         0x18
#define ACCEL_CONFIG_2              0x1D
#define LP_ACCEL_ODR                0x1E

#define ACC_INTERRUPT_PIN           4

//// FUNCTION PROTOTYPES ////
void ICACHE_RAM_ATTR handleInterruption();  // Store in RAM

void I2Cread(uint8_t accAddress, uint8_t memRegister, uint8_t numBytes, uint8_t *Data) {
   Wire.beginTransmission(accAddress);
   Wire.write(memRegister);
   Wire.endTransmission();

   Wire.requestFrom(accAddress, numBytes);
   uint8_t index = 0;
   while (Wire.available()) {
      Data[index++] = Wire.read();
   }
} // I2Cread()

void I2CwriteByte(uint8_t accAddress, uint8_t memRegister, uint8_t Data) {
   Wire.beginTransmission(accAddress);
   Wire.write(memRegister);
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
   I2CwriteByte(accAddress, POWER_MANAGEMENT_1, 0);
   I2CwriteByte(accAddress, POWER_MANAGEMENT_2, 7);
   I2CwriteByte(accAddress, ACCEL_CONFIG_2, 9);
   I2CwriteByte(accAddress, INTERRUPTION_ENABLE, 64);
   I2CwriteByte(accAddress, MOTION_DETECTION_CTRL, 192);
   I2CwriteByte(accAddress, WAKE_ON_MOTION_THRESHOLD, 10);    // [0 - 255] -> 8 bits
   I2CwriteByte(accAddress, LP_ACCEL_ODR, 3);                 // [0 - 16]  -> 4 bits
   I2CwriteByte(accAddress, POWER_MANAGEMENT_1, 32);
   I2CwriteByte(accAddress, INTERRUPTION_PIN_CFG, 128);

   // Read from intStatus in order to deactivate the interruption
   uint8_t status[1];
   I2Cread(accAddress, 0x3A, 1, status);
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
   I2Cread(MPU9250_ADDRESS, 0x3A, 1, intStatus);
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