/*  ------------------------------------------------------------------------
    AUTHOR:         Abidan Brito Clavijo
    FILE:           Sensors.h
    DATE:           06/01/2020
    STATE:          DONE
    FUNCTIONALITY:  Miscellaneous library used by sensor objects.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */
#ifndef SENSORS_H
#define SENSORS_H

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

//// OBJECT DECLARATION ////
Adafruit_BMP280 bmp;    // Sensor object - I2C interface

//// MACRO DEFINITIONS ////
#define POWER_PIN_SALINITY      5
#define OUTPUT_PIN_SALINITY     0
#define OUTPUT_PIN_HUMIDITY     1
#define OUTPUT_PIN_TEMPERATURE  2
#define OUTPUT_PIN_LUMINOSITY   3
#define LOWER_BOUND_SALINITY    1150
#define LOWER_BOUND_HUMIDITY    20050
#define UPPER_BOUND_SALINITY    22000
#define UPPER_BOUND_HUMIDITY    10100
#define Y_INTERCEPT             0.786
#define SLOPE                   0.0348
#define D_TEMP                  -0.24
#define NUM_READINGS            5
#define ECHO_PIN_RAINGAUGE      0
#define TAZA_ASUN_ML            402.12

// ----------------------------------------------------------------------
// Print out the received data into the Serial Monitor.
// ----------------------------------------------------------------------
void printSensorReading(double measureValue, char* strLiteral, char* strUnit) {
    Serial.print(strLiteral);
    Serial.print(" = ");
    Serial.print(measureValue);
    Serial.print(" ");
    Serial.println(strUnit);
}

void bmp280_setup(void) {
    // Check communication with the sensor
    if (!bmp.begin()) {
        Serial.println("BMP280 sensor could not be found!");
        // Stop program flow with infinite loop
        while (1);
    }
    else {
        Serial.println("BMP280 sensor found!");
    }

    // Default settings from datasheet
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,       // Operating Mode
                    Adafruit_BMP280::SAMPLING_X2,       // Temperature oversampling
                    Adafruit_BMP280::SAMPLING_X16,      // Pressure oversampling
                    Adafruit_BMP280::FILTER_X16,        // Filtering
                    Adafruit_BMP280::STANDBY_MS_500);   // Standby time
}

void bmp280_loop() {
    // Pressure
    float pressure = bmp.readPressure() / 100;
    Serial.print("Pressure\t=\t");
    Serial.print(pressure); // hPa (unit)
    Serial.println(" (hPa)");

    // Altitude
    Serial.print("Altitude\t=\t");
    Serial.print(bmp.readAltitude(pressure + 1));
    Serial.println(" (m)");

    // Temperature
    Serial.print("Temperature\t=\t");
    Serial.print(bmp.readTemperature());
    Serial.println(" (ºC)");

    // Line break to separate readings
    Serial.println();
}

double bmp280Pressure() {
    double pressure = bmp.readPressure() / 100;

    return pressure;
}

double bmp280Altitude() {
    double pressure = bmp.readPressure() / 100;
    double altitude = bmp.readAltitude(pressure + 1);

    return altitude;
}

double bmp280Temperature() {
    double temperature = bmp.readTemperature();

    return temperature;
}

#endif
