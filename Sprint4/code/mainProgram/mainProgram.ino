/*  ------------------------------------------------------------------------
    AUTHOR:        Abidan Brito Clavijo
    FILE:          mainProgram.ino
    DATE:          10/12/2019
    STATE:         DONE
    FUNCTIONALITY: This is the main file that is to be executed. It can be
                   thought of as the center of the codebase.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019. All rights reserved.
    ------------------------------------------------------------------------ */

//// IMPORT EXTERNAL LIBRARIES ////
#include "System_Configuration.h"  // System configuration
#include "Interruptions.h"         // Wake on motion & Deep Sleep
#include "Sensors.h"               // Analog and digital sensors
#include "GPS_A2235.h"             // GPS receiver

//// MACROS ////
#define HIBERNATION_TIME    10

//----------------------------------------------------------------------
// Initial configuration
//----------------------------------------------------------------------
void setup() {
    // System configuration
    init_setup();

    // GPS receiver configuration
    setupGPS();

    // Pressure sensor configuration
    bmp280_setup(&bmp);

    // Interruptions configuration
    wakeOnMotion_setup();
} // setup()

//----------------------------------------------------------------------
// Runtime execution
//----------------------------------------------------------------------
void loop() {
    // Salinity measure
    float meanSalinity = readSalinityV2(&adc, POWER_PIN_SALINITY, OUTPUT_PIN_SALINITY,
                                        LOWER_BOUND_SALINITY, UPPER_BOUND_SALINITY, NUM_READINGS);
    printSensorReading(meanSalinity, "Salinity");

    // Humidity measure
    float meanHumidity = readHumidity(&adc, OUTPUT_PIN_HUMIDITY, LOWER_BOUND_HUMIDITY,
                                      UPPER_BOUND_HUMIDITY, NUM_READINGS);
    printSensorReading(meanHumidity, "Humidity");
    Serial.println();

    // Temperature measure
    float meanTemperature = readTemperature(&adc, NUM_READINGS, OUTPUT_PIN_TEMPERATURE,
                                            Y_INTERCEPT, SLOPE, D_TEMP);
    printTemperature(meanTemperature);
    Serial.println();

    // Light intensity sensor
    unsigned int lightState = readVoltageLight(&adc, OUTPUT_PIN_LUMINOSITY);
    printLightState(lightState);

    // Barometric pressure / Altitude measures
    bmp280_loop(&bmp);

    // Geolocation (NMEA messages)
    loopGPS();

    // Hibernation mode
    deepSleep_loop(HIBERNATION_TIME);
} // loop()