#ifndef TEMPERATURE_H
#define TEMPERATURE_H

//// DEPENDENCIES ////
#include "System_Configuration.h"

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

//-----------------------------------------------------------------------
// One temperature reading. Return the voltage
//-----------------------------------------------------------------------
float readTemperature_V(Adafruit_ADS1115* adc) {

    int16_t reading = (*adc).readADC_SingleEnded(outputPin);

    return reading;
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

#endif
