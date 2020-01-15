/*  ------------------------------------------------------------------------
    AUTHOR:        Abidan Brito Clavijo
    FILE:          mainProgram.ino
    DATE:          06/01/2020
    STATE:         DONE
    FUNCTIONALITY: This is the main file that is to be executed. It can be
    thought of as the center of the codebase.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019. All rights reserved.
    ------------------------------------------------------------------------ */

//// IMPORT EXTERNAL LIBRARIES ////
#include "System_Configuration.h"  // System configuration.
#include "Sensors.h"               // Sensor-related miscellaneous.
#include "Interruptions.h"         // Wake on Motion & Deep Sleep.
#include "REST_Server.h"           // REST Server API.
#include "GPS_A2235.h"             // GPS receiver.

//----------------------------------------------------------------------
// Initial configuration.
//----------------------------------------------------------------------
void setup() {
    // Initial system configuration.
    init_setup();

    // GPS receiver configuration.
    setupGPS();

    // Pressure sensor configuration.
    bmp280_setup();

    // REST server configuration.
    setupHTTP();

    // Interruptions configuration.
    wakeOnMotion_setup();
}

//----------------------------------------------------------------------
// Runtime execution.
//----------------------------------------------------------------------
void loop() {
    // Salinity measure.
    double meanSalinity = salinityOBJ.getSalinity();

    // Humidity measure.
    double meanHumidity = humidityOBJ.getHumidity();

    // Temperature measure.
    double temperature_v1 = tempOBJ.getTemperature();

    // Light intensity measure.
    unsigned int lightState = lightOBJ.getLuminosityState();
    lightOBJ.printLightState();
    lightOBJ.printCalibrationReading();

    // Rainfall measure.
    double rainfall = rainOBJ.getRainfall();
    printSensorReading(rainfall, "Vase volume", "l");
    Serial.println();

    // Barometric pressure / Altitude measures.
    double barometricPressure = bmp280Pressure();
    double altitude = bmp280Altitude();
    double temperature_v2 = bmp280Temperature();
    bmp280_loop();

    // Send data over to the server.
    loopHTTP(meanSalinity, meanHumidity, temperature_v1,
             lightState, barometricPressure, altitude,
             rainfall);

    humidityOBJ.printCalibrationReading();

    // Geolocation (NMEA messages).
    loopGPS();

    // Hibernation mode.
    deepSleep_loop(HIBERNATION_TIME);
}
