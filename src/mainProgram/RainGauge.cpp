/*  ------------------------------------------------------------------------
    AUTHOR:         Abidan Brito Clavijo
    FILE:           RainGauge.cpp
    DATE:           05/01/2020
    STATE:          DONE
    FUNCTIONALITY:  Rain gauge sensor member functions (definitions).
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */

#include "RainGauge.h"

#define PI 3.141539

// ----------------------------------------------------------------------
// Rain gauge sensor constructor. It initializes all member variables.
// ----------------------------------------------------------------------
RainGauge::RainGauge(unsigned int const powerPin,
                     unsigned int const echoPin)
    : powerPin(powerPin)
    , echoPin(echoPin)
{}

// ----------------------------------------------------------------------
// It returns the current rainfall volume (l).
// ----------------------------------------------------------------------
double RainGauge::getRainfall() const {
    unsigned int height;
    unsigned int elapsedTime;

    // Start at LOW for a clean pulse.
    digitalWrite(this->powerPin, LOW);
    delayMicroseconds(4);

    // Trigger after 10 (us) at HIGH.
    digitalWrite(this->powerPin, HIGH);
    delayMicroseconds(10);

    // End pulse.
    digitalWrite(this->powerPin, LOW);

    // Time measure (us).
    elapsedTime = pulseIn(this->echoPin, HIGH);

    // Convert to distance (cm).
    height = elapsedTime * 10 / 292/ 2;

    double const volume = (PI * 4*4 * height) / 1000;

    return volume;
}

//----------------------------------------------------------------------
// It prints out the current rainfall volume (l).
//----------------------------------------------------------------------
void RainGauge::printRainfall() const {
    double const volume = this->getRainfall();

    Serial.print("Vase volume: ");
    Serial.print(volume);
    Serial.println(" l");
}
