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
#include "Sensores.h"              // Analog sensors library
#include "GPS_A2235.h"             // GPS receiver library

//----------------------------------------------------------------------
// Initial configuration
//----------------------------------------------------------------------
void setup() {
    // Set data rate for serial data transmission
    Serial.begin(9600);

    // Turn on ADS1115
    adc.begin();

    // Gain (ADC Range) -> +/- 4.096 V (1 bit = 2 mV)
    adc.setGain(GAIN_ONE);

    // Set power pins mode
    pinMode (POWER_PIN_HUMIDITY, OUTPUT);
    pinMode (POWER_PIN_SALINITY, OUTPUT);

    // GPS receiver
    setupGPS();

    // Pressure sensor
    bmp280_setup(&bmp);
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

    // Pressure sensor
    bmp280_loop(&bmp);

    // GPS receiver
    loopGPS();

    // TODO(abi): wake on motion as well
    // Hibernate for a minute
    // ESP.deepSleep(DEEP_SLEEP_TIME * 1000000);

    // Hold on for a second
    delay(1000);
} // loop()