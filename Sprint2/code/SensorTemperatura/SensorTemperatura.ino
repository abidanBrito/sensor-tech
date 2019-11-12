/*  ------------------------------------------------------------------------
    AUTHOR:        Abidan Brito, Elvira Montagud, Luis Belloch, Pablo Enguix
    FILE:          mainProgram.ino
    DATE:          29/10/2019
    STATE:         DONE
    FUNCTIONALITY: This is the main file that is to be executed. It can be
                   thought of as the center of the codebase.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019. All rights reserved.
    ------------------------------------------------------------------------ */

//// IMPORT EXTERNAL LIBRARIES ////
#include <Wire.h>
#include <Adafruit_ADS1015.h>

// Create an ADC object
Adafruit_ADS1115 ads1115(0x48);

//// MACRO DEFINITIONS ////
#define POWER_PIN       13      // Power pin NTC sensor

void setup() {
    // Set data rate for serial data transmission
    Serial.begin(9600);

    // Turn on ADS1115
    ads1115.begin();

    // Gain (ADC Range) -> +/- 4.096 V (1 bit = 2 mV)
    ads1115.setGain(GAIN_ONE);
} // setup()

float readVoltageTemperature(int numReadings, int outputPin){
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

    return averageReading;
} // readTemperature()

void loop() {
    float voltageReading = 0.0, temperatureReading = 0.0;

    // Find temperature
    voltageReading = readVoltageTemperature(5, 2);
    temperatureReading = voltageToTemperature(voltageReading);

    // Print out result
    Serial.println(voltageReading);         // Volts
    Serial.println(temperatureReading);     // Degrees Celsius
    delay(1000);
} // loop()

float voltageToTemperature(float voltage) {
    float temperature;
    float y_Intercept = 0.786;
    float slope = 0.0348;
    float d_Temp = -0.24;

    // Apply formula
    temperature = ((voltage - y_Intercept) / slope) + d_Temp;

    return temperature;
} // voltageToTemperature()

