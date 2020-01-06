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

//// MACRO DEFINITIONS ////
#define POWER_PIN_SALINITY      5
#define OUTPUT_PIN_SALINITY     0
#define OUTPUT_PIN_HUMIDITY     1
#define OUTPUT_PIN_TEMPERATURE  2
#define OUTPUT_PIN_LUMINOSITY   3
#define LOWER_BOUND_SALINITY    1150
#define UPPER_BOUND_SALINITY    22000
#define LOWER_BOUND_HUMIDITY    20200
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
    Serial.println(" ");
    Serial.println(strUnit);
}

#endif
