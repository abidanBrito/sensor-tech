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

//// DEPENDENCIES ////
#include <Adafruit_ADS1015.h>       // ADS library

// Create an ADC object
Adafruit_ADS1115 ads1115(0x48);     // Defined at address '0x48'

//// FUNCTION PROTOTYPES ////
void safeValues(float * reading);

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
        percentageSum += map(adc0, lowerBound, upperBound, 0, 100);      // Add new percentage to the sum
        digitalWrite(powerPin, LOW);                                     // Turn off power to the sensor
        delay(10);                                                       // Wait between readings
    } // for

    // Get average reading value
    averageReading = percentageSum / numReadings;

    // Safety net (values within bounds)
    safeValues(&averageReading);

    return averageReading;
} // readSalinityV2()

//-----------------------------------------------------------------------
// Several humidity readings. Return the average
//-----------------------------------------------------------------------
float readHumidity(int powerPin, int outputPin, int lowerBound,
                                int upperBound, int numReadings) {
    float averageReading = 0.0;
    int percentageSum = 0;

    for(int i = 0; i < numReadings; i++) {
        digitalWrite(powerPin, HIGH);       // Supply power to the sensor
        delay(100);                         // Wait for sensor to settle

        // Returns '16-bit int' (using ' 32-bit int' to prevent overflow)
        int16_t adc0 = ads1115.readADC_SingleEnded(outputPin);

        int dato = map(adc0, upperBound, lowerBound, 100, 0);
        percentageSum += dato;    // Add reading to the running sum

        delay(25);                          // Wait before turning off power
        digitalWrite(powerPin, LOW);        // Turn off power to the sensor
        delay(25);                          // Wait between readings
    } // for

    // Get average reading value
    averageReading = percentageSum / numReadings;

    // Safety net (values within bounds)
    safeValues(&averageReading);

    return averageReading;
} // readHumidity()

//-----------------------------------------------------------------------
// Several temperature readings. Return the average
//-----------------------------------------------------------------------
float readTemperature(int numReadings, int outputPin){
    float averageReading = 0.0;
    int16_t sum = 0;

    for(int i = 0; i < numReadings; i++){
        sum += ads1115.readADC_SingleEnded(outputPin);
        delay(10);
    }

    // Get average reading value
    averageReading = (sum / numReadings);

    // Convert it to (0 - 4.096 V) range
    averageReading = (float) map(averageReading, 0, 32768, 0, 4096) / 1000;

    // Transform value from voltaje to temperature
    float temperature;
    float y_Intercept = 0.786;
    float slope = 0.0348;
    float d_Temp = -0.24;

    // Apply formula
    temperature = ((averageReading - y_Intercept) / slope) + d_Temp;

    return temperature;
} // readTemperature()

//----------------------------------------------------------------------
// Print out received data into the Serial Monitor
//----------------------------------------------------------------------
void printSensorReading(float measureValue, char StrLiteral[]) {
    // Print out measure in new range
    Serial.print(StrLiteral);
    Serial.print(" percentage: ");
    Serial.print(measureValue);
    Serial.println(" %");
} // printSensorReading()

//----------------------------------------------------------------------
// Make sure provided reading doesn't exceed bounds (0 - 100)
//----------------------------------------------------------------------
void safeValues(float *reading) {
    float upperBound = 100.0, lowerBound = 0.0;

    if(*reading > upperBound) {
        *reading = upperBound;
    }
    else if(*reading < lowerBound) {
        *reading = lowerBound;
    }
} // safeValues()

#endif
