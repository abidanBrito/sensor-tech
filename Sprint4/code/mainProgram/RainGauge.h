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

// ---------------------------------------------------
// Rain gauge (rainfall) sensor class definition.
// ---------------------------------------------------
class RainGauge {
private:
    int powerPin;
    int echoPin;

// MEMBER FUNCTIONS - DECLARATIONS
public:
    RainGauge();
    double getRainfall() const;
    void printRainfall() const;
};

#endif
