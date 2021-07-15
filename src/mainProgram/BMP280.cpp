/*  ------------------------------------------------------------------------
    AUTHOR:         Abidan Brito Clavijo
    FILE:           BMP280.cpp
    DATE:           02/01/2020
    STATE:          DONE
    FUNCTIONALITY:  BMP280 sensor member functions (definitions).
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */

#include "BMP280.h"

//----------------------------------------------------------------------
// BMP280 sensor constructor. It initializes all member variables.
//----------------------------------------------------------------------
BMP280::BMP280(Adafruit_BMP280 * const bmpAddress)
    : bmpAddress(bmpAddress)
{}

//----------------------------------------------------------------------
// It initializes communication with the sensor and sets it up.
//----------------------------------------------------------------------
void BMP280::setup() const {
    // Check communication with the sensor
    if (!(*(this->bmpAddress)).begin()) {
        Serial.println("BMP280 sensor could not be found!");
        // Stop program flow with infinite loop
        while (1);
    }
    else {
        Serial.println("BMP280 sensor found!");
    }

    // Default settings from datasheet
    defaultSampling();
}

void BMP280::defaultSampling() const {
    (*(this->bmpAddress)).setSampling(Adafruit_BMP280::MODE_NORMAL,       // Operating Mode
                                      Adafruit_BMP280::SAMPLING_X2,       // Temperature oversampling
                                      Adafruit_BMP280::SAMPLING_X16,      // Pressure oversampling
                                      Adafruit_BMP280::FILTER_X16,        // Filtering
                                      Adafruit_BMP280::STANDBY_MS_500);   // Standby time
}

//----------------------------------------------------------------------
// Ambient temperature reading. It returns the current temperature (º C).
//----------------------------------------------------------------------
double BMP280::getTemperature() const {
    double temperature = bmpAddress->readTemperature();

    return temperature;
}

//----------------------------------------------------------------------
// Barometric pressure reading. It returns the current pressure (hPa).
//----------------------------------------------------------------------
double BMP280::getPressure() const {
    double pressure = (bmpAddress->readPressure()) / 100;

    return pressure;
}

//----------------------------------------------------------------------
// Altitude reading. It returns the current altitude (m).
//----------------------------------------------------------------------
double BMP280::getAltitude() const {
    double pressure = (bmpAddress->readPressure()) / 100;
    double altitude = bmpAddress->readAltitude(pressure + 1);

    return altitude;
}

//----------------------------------------------------------------------
// It prints out all magnitude readings into the Serial Monitor.
//----------------------------------------------------------------------
void BMP280::printReadings() const {
    // Pressure (hPa)
    Serial.print("Pressure\t=\t");
    Serial.print(bmpAddress->readPressure() / 100);
    Serial.println(" (hPa)");

    // Altitude (m)
    Serial.print("Altitude\t=\t");
    double pressure = bmpAddress->readPressure() / 100;
    Serial.print(bmpAddress->readAltitude(pressure + 1));
    Serial.println(" (m)");

    // Temperature (º C)
    Serial.print("Temperature\t=\t");
    Serial.print(bmpAddress->readTemperature());
    Serial.println(" (º C)");

    // Line break to separate readings
    Serial.println();
}
