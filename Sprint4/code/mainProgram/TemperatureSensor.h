/*  ------------------------------------------------------------------------
    AUTHOR:         Abidan Brito Clavijo
    FILE:           TemperatureSensor.h
    DATE:           02/01/2020
    STATE:          DONE
    FUNCTIONALITY:  Temperature sensor class definition.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */

#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

// ---------------------------------------------------
// Temperature sensor class definition.
// ---------------------------------------------------
class TemperatureSensor {
private:
    Adafruit_ADS1115* adcAddress;
    unsigned int outputPin;
    double slope;
    double dTemp;
    double yIntercept;

// MEMBER FUNCTIONS - DECLARATIONS
private:
    double readTemperature() const;                         // Return ADC reading.
    double voltageToTemperature(int16_t adcReading,
                                double slope,
                                double dTemp,
                                double yIntercept) const;   // Return voltage value from ADC reading.
    double mapFloatingPoint(int16_t adcReading,
                            double newlowerBound,
                            double newUpperBound) const;    // Floating-point compliant "map()".
public:
    TemperatureSensor(Adafruit_ADS1115* adcAddress,
                      unsigned int outputPin,
                      double slope,
                      double dTemp
                      double yIntercept);   // Default constructor.
    double getTemperature() const;          // Return temperature (º C).
    void printCalibrationReading() const;   // Print voltage value for calibration.
};

#endif
