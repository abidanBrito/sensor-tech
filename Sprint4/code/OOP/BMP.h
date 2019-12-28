#ifndef BMP_H
#define BMP_H

//// DEPENDENCIES ////
#include "System_Configuration.h"

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

#endif
