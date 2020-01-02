/*  ------------------------------------------------------------------------
    AUTHOR:         Abidan Brito Clavijo
    FILE:           HumiditySensor.cpp
    DATE:           02/01/2020
    STATE:          DONE
    FUNCTIONALITY:  Humidity sensor member functions (definitions).
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */

#include "HumiditySensor.h"

//----------------------------------------------------------------------
// Salinity sensor constructor. It initializes all member variables.
//----------------------------------------------------------------------
HumiditySensor::HumiditySensor(const Adafruit_ADS1115* const adcAddress,
                               const unsigned int outputPin,
                               const unsigned int numReadings,
                               const int16_t lowerBound,
                               const int16_t upperBound)
    : adcAddress(adcAddress)
    , outputPin(outputPin)
    , numReadings(numReadings)
    , lowerBound(lowerBound)
    , upperBound(upperBound)
{}

//----------------------------------------------------------------------
// Several humidity readings. It returns the mean average (%).
//----------------------------------------------------------------------
double HumiditySensor::getHumidity() const {
    // Floating-point for precision (prevent overflow)
    double averageReading = 0.0;
    double percentageSum = 0.0;
    double minPercentage = 0.0, maxPercentage = 100.0;

    for (unsigned int i = 0; i < this->numReadings; i++) {
        // Get new reading
        int16_t reading = this->readHumidity();

        // Convert reading to percentage and add it up
        percentageSum += this->mapFloatingPoint(reading, minPercentage, maxPercentage);
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
int16_t HumiditySensor::readHumidity() const {
    // Wait for sensor to settle
    delay(50);

    // Get reading
    int16_t reading = (*(this->adcAddress)).readADC_SingleEnded(this->outputPin);

    return reading;
}

//----------------------------------------------------------------------
// It makes sure the provided reading doesn't exceed percentage bounds.
//----------------------------------------------------------------------
double HumiditySensor::safeValues(double* const reading) const {
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
double HumiditySensor::mapFloatingPoint(const int16_t adcReading,
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
void HumiditySensor::printCalibrationReading() const {
    Serial.print("Humidity (voltage) = ");
    Serial.print(this->readHumidity());
    Serial.println(" (mV)");
}
