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

#ifndef WIRE_H
#define WIRE_H
#include <Wire.h>                   // I2C communication protocol library.
#endif

// Sensors (classes & library)
#include "Sensors.h"               // Sensor-related miscellaneous.
#include "SalinitySensor.h"
#include "HumiditySensor.h"
#include "TemperatureSensor.h"
#include "LuminositySensor.h"
#include "RainGauge.h"
/* #include "BMP280.h" */

//// OBJECTS DEClARATIONS ////
Adafruit_ADS1115 adc(0x48);     // Defined at address '0x48'.
/* Adafruit_BMP280 bmp;            // Sensor object - I2C interface. */

// Sensors
SalinitySensor salinityOBJ(&adc, POWER_PIN_SALINITY, OUTPUT_PIN_SALINITY,
                           NUM_READINGS, LOWER_BOUND_SALINITY, UPPER_BOUND_SALINITY);

HumiditySensor humidityOBJ(&adc, OUTPUT_PIN_HUMIDITY, NUM_READINGS,
                           LOWER_BOUND_HUMIDITY, UPPER_BOUND_HUMIDITY);

LuminositySensor lightOBJ(&adc, OUTPUT_PIN_LUMINOSITY);

TemperatureSensor tempOBJ(&adc, OUTPUT_PIN_TEMPERATURE, SLOPE,
                          D_TEMP, Y_INTERCEPT, NUM_READINGS);

/* BMP280 bmpOBJ(&bmp); */

RainGauge rainOBJ(POWER_PIN_SALINITY, ECHO_PIN_RAINGAUGE);

void init_setup() {
    // Initialize I2C protocol library.
    Wire.begin();

    // Set data rate for serial data transmission.
    Serial.begin(9600);

    // Turn on ADS1115.
    adc.begin();

    // Gain (ADC Range) -> +/- 4.096 V (1 bit = 2 mV).
    adc.setGain(GAIN_ONE);

    // Set power pins mode.
    pinMode(POWER_PIN_SALINITY, OUTPUT);
}

#endif
