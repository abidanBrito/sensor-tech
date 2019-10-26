/*  ------------------------------------------------------------------------
    AUTHOR:        Abidan Brito, Elvira Montagud, Luis Belloch, Pablo Enguix
    FILE:          UnionHumedadSalinidad.ino
    DATE:          25/10/2019
    STATE:         DONE
    FUNCTIONALITY: Describe what this file is used for.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019. All rights reserved.
    ------------------------------------------------------------------------ */

//// IMPORT EXTERNAL LIBRARIES ////
#include <Wire.h>
#include <Adafruit_ADS1015.h>       // ADS library

//// MACRO DEFINITIONS ////
#define POWER_PIN                   5           // Digital I/O
#define INPUT_PIN_SALINITY          0           // Input salinity pin
#define INPUT_PIN_HUMIDITY          1           // Input humidity pin
#define SALINITY_NUM_READINGS       10          // Number of salinity readings
#define HUMIDITY_NUM_READINGS       10          // Number of salinity readings
#define SALINITY_RANGE_LOW          1450        // Salinity threshold in water (lower bound)
#define SALINITY_RANGE_HIGH         6250        // Salinity threshold in water (upper bound)
#define HUMIDITY_RANGE_LOW          1700        // Humidity threshold -> Dry value (lower bound)
#define HUMIDITY_RANGE_HIGH         400         // Humidity threshold -> Soaked value (upper bound)
#define DEEP_SLEEP_TIME             60000000    // Hibernating time

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
    printSensorReading(meanSalinity, "Salinity");

    // Humidity measure
    float meanHumidity = readHumidity(HUMIDITY_NUM_READINGS);
    printSensorReading(meanHumidity, "Humidity");

    // Hibernate for a minute
    //ESP.deepSleep(DEEP_SLEEP_TIME);

    // Hold on for a minute
    delay(1000);
} // loop()

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

        // Returns '16-bit int' (using ' 32-bit int' to prevent overflow)
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

//-----------------------------------------------------------------------
// Several humidity readings. Return the average
//-----------------------------------------------------------------------
int readHumidity(int numReadings) {
    float averageReading = 0.0, humidityPercentage = 0.0;
    int sum = 0;

    for(int i = 0; i < numReadings; i++) {
        // Returns '16-bit int' (using ' 32-bit int' to prevent overflow)
        int16_t dato = ads1115.readADC_SingleEnded(INPUT_PIN_HUMIDITY);

        sum += 100*HUMIDITY_RANGE_LOW/(HUMIDITY_RANGE_LOW-HUMIDITY_RANGE_HIGH)-dato*100/(HUMIDITY_RANGE_LOW-HUMIDITY_RANGE_HIGH);

        delay(10);  //  Wait between readings
    } // for

    // Get average reading value
    averageReading = sum / numReadings;

    // Get percentage
    humidityPercentage = map(averageReading, HUMIDITY_RANGE_LOW,
                                    HUMIDITY_RANGE_HIGH, 100, 0);

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