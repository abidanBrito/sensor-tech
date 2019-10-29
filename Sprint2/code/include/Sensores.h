/*  ------------------------------------------------------------------------
    AUTHOR:        Abidan Brito, Elvira Montagud
    FILE:          Sensores.h
    DATE:          29/10/2019
    STATE:         DONE
    FUNCTIONALITY: Describe what this file is used for.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */
#ifndef SENSORES_H
#define SENSORES_H

//----------------------------------------------------------------------
// Several salinity readings. Return the average
//----------------------------------------------------------------------
float readSalinityV2(int powerPin, int inputPin, int lowerBound,
                                int upperBound, int numReadings) {
    //  Float for precision and prevent overflow
    float averageReading = 0.0;
    int percentageSum = 0;

    for (int i = 0; i < numReadings; i++) {
        digitalWrite(powerPin, HIGH);       // Supply power to the sensor
        delay(100);                         // Wait for sensor to settle

        // Returns '16-bit int' (using ' 32-bit int' to prevent overflow)
        int16_t adc0 = ads1115.readADC_SingleEnded(inputPin);            // Get new reading
        percentageSum += map(adc0, lowerBound, upperBound, 0, 100);                // Add new percentage to the sum
        digitalWrite(powerPin, LOW);                                     // Turn off power to the sensor
        delay(10);                                                       // Wait between readings
    } // for

    // Get average reading value
    averageReading = percentageSum / numReadings;

    return averageReading;
} // readSalinityV2()

//-----------------------------------------------------------------------
// Several humidity readings. Return the average
//-----------------------------------------------------------------------
int readHumidity(int powerPin, int inputPin, int lowerBound,
                                int upperBound, int numReadings) {
    float averageReading = 0.0;
    int percentageSum = 0;

    for(int i = 0; i < numReadings; i++) {
        digitalWrite(powerPin, HIGH);    // Supply power to the sensor
        delay(100);                         // Wait for sensor to settle

        // Returns '16-bit int' (using ' 32-bit int' to prevent overflow)
        int16_t adc0 = ads1115.readADC_SingleEnded(inputPin);

        int dato = map(adc0, upperBound, lowerBound, 100, 0);
        percentageSum += dato;    // Add reading to the running sum

        delay(25);                          // Wait before turning off power
        digitalWrite(powerPin, LOW);     // Turn off power to the sensor
        delay(25);                          // Wait between readings
    } // for

    // Get average reading value
    averageReading = percentageSum / numReadings;

    return averageReading;
} // readHumidity()

//----------------------------------------------------------------------
// Print out received data into the Serial Monitor
//----------------------------------------------------------------------
void printSensorReading(float measureValue, char StrLiteral[]) {
    // Avoid negative values
    if (measureValue < 0) {
        measureValue = 0;
    }

    // Print out measure in new range
    Serial.print(StrLiteral);
    Serial.print(" percentage: ");
    Serial.print(measureValue);
    Serial.println(" %");
} // printSensorReading()

#endif