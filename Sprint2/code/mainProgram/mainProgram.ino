/*  ------------------------------------------------------------------------
    AUTHOR:        Abidan Brito, Elvira Montagud, Luis Belloch, Pablo Enguix
    FILE:          mainProgram.ino
    DATE:          29/10/2019
    STATE:         DONE
    FUNCTIONALITY: This is the main file that is to be executed. It can be
                   thought of as the center of the codebase.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019. All rights reserved.
    ------------------------------------------------------------------------ */

//// IMPORT EXTERNAL LIBRARIES ////
#include <Wire.h>                   // I2C communication protocol
#include "Sensores.h"               // Sensors library

//// MACRO DEFINITIONS ////
#define DEEP_SLEEP_TIME     15    // Hibernating time (15 s)

//----------------------------------------------------------------------
// Initial configuration
//----------------------------------------------------------------------
void setup() {
    // Set data rate for serial data transmission
    Serial.begin(9600);

    // Turn on ADS1115
    ads1115.begin();

    // Gain (ADC Range) -> +/- 4.096 V (1 bit = 2 mV)
    ads1115.setGain(GAIN_ONE);

    // Set power pins mode
    uint powerPinSalinity = 5, powerPinHumidity = 4;
    pinMode (powerPinHumidity, OUTPUT);
    pinMode (powerPinSalinity, OUTPUT);
} // setup()

//----------------------------------------------------------------------
// Runtime execution
//----------------------------------------------------------------------
void loop() {
    // Pins declaration & initialization
    uint powerPinSalinity = 5, powerPinHumidity = 4;
    uint inputPinSalinity = 0, inputPinHumidity = 1;

    // Calibration bounds declaration & initialization
    uint lowerBoundSalinity = 1450, upperBoundSalinity = 26040;
    uint lowerBoundHumidity = 20475, upperBoundHumidity = 10115;

    // Number of readings to average out by the sensors
    uint numReadings = 5;

    // Salinity measure
    float meanSalinity = readSalinityV2(powerPinSalinity, inputPinSalinity,
                                        lowerBoundSalinity, upperBoundSalinity,
                                        numReadings);

    // Print salinity measure
    printSensorReading(meanSalinity, "Salinity");

    // Humidity measure
    float meanHumidity = readHumidity(powerPinHumidity, inputPinHumidity,
                                        lowerBoundHumidity, upperBoundHumidity,
                                        numReadings);

    // Print humidity measure
    printSensorReading(meanHumidity, "Humidity");

    // TODO(abi): convert timer wake up to external wake up (RST).
    // Hibernate for a minute
    ESP.deepSleep(DEEP_SLEEP_TIME * 1000000);
    //ESP.deepSleep(0); // Wake up when RST receives a LOW signal

    // Hold on for a minute
    //delay(1000);
} // loop()
