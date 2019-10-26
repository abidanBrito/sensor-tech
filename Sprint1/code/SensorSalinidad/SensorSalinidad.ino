/*  ------------------------------------------------------------------------
    AUTHOR:        Abidan Brito, Elvira Montagud, Luis Belloch, Pablo Enguix
    FILE:          SensorSalinidad.ino
    DATE:          22/10/2019
    STATE:         DONE
    FUNCTIONALITY: Describe what this file is used for.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019. All rights reserved.
    ------------------------------------------------------------------------ */

//// IMPORT EXTERNAL LIBRARIES ////
#include <Wire.h>
#include <Adafruit_ADS1015.h>       // ADS library

//// MACRO DEFINITIONS ////
#define POWER_PIN                   5     // Digital I/O
#define INPUT_PIN_SALINITY          0     // Input
#define SALINITY_NUM_READINGS       10    // Number of salinity readings
#define SALINITY_RANGE_LOW          1450  // Salinity threshold in water (lower bound)
#define SALINITY_RANGE_HIGH         6250  // Salinity threshold in water (upper bound)

// Create an ADC object
Adafruit_ADS1115 ads1115(0x48);     // Defined at address '0x48'

//----------------------------------------------------------------------
// Initial configuration
//----------------------------------------------------------------------
void setup() {
    // Set data rate for serial data transmission
    Serial.begin(9600);

    // Turn on ADS1115
    ads1115.begin();

    // Gain (ADC Range) -> +/- 4.096 V (1 bit = 2 mV)
    ads1115.setGain(GAIN_ONE);
} // setup()

//----------------------------------------------------------------------
// Runtime execution
//----------------------------------------------------------------------
void loop() {
    // Salinity measure
    float meanSalinity = readSalinityV2(SALINITY_NUM_READINGS);
    printSalinityReading(meanSalinity);

    // Stand by for 3 seconds
    delay(3000);
} // loop()

//----------------------------------------------------------------------
// Return single salinity reading
//----------------------------------------------------------------------
float readSalinityV1(int power_pin) {
    //  Float for precision and prevent overflow
    float salinityPercentage = 0.0;
    int16_t reading = 0;

    digitalWrite(POWER_PIN, HIGH);                                  //  Supply power to the sensor
    delay(100);                                                     //  Wait for sensor to settle
    reading = ads1115.readADC_SingleEnded(INPUT_PIN_SALINITY);      //  Store measured reading in 'res'
    digitalWrite(POWER_PIN, LOW);                                   //  Turn off power to the sensor

    // Get percentage
    salinityPercentage = map(reading, SALINITY_RANGE_LOW,
                                SALINITY_RANGE_HIGH, 0, 100);

    return reading;
} // readSalinityV1()

//----------------------------------------------------------------------
// Several salinity readings. Return the average
//----------------------------------------------------------------------
float readSalinityV2(int numReadings) {
    //  Float for precision and prevent overflow
    float averageReading = 0.0, salinityPercentage = 0.0;
    int sum = 0;

    for (int i = 0; i < numReadings; i++) {
        digitalWrite(POWER_PIN, HIGH);                           //  Supply power to the sensor
        delay(100);                                              //  Wait for sensor to settle

        // Returns '16-bit int' (using ' 32-bit int' to avoid overflow)
        sum += ads1115.readADC_SingleEnded(INPUT_PIN_SALINITY);  //  Add reading to the running sum
        digitalWrite(POWER_PIN, LOW);                            //  Turn off power to the sensor
        delay(10);                                               //  Wait between readings
    } // for

    // Get average reading value
    averageReading = sum / numReadings;

    // Get percentage
    salinityPercentage = map(averageReading, SALINITY_RANGE_LOW,
                                SALINITY_RANGE_HIGH, 0, 100);

    return salinityPercentage;
} // readSalinityV2()

//----------------------------------------------------------------------
// Print out received data into the Serial Monitor
//----------------------------------------------------------------------
void printSalinityReading(float salinityValue) {
    float salinityPercentage = map(salinityValue, SALINITY_RANGE_LOW,
                                     SALINITY_RANGE_HIGH, 0, 100);

    // Avoid negative values when electrodes are in the air
    if (salinityPercentage < 0) {
        salinityPercentage = 0;
    }

    // Print out measure in new range
    Serial.print("Salinity percentage: ");
    Serial.print(salinityPercentage);
    Serial.println(" %");
} // printSalinityReading()