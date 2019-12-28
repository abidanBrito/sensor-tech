#ifndef SALINITY_H
#define SALINITY_H

//// DEPENDENCIES ////
#include "System_Configuration.h"


void safeValues(float* reading);
//----------------------------------------------------------------------
// Several salinity readings. Return the average
//----------------------------------------------------------------------
float readSalinity(Adafruit_ADS1115* adc, int powerPin, int inputPin,
                     int lowerBound, int upperBound, int numReadings) {
    //  Float for precision and prevent overflow
    float averageReading = 0.0f;
    int percentageSum = 0;

    for (int i = 0; i < numReadings; i++) {
        // Supply power to the sensor
        digitalWrite(powerPin, HIGH);

        // Wait for sensor to settle
        delay(100);

        // Get new reading
        int16_t reading = (*adc).readADC_SingleEnded(inputPin);

        // Convert reading to percentage and add it to the sum
        percentageSum += map(reading, lowerBound, upperBound, 0, 100);

        // Turn off power to the sensor
        digitalWrite(powerPin, LOW);

        // Wait between readings
        delay(10);
    }

    // Get average reading value
    averageReading = percentageSum / numReadings;

    // Safety net (values within bounds)
    safeValues(&averageReading);

    return averageReading;
} // readSalinity()

//----------------------------------------------------------------------
// One salinity reading. Return the voltage
//----------------------------------------------------------------------
float readSalinity_V(Adafruit_ADS1115* adc, int powerPin, int inputPin) {

    // Supply power to the sensor
    digitalWrite(powerPin, HIGH);

    // Wait for sensor to settle
    delay(100);

    // Get new reading
    int16_t reading = (*adc).readADC_SingleEnded(inputPin);

    // Turn off power to the sensor
    digitalWrite(powerPin, LOW);

    return reading;
} // readSalinity()

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

#endif
