#ifndef HUMIDITY_H
#define HUMIDITY_H

//// DEPENDENCIES ////
#include "System_Configuration.h"


void safeValues(float* reading);
//-----------------------------------------------------------------------
// Several humidity readings. Return the average
//-----------------------------------------------------------------------
float readHumidity(Adafruit_ADS1115* adc, int outputPin, int lowerBound,
                   int upperBound, int numReadings) {
    float averageReading = 0.0f;
    int percentageSum = 0;

    for(int i = 0; i < numReadings; i++) {
        delay(100);                         // Wait for sensor to settle

        // Get new reading
        int16_t reading = (*adc).readADC_SingleEnded(outputPin);

        int percentage = map(reading, upperBound, lowerBound, 100, 0);
        percentageSum += percentage;    // Add current percentage to the sum

        delay(25);                          // Wait between readings
    } // for

    // Get average reading value
    averageReading = percentageSum / numReadings;

    // Safety net (values within bounds)
    safeValues(&averageReading);

    return averageReading;
} // readHumidity()

//-----------------------------------------------------------------------
// One humidity reading. Return the voltage
//-----------------------------------------------------------------------
float readHumidity_V(Adafruit_ADS1115* adc, int outputPin) {

    // Get new reading
    int16_t reading = (*adc).readADC_SingleEnded(outputPin);

    return reading;
} // readHumidity()


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
