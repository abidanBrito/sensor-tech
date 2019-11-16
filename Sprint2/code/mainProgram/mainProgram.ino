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
#include <Wire.h>                   // I2C communication protocol library
#include "Sensores.h"               // Analog sensors library

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
    uint outputPinSalinity = 0, outputPinHumidity = 1, outputPinTemperature = 2;

    // Calibration bounds declaration & initialization
    uint lowerBoundSalinity = 1450, upperBoundSalinity = 26040;
    uint lowerBoundHumidity = 20475, upperBoundHumidity = 10115;

    // Number of readings to average out by the sensors
    uint numReadings = 5;

    // Salinity measure
    float meanSalinity = readSalinityV2(powerPinSalinity, outputPinSalinity,
                                        lowerBoundSalinity, upperBoundSalinity,
                                        numReadings);

    // Print salinity measure
    printSensorReading(meanSalinity, "Salinity");

    // Humidity measure
    float meanHumidity = readHumidity(powerPinHumidity, outputPinHumidity,
                                        lowerBoundHumidity, upperBoundHumidity,
                                        numReadings);

    // Print humidity measure
    printSensorReading(meanHumidity, "Humidity");

    // Temperature measure
    float meanTemperature = readTemperature(numReadings, outputPinTemperature);

    // Print temperature measure
    printSensorReading(meanTemperature, "Temperature");

    // TODO(abi): wake on motion as well
    // Hibernate for a minute
    // ESP.deepSleep(DEEP_SLEEP_TIME * 1000000);

    // Hold on for a second
    delay(1000);
} // loop()
