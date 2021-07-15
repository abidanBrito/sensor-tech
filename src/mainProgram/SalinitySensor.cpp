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
SalinitySensor::SalinitySensor(Adafruit_ADS1115 * const adcAddress,
                               unsigned int const powerPin,
                               unsigned int const outputPin,
                               unsigned int const numReadings,
                               int16_t const lowerBound,
                               int16_t const upperBound)
    : adcAddress(adcAddress)
    , powerPin(powerPin)
    , outputPin(outputPin)
    , numReadings(numReadings)
    , lowerBound(lowerBound)
    , upperBound(upperBound)
{}

//----------------------------------------------------------------------
// Several salinity readings. It returns the mean average (%).
//----------------------------------------------------------------------
double SalinitySensor::getSalinity() const {
    // Floating-point for precision (prevent overflow)
    double averageReading = 0.0;
    double percentageSum = 0.0;
    double const minPercentage = 0.0, maxPercentage = 100.0;

    for(unsigned int i = 0; i < this->numReadings; i++) {
        // Get new reading
        int16_t adcReading = this->readADC();

        // Convert reading to percentage and add it up
        percentageSum += this->mapFloatingPoint(adcReading, minPercentage, maxPercentage);

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
int16_t SalinitySensor::readADC() const {
    // Supply power to the sensor
    digitalWrite(this->powerPin, HIGH);

    // Wait for sensor to settle
    delay(100);

    // Get reading
    int16_t adcReading = (*(this->adcAddress)).readADC_SingleEnded(this->outputPin);

    // Turn off power to the sensor
    digitalWrite(this->powerPin, LOW);

    return adcReading;
}

//----------------------------------------------------------------------
// It makes sure the provided reading doesn't exceed percentage bounds.
//----------------------------------------------------------------------
double SalinitySensor::safeValues(double * const reading) const {
    double const maxPercentage = 100.0;
    double const minPercentage = 0.0;

    if(*reading > maxPercentage) {
        *reading = maxPercentage;
    }
    else if(*reading < minPercentage) {
        *reading = minPercentage;
    }
}

//----------------------------------------------------------------------
// Analogous to "map()", but this one uses floating-point arithmetic and
// old range parameters are known. It returns the mapped value.
//----------------------------------------------------------------------
double SalinitySensor::mapFloatingPoint(int16_t const adcReading,
                                        double const newLowerBound,
                                        double const newUpperBound) const {
    int16_t oldUpperBound = this->upperBound;
    int16_t oldLowerBound = this->lowerBound;
    int16_t oldRange = oldUpperBound - oldLowerBound;
    double newRange = newUpperBound - newLowerBound;

    return ((((adcReading - oldLowerBound) * newRange) / oldRange) + newLowerBound);
}

//----------------------------------------------------------------------
// It prints out the current voltage (V) into the Serial Monitor for
// calibration purposes.
//----------------------------------------------------------------------
void SalinitySensor::printCalibrationReading() const {
    Serial.print("SALINITY = ");
    Serial.print(this->readADC());
    Serial.println(" (ADC reading)");
}
