/*  ------------------------------------------------------------------------
    AUTHOR:         Abidan Brito Clavijo
    FILE:           SalinitySensor.h
    DATE:           01/01/2020
    STATE:          DONE
    FUNCTIONALITY:  Salinity sensor class definition.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */

#ifndef SALINITYSENSOR_H
#define SALINITYSENSOR_H

#ifndef ADCAPI_H
#define ADCAPI_H
#include <Adafruit_ADS1015.h>
#endif

// ---------------------------------------------------
// Salinity sensor class definition.
// ---------------------------------------------------
class SalinitySensor {
private:
    Adafruit_ADS1115 * adcAddress;
    unsigned int powerPin;
    unsigned int outputPin;
    unsigned int numReadings;
    int16_t lowerBound;
    int16_t upperBound;

// MEMBER FUNCTIONS - DECLARATIONS
private:
    int16_t readADC() const;                                // Return ADC reading.
    double safeValues(double * reading) const;              // Return reading within [0, 100] range.
    double mapFloatingPoint(int16_t adcReading,
                            double outLowerBound,
                            double outUpperBound) const;    // Floating-point compliant "map()".

public:
    SalinitySensor(Adafruit_ADS1115 * adcAddress,
                   unsigned int powerPin,
                   unsigned int outputPin,
                   unsigned int numReadings,
                   int16_t lowerBound,
                   int16_t upperBound);         // Default constructor.
    double getSalinity() const;                 // Return mean salinity (%).
    void printCalibrationReading() const;       // Print voltage value for calibration.
};

#endif
