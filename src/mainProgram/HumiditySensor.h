/*  ------------------------------------------------------------------------
    AUTHOR:         Abidan Brito Clavijo
    FILE:           HumiditySensor.h
    DATE:           02/01/2020
    STATE:          DONE
    FUNCTIONALITY:  Humidity sensor class definition.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */

#ifndef HUMIDITYSENSOR_H
#define HUMIDITYSENSOR_H

#include "ADC_API.h"

// ---------------------------------------------------
// Humidity (soil moisture) sensor class definition.
// ---------------------------------------------------
class HumiditySensor {
private:
    Adafruit_ADS1115 * adcAddress;
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
    HumiditySensor(Adafruit_ADS1115 * adcAddress,
                   unsigned int outputPin,
                   unsigned int numReadings,
                   int16_t lowerBound,
                   int16_t upperBound);         // Default constructor.
    double getHumidity() const;                 // Return mean humidity (%).
    void printCalibrationReading() const;       // Print voltage value for calibration.
};

#endif
