/*  ------------------------------------------------------------------------
    AUTHOR:        Abidan Brito
    FILE:          Sensors.h
    DATE:          10/12/2019
    STATE:         DONE
    FUNCTIONALITY: Internal library containing all sensor-related functions.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */

#ifndef SENSORES_H
#define SENSORES_H

//// DEPENDENCIES ////
#include "System_Configuration.h"

//// FUNCTION PROTOTYPES ////
void safeValues(float* reading);
float voltageToTemperature(float voltage, float yIntercept, float slope, float dTemp);

//----------------------------------------------------------------------
// Several salinity readings. Return the average
//----------------------------------------------------------------------
float readSalinityV2(Adafruit_ADS1115* adc, int powerPin, int inputPin,
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
} // readSalinityV2()

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

//-----------------------------------------------------------------------
// Several temperature readings. Return the average
//-----------------------------------------------------------------------
float readTemperature(Adafruit_ADS1115* adc, int numReadings, int outputPin,
                      float y_Intercept, float slope, float d_Temp) {
    float averageReading = 0.0f;
    int16_t sum = 0;

    for(int i = 0; i < numReadings; i++) {
        sum += (*adc).readADC_SingleEnded(outputPin);
        delay(10);
    }

    // Get average reading value
    averageReading = (sum / numReadings);

    // Convert it to (0 - 4.096 V) range
    averageReading = (float) map(averageReading, 0, 32768, 0, 4096) / 1000;

    // Transform value from voltaje to temperature
    float temperature = - (voltageToTemperature(averageReading, y_Intercept, slope, d_Temp));

    return temperature;
} // readTemperature()

float voltageToTemperature(float voltage, float y_Intercept, float slope, float d_Temp) {
    float temperature = 0.0f;

    // Apply formula
    temperature = ((voltage - y_Intercept) / slope) + d_Temp;

    return temperature;
} // voltageToTemperature()

void printTemperature(float temperature) {
    Serial.print("Temperature = ");
    Serial.print(temperature);
    Serial.println(" (ºC)");
} // printTemperature()

unsigned int readVoltageLight(Adafruit_ADS1115* adc, int outputPin) {
    int16_t reading = 0;
    unsigned int voltage = 0;

    reading = (*adc).readADC_SingleEnded(outputPin);

    // Convert it to (0 - 4.096 V) range
    voltage = map(reading, 0, 32768, 0, 4096);

    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println(" (mV)");

    if(voltage <= 30) {
        return 0;
    }
    else if (voltage <= 3700) {
        if(voltage <= 150) {
            return 1;
        }
        else if (voltage < 1500) {
            return 2;
        }
        else {
            return 3;
        }
    }
} // readVoltageLight()

void printLightState(unsigned int lightState) {
    //Print out result
    Serial.print("Intensidad de luz: ");
    if(lightState == 0) {
        Serial.println("está oscuro.");
    }
    else if(lightState == 1) {
        Serial.println("está nublado o en sombra.");
    }
    else if(lightState == 2) {
        Serial.println("está despejado.");
    }
    else {
        Serial.println("está soleado.");
    }
    Serial.println();
} // lightState()

void bmp280_setup(Adafruit_BMP280* bmp) {
    // Check communication with the sensor
    if (!(*bmp).begin()) {
        Serial.println("BMP280 sensor could not be found!");
        // Stop program flow with infinite loop
        while (1);
    }
    else {
        Serial.println("BMP280 sensor found!");
    }

    // Default settings from datasheet
    (*bmp).setSampling(Adafruit_BMP280::MODE_NORMAL,       // Operating Mode
                       Adafruit_BMP280::SAMPLING_X2,       // Temperature oversampling
                       Adafruit_BMP280::SAMPLING_X16,      // Pressure oversampling
                       Adafruit_BMP280::FILTER_X16,        // Filtering
                       Adafruit_BMP280::STANDBY_MS_500);   // Standby time
}

void bmp280_loop(Adafruit_BMP280* bmp) {
    // Pressure
    float pressure = (*bmp).readPressure() / 100;
    Serial.print("Pressure\t=\t");
    Serial.print(pressure); // hPa (unit)
    Serial.println(" (hPa)");

    // Altitude
    Serial.print("Altitude\t=\t");
    Serial.print((*bmp).readAltitude(pressure + 1));
    Serial.println(" (m)");

    // Temperature
    Serial.print("Temperature\t=\t");
    Serial.print((*bmp).readTemperature());
    Serial.println(" (ºC)");

    // Line break to separate readings
    Serial.println();
}

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
