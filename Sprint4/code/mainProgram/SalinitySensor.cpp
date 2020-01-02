/*  ------------------------------------------------------------------------
    AUTHOR:         Abidan Brito Clavijo
    FILE:           SalinitySensor.cpp
    DATE:           01/01/2020
    STATE:          DONE
    FUNCTIONALITY:  Salinity sensor member functions (definitions).
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */

#include "SalinitySensor.h"

//----------------------------------------------------------------------
// Salinity sensor constructor. It initializes all member variables.
//----------------------------------------------------------------------
SalinitySensor::SalinitySensor(const Adafruit_ADS1115* const adcAddress,
                               const unsigned int powerPin,
                               const unsigned int outputPin,
                               const unsigned int numReadings,
                               const int16_t lowerBound,
                               const int16_t upperBound)
    : adcAddress(adcAddress)
    , powerPin(powerPin)
    , outputPin(outputPin)
    , numReadings(numReadings)
    , lowerBound(lowerBound)
    , upperBound(upperBound)
{}

//----------------------------------------------------------------------
// Several salinity readings. It returns a mean average (%).
//----------------------------------------------------------------------
double SalinitySensor::getSalinity() const {
    // Floating-point for precision (prevent overflow)
    double averageReading = 0.0;
    double percentageSum = 0.0;
    double minPercentage = 0.0, maxPercentage = 100.0;

    for (unsigned int i = 0; i < numReadings; i++) {
        // Get new reading
        int16_t reading = this->readSalinity();

        // Convert reading to percentage and add it up
        percentageSum += this->mapFloatingPoint(reading, minPercentage, maxPercentage);

        // Wait between readings
        delay(10);
    }

    // Get mean average
    averageReading = percentageSum / this->numReadings;

    // Safety net (value within bounds)
    this->safeValues(&averageReading);

    return averageReading;
}

//----------------------------------------------------------------------
// Single ADC reading. It returns a signed integer (16-bit).
//----------------------------------------------------------------------
int16_t SalinitySensor::readSalinity() const {
    // Supply power to the sensor
    digitalWrite(this->powerPin, HIGH);

    // Wait for sensor to settle
    delay(100);

    // Get reading
    int16_t reading = (*(this->adcAddress)).readADC_SingleEnded(this->outputPin);

    // Turn off power to the sensor
    digitalWrite(this->powerPin, LOW);

    return reading;
}

//----------------------------------------------------------------------
// It makes sure the provided reading doesn't exceed percentage bounds.
//----------------------------------------------------------------------
double SalinitySensor::safeValues(double* const reading) const {
    double maxPercentage = 100.0;
    double minPercentage = 0.0;

    if(*reading > maxPercentage) {
        *reading = maxPercentage;
    }
    else if(*reading < minPercentage) {
        *reading = minPercentage;
    }
}

//----------------------------------------------------------------------
// Analogous to "map()", but this one uses floating-point arithmetic.
// It returns the mapped value.
//----------------------------------------------------------------------
double SalinitySensor::mapFloatingPoint(const int16_t adcReading,
                                        const double outLowerBound,
                                        const double outUpperBound) const {
    double numerator = (reading - this->lowerBound) * (outUpperBound - outLowerBound);
    double denominator = (this->upperBound - this->lowerBound) + outLowerBound;

    return (numerator / denominator);
}

//----------------------------------------------------------------------
// It prints out the current voltage (V) into the Serial Monitor for
// calibration purposes.
//----------------------------------------------------------------------
void SalinitySensor::printCalibrationReading() const {
    Serial.print("SALINITY (voltage) = ");
    Serial.print(this->readSalinity());
    Serial.println(" (mV)");
}
