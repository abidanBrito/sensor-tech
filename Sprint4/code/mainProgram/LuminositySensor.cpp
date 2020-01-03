/*  ------------------------------------------------------------------------
    AUTHOR:         Abidan Brito Clavijo
    FILE:           LuminositySensor.cpp
    DATE:           02/01/2020
    STATE:          DONE
    FUNCTIONALITY:  Luminosity sensor member functions (definitions).
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */

#include "LuminositySensor.h"

//----------------------------------------------------------------------
// Luminosity Salinity sensor constructor. It initializes all member
// variables.
//----------------------------------------------------------------------
LuminositySensor::LuminositySensor(Adafruit_ADS1115 * const adcAddress,
                                   unsigned int const outputPin)
    : adcAddress(adcAddress)
    , outputPin(outputPin)
{}

//----------------------------------------------------------------------
// Single luminosity reading. It returns the current light state in the
// form of an unsigned integer.
//----------------------------------------------------------------------
unsigned int LuminositySensor::getLuminosityState() const {
    // Read from ADC
    int16_t const adcReading = this->readADC();

    // Convert ADC reading to voltage, [0, 4.096] (V) range.
    double newMin = 0.0, newMax = 4096.0;
    double voltage = this->mapFloatingPoint(adcReading, newMin, newMax);

    // Voltage expressed in mV.
    // Photodiode saturation voltage = 3.7 V.
    if(voltage <= 30) {             // Dark / covered
        return 0;
    }
    if (voltage <= 3700) {
        if(voltage <= 150) {
            return 1;               // Cloudy / in shadow
        }
        else if (voltage < 1500) {
            return 2;               // Cloudless
        }
        else {
            return 3;               // Sunny
        }
    }
}

//----------------------------------------------------------------------
// Single ADC reading. It returns a signed integer (16-bit).
//----------------------------------------------------------------------
int16_t LuminositySensor::readADC() const {
    int16_t adcReading = (*(this->adcAddress)).readADC_SingleEnded(this->outputPin);

    return adcReading;
}

//----------------------------------------------------------------------
// Analogous to "map()", but this one uses floating-point arithmetic and
// old range parameters are known. It returns the mapped value.
//----------------------------------------------------------------------
double LuminositySensor::mapFloatingPoint(int16_t const adcReading,
                                          double const newLowerBound,
                                          double const newUpperBound) const {
    int16_t oldUpperBound = 32768;
    int16_t oldLowerBound = 0;
    int16_t oldRange = oldUpperBound - oldLowerBound;
    double newRange = newUpperBound - newLowerBound;

    return ((((adcReading - oldLowerBound) * newRange) / oldRange) + newLowerBound);
}

//----------------------------------------------------------------------
// It prints out the current voltage (V) into the Serial Monitor for
// calibration purposes.
//----------------------------------------------------------------------
void LuminositySensor::printCalibrationReading() const {
    // Read from ADC
    int16_t adcReading = this->readADC();

    // Convert ADC reading to voltage, [0, 4.096] (V) range.
    double voltage = this->mapFloatingPoint(adcReading, 0, 4096);

    Serial.print("Luminosity (voltage) = ");
    Serial.print(voltage);
    Serial.println(" (mV)");
}
