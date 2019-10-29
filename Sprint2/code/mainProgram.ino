/*  ------------------------------------------------------------------------
    AUTHOR:        Abidan Brito, Elvira Montagud, Luis Belloch, Pablo Enguix
    FILE:          UnionHumedadSalinidad.ino
    DATE:          29/10/2019
    STATE:         DONE
    FUNCTIONALITY: Describe what this file is used for.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019. All rights reserved.
    ------------------------------------------------------------------------ */

//// IMPORT EXTERNAL LIBRARIES ////
#include <Sensores.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>       // ADS library

//// MACRO DEFINITIONS ////
#define DEEP_SLEEP_TIME             60000000    // Hibernating time

// Create an ADC object
Adafruit_ADS1115 ads1115(0x48);     // Defined at address '0x48'

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

    // Hibernate for a minute
    //ESP.deepSleep(DEEP_SLEEP_TIME);

    // Hold on for a minute
    delay(1000);
} // loop()