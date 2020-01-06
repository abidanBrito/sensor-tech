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

BMP280::BMP280(Adafruit_BMP280 * bmpAddress)
    : bmpAddress(bmpAddress)
{}

void BMP280::setup() const {
    // Check communication with the sensor
    if (!(*this->bmpAddress).begin()) {
        Serial.println("BMP280 sensor could not be found!");
        // Stop program flow with infinite loop
        while (1);
    }
    else {
        Serial.println("BMP280 sensor found!");
    }

    // Default settings from datasheet
    this->defaultSampling();
}

void BMP280::defaultSampling() const {
    (*this->bmpAddress).setSampling(Adafruit_BMP280::MODE_NORMAL,       // Operating Mode
                                    Adafruit_BMP280::SAMPLING_X2,       // Temperature oversampling
                                    Adafruit_BMP280::SAMPLING_X16,      // Pressure oversampling
                                    Adafruit_BMP280::FILTER_X16,        // Filtering
                                    Adafruit_BMP280::STANDBY_MS_500);   // Standby time
}

double BMP280::getPressure() const {
    double pressure = (*this->bmpAddress).readPressure() / 100;

    return pressure;
}

double BMP280::getAltitude() const {
    double altitude = (*this->bmpAddress).readAltitude(pressure + 1);

    return altitude;
}

double BMP280::getTemperature() const {
    double temperature = (*this->bmpAddress).readTemperature();

    return temperature;
}

void BMP280::printReadings() const {
    // Pressure (hPa)
    Serial.print("Pressure\t=\t");
    Serial.print((*this->bmpAddress).readPressure() / 100);
    Serial.println(" (hPa)");

    // Altitude (m)
    Serial.print("Altitude\t=\t");
    Serial.print((*this->bmpAddress).readAltitude(pressure + 1));
    Serial.println(" (m)");

    // Temperature (º C)
    Serial.print("Temperature\t=\t");
    Serial.print((*this->bmpAddress).readTemperature());
    Serial.println(" (º C)");

    // Line break to separate readings
    Serial.println();
}
