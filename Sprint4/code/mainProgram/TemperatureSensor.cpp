/*  ------------------------------------------------------------------------
    AUTHOR:         Abidan Brito Clavijo
    FILE:           TemperatureSensor.cpp
    DATE:           02/01/2020
    STATE:          DONE
    FUNCTIONALITY:  Temperature sensor member functions (definitions).
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */

#include "TemperatureSensor.h"

//----------------------------------------------------------------------
// Temperature sensor constructor. It initializes all member variables.
//----------------------------------------------------------------------
TemperatureSensor::TemperatureSensor(const Adafruit_ADS1115* const adcAddress,
                                     const unsigned int outputPin,
                                     const unsigned int numReadings,
                                     const double slope,
                                     const double dTemp,
                                     const double yIntercept)
    : adcAddress(adcAddress)
    , outputPin(outputPin)
    , numReadings(numReadings)
    , slope(slope)
    , dTemp(dTemp)
    , yIntercept(yIntercept)
{}

//----------------------------------------------------------------------
// Single temperature reading. It returns the current temperature (º C).
//----------------------------------------------------------------------
double TemperatureSensor::getTemperature() const {
    // Read from ADC
    int16_t adcReading = this->readTemperature();

    // Convert ADC reading to voltage, [0, 4.096] (V) range.
    double newMin = 0.0, newMax = 4096.0;
    double voltage = this->mapFloatingPoint(adcReading, newMin, newMax) / 1000;

    // Convert voltaje value to temperature (º C).
    double temperature = - this->voltageToTemperature(voltage, slope, dTemp, yIntercept);

    return temperature;
}

//-----------------------------------------------------------------------
// Single ADC reading. It returns a signed integer (16-bit).
//-----------------------------------------------------------------------
int16_t TemperatureSensor::readTemperature() const {
    int16_t adcReading = (*(this->adcAddress)).readADC_SingleEnded(this->outputPin);

    return adcReading;
}

//-----------------------------------------------------------------------
// It converts ADC reading to a voltage value -> [0, 4.096] (V).
//-----------------------------------------------------------------------
double TemperatureSensor::voltageToTemperature(const double voltage,
                                               const double slope,
                                               const double dTemp,
                                               const double yIntercept) const {
    // Apply conversion formula
    double temperature = ((voltage - yIntercept) / slope) + dTemp;

    return temperature;
}

//----------------------------------------------------------------------
// Analogous to "map()", but this one uses floating-point arithmetic and
// old range parameters are known. It returns the mapped value.
//----------------------------------------------------------------------
double TemperatureSensor::mapFloatingPoint(const int16_t adcReading,
                                           const double newLowerBound,
                                           const double newUpperBound) const {
    int16_t oldupperBound = 32768;
    int16_t oldlowerBound = 0;

    int16_t oldRange = upperBound - lowerBound;
    double newRange = newUpperBound - newLowerBound;

    return ((((adcReading - lowerBound) * newRange) / oldRange) + newLowerBound);
}

//----------------------------------------------------------------------
// It prints out the current voltage (V) into the Serial Monitor for
// calibration purposes.
//----------------------------------------------------------------------
void Temperature::printCalibrationReading() const {
    // Read from ADC
    int16_t adcReading = this->readTemperature();

    // Convert ADC reading to voltage, [0, 4.096] (V) range.
    double voltage = this->mapFloatingPoint(adcReading, 0, 4096) / 1000;

    Serial.print("Temperature (voltage) = ");
    Serial.print(voltage);
    Serial.println(" (V)");
}
