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
TemperatureSensor::TemperatureSensor(Adafruit_ADS1115 * const adcAddress,
                                     unsigned int const outputPin,
                                     double const slope,
                                     double const dTemp,
                                     double const yIntercept,
                                     unsigned int const numReadings)
    : adcAddress(adcAddress)
    , outputPin(outputPin)
    , slope(slope)
    , dTemp(dTemp)
    , yIntercept(yIntercept)
    , numReadings(numReadings)
{}

//----------------------------------------------------------------------
// Mean average temperature reading. It returns the current
// temperature (º C).
//----------------------------------------------------------------------
double TemperatureSensor::getTemperature() const {
    // Floating-point for precision (prevent overflow)
    double voltageSum = 0.0;
    double averageVoltage = 0.0;
    double newMin = 0.0, newMax = 4096.0;

    for(unsigned int i = 0; i < this->numReadings; i++) {
        // Get new reading
        int16_t adcReading = this->readADC();

        // Convert ADC reading to voltage, [0, 4.096] (V) range.
        voltageSum += this->mapFloatingPoint(adcReading, newMin, newMax) / 1000;

        // Wait between readings
        delay(10);
    }

    averageVoltage = voltageSum / this->numReadings;

    // Convert voltaje value to temperature (º C).
    double temperature = - this->voltageToTemperature(averageVoltage, slope, dTemp, yIntercept);

    return temperature;
}

//----------------------------------------------------------------------
// Single ADC reading. It returns a signed integer (16-bit).
//----------------------------------------------------------------------
int16_t TemperatureSensor::readADC() const {
    int16_t adcReading = (*(this->adcAddress)).readADC_SingleEnded(this->outputPin);

    return adcReading;
}

//----------------------------------------------------------------------
// It converts ADC reading to a voltage value -> [0, 4.096] (V).
//----------------------------------------------------------------------
double TemperatureSensor::voltageToTemperature(double const voltage,
                                               double const slope,
                                               double const dTemp,
                                               double const yIntercept) const {
    // Apply conversion formula
    double temperature = ((voltage - yIntercept) / slope) + dTemp;

    return temperature;
}

//----------------------------------------------------------------------
// Analogous to "map()", but this one uses floating-point arithmetic and
// old range parameters are known. It returns the mapped value.
//----------------------------------------------------------------------
double TemperatureSensor::mapFloatingPoint(int16_t const adcReading,
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
void TemperatureSensor::printCalibrationReading() const {
    // Read from ADC
    int16_t adcReading = this->readADC();

    // Convert ADC reading to voltage, [0, 4.096] (V) range.
    double voltage = this->mapFloatingPoint(adcReading, 0, 4096) / 1000;

    Serial.print("Temperature (voltage) = ");
    Serial.print(voltage);
    Serial.println(" (V)");
}
