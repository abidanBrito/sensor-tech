/*  ------------------------------------------------------------------------
    AUTHOR:         Abidan Brito Clavijo
    FILE:           GPS_A2235.h
    DATE:           05/11/2019
    STATE:          DONE
    FUNCTIONALITY:  Describe what this file is used for.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */

#ifndef SYSTEM_CONFIGURATION_H
#define SYSTEM_CONFIGURATION_H

//// DEPENDENCIES ////
#include <Wire.h>       // I2C communication protocol library

//// MACRO DEFINITIONS ////
#define DEEP_SLEEP_TIME         15    // Hibernating time (15 s)
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