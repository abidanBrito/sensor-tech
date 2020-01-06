/*  ------------------------------------------------------------------------
    AUTHOR:         Abidan Brito Clavijo
    FILE:           BMP280.h
    DATE:           02/01/2020
    STATE:          DONE
    FUNCTIONALITY:  BMP280 sensor class definition.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */
#ifndef BMP280_H
#define BMP280_H

#include <Adafruit_BMP280.h>

//----------------------------------------------------------------------
// BMP280 sensor class definition.
//----------------------------------------------------------------------
class BMP280 {
private:
    Adafruit_BMP280 * bmpAddress;

// MEMBER FUNCTIONS - DECLARATIONS
private:
    void defaultSampling() const;
public:
    BMP280(Adafruit_BMP280 * bmpAddress);   // Default constructor.
    void setup() const;                     // Set up the sensor (configuration).
    void printReadings() const;             // Print out sensor readings.
    double getTemperature() const;          // Return ambient temperature reading.
    double getPressure() const;             // Return barometric pressure reading.
    double getAltitude() const;             // Return altitude reading.
};

#endif
