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

    // REST server configuration.
    setupHTTP();

    // Pressure sensor configuration.
    bmpOBJ.setup();

    // Interruptions configuration.
    wakeOnMotion_setup();
}

//----------------------------------------------------------------------
// Runtime execution.
//----------------------------------------------------------------------
void loop() {
    // Salinity measure.
    double const meanSalinity = salinityOBJ.getSalinity();
    printSensorReading(meanSalinity, "Salinity", "%");

    // Humidity measure.
    double const meanHumidity = humidityOBJ.getHumidity();
    printSensorReading(meanHumidity, "Humidity", "%");
    Serial.println();

    // Temperature measure.
    double const temperature = tempOBJ.getTemperature();
    printSensorReading(temperature, "Temperature", "º C");
    Serial.println();

    // Light intensity measure.
    unsigned int const lightState = lightOBJ.getLuminosityState();
    lightOBJ.printLightState();

    // Rainfall measure.
    double const rainfall = rainOBJ.getRainfall();
    printSensorReading(rainfall, "Vase volume", "l");
    Serial.println();

    // Barometric pressure / Altitude measures.
    double const barometricPressure = bmpOBJ.getPressure();
    double const altitude = bmpOBJ.getAltitude();
    bmpOBJ.printReadings();

    // Send data over to the server.
    loopHTTP(meanSalinity, meanHumidity, temperature,
             lightState, barometricPressure, altitude,
             rainfall);

    // Geolocation (NMEA messages).
    loopGPS();

    // Hibernation mode.
    deepSleep_loop(HIBERNATION_TIME);
}
