/*  ------------------------------------------------------------------------
    AUTHOR:         Abidan Brito Clavijo
    FILE:           System_Configuration.h
    DATE:           10/12/2019
    STATE:          DONE
    FUNCTIONALITY:  Small internal library with basic dependencies, macros,
                    transmission initialization and settings for the system.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */

#ifndef SYSTEM_CONFIGURATION_H
#define SYSTEM_CONFIGURATION_H

//// DEPENDENCIES ////
#ifndef WIRE_H
#define WIRE_H

#include <Wire.h>                   // I2C communication protocol library

#endif
#include <Adafruit_ADS1015.h>       // ADS library
#include <Adafruit_Sensor.h>        // Unified Sensor library
#include <Adafruit_BMP280.h>        // Pressure / Altitude Sensor library

//// OBJECTS DEClARATION ////
Adafruit_ADS1115 adc(0x48);     // Defined at address '0x48'
Adafruit_BMP280 bmp;            // Sensor object - I2C interface

//// MACRO DEFINITIONS ////
#define POWER_PIN_SALINITY      5
#define POWER_PIN_HUMIDITY      4
#define OUTPUT_PIN_SALINITY     0
#define OUTPUT_PIN_HUMIDITY     1
#define OUTPUT_PIN_TEMPERATURE  2
#define OUTPUT_PIN_LUMINOSITY   3
#define LOWER_BOUND_SALINITY    1150
#define UPPER_BOUND_SALINITY    22000
#define LOWER_BOUND_HUMIDITY    20200
#define UPPER_BOUND_HUMIDITY    10100
#define Y_INTERCEPT             0.786f
#define SLOPE                   0.0348f
#define D_TEMP                  -0.24f
#define NUM_READINGS            5

void init_setup() {
    // Initialize I2C protocol library
    Wire.begin();

    // Set data rate for serial data transmission
    Serial.begin(9600);

    // Turn on ADS1115
    adc.begin();

    // Gain (ADC Range) -> +/- 4.096 V (1 bit = 2 mV)
    adc.setGain(GAIN_ONE);

    // Set power pins mode
    pinMode (POWER_PIN_HUMIDITY, OUTPUT);
    pinMode (POWER_PIN_SALINITY, OUTPUT);

} // init_setup()

#endif
