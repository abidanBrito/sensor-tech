/*  ------------------------------------------------------------------------
    AUTHOR:         Abidan Brito Clavijo
    FILE:           LuminositySensor.h
    DATE:           02/01/2020
    STATE:          DONE
    FUNCTIONALITY:  Luminosity sensor class definition.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */

#ifndef LUMINOSITYSENSOR_H
#define LUMINOSITYSENSOR_H

class LuminositySensor {
private:
    Adafruit_ADS1115* adcAddress;
    unsigned int outputPin;

// MEMBER FUNCTIONS - DECLARATIONS
private:
    int16_t readADC() const;                                // Return ADC reading.
    double mapFloatingPoint(int16_t adcReading,
                            double outLowerBound,
                            double outUpperBound) const;    // Floating-point compliant "map()".

public:
    LuminositySensor(Adafruit_ADS1115* adcAddress,
                     unsigned int outputPin);       // Default constructor.
    unsigned int getLuminosityState() const;        // Return light state -> [0, 3].
    void printCalibrationReading() const;           // Print voltage value for calibration.
};

#endif
