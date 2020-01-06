/*  ------------------------------------------------------------------------
    AUTHOR:         Abidan Brito Clavijo
    FILE:           RainGauge.h
    DATE:           05/01/2020
    STATE:          DONE
    FUNCTIONALITY:  Rain gauge sensor class definition.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */
#ifndef RAINGAUGE_H
#define RAINGAUGE_H

#include "Arduino.h"

// ---------------------------------------------------
// Rain gauge (rainfall) sensor class definition.
// ---------------------------------------------------
class RainGauge {
private:
    unsigned int powerPin;
    unsigned int echoPin;

// MEMBER FUNCTIONS - DECLARATIONS
public:
    RainGauge(unsigned int powerPin,
              unsigned int echoPin);    // Default constructor.
    double getRainfall() const;         // Return rainfall reading.
    void printRainfall() const;         // Print out rainfall reading.
};

#endif
