/*  ------------------------------------------------------------------------
    AUTHOR:         Abidan Brito Clavijo
    FILE:           GPS_A2235.h
    DATE:           10/12/2019
    STATE:          DONE
    FUNCTIONALITY:  Internal library to set up and read NMEA messages from
                    the A2235-H GPS receiver.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */

//// USAGE INSTRUCTIONS ////
/***************************************************
    - Connect RXI to pin 12 on the MCU (ESP8266).
    - Connect TXO to pin 13 on the MCU (ESP8266).
    - Connect pin 15 to pin 15 on the MCU (ESP8266).
****************************************************/

#ifndef GPS_A2235_H
#define GPS_A2235_H

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

//// MACROS ////
#define RX_PIN      12      // GPS RXI
#define TX_PIN      13      // GPS TX0
#define INIT_PIN    15      // GPS init pin
#define GPS_BAUD    4800    // Serial communication speed

//// OBJECT DECLARATIONS ////
TinyGPSPlus gps;                               // GPS object
SoftwareSerial softwareSerial(RX_PIN, TX_PIN); // Virtual UART (software)

//// FUNCTIONS ////
static void smartDelay(unsigned long ms) {
    unsigned long start = millis();
    do {
        while(softwareSerial.available()) {
            // Read from GPS
            gps.encode(softwareSerial.read());
        }
    } while((millis() - start) < ms);
}

// Turn GPS on/off by sending a rectangular pulse through the signal
void switchOnOff() {
    digitalWrite(INIT_PIN, LOW);
    delay(200);
    digitalWrite(INIT_PIN, HIGH);
    delay(200);
    digitalWrite(INIT_PIN, LOW);
}

void setupGPS() {
    Serial.begin(9600);             // Communication stream with IDE serial monitor (USB)
    softwareSerial.begin(GPS_BAUD); // Communication stream with the GPS (software)

    // Turn the GPS ON/OFF
    pinMode(INIT_PIN, OUTPUT);
    switchOnOff();

    // Print out data stream format with units (NMEA message)
    Serial.println("----------------------------------------------------------------------------------------------------------");
    Serial.println("DATE (MM/DD/YY)  TIME (HH:MM:SS)  LATITUDE (deg)  LONGITUDE (deg) ALTITUDE (ft)  COURSE (deg)  SPEED (mph)");
    Serial.println("----------------------------------------------------------------------------------------------------------");
}

void loopGPS() {
    char gpsDate[10];
    char gpsTime[10];

    // Check for NMEA messages
    if(gps.location.isValid()) {
        // Date data string
        sprintf(gpsDate, "%d/%d/%d", gps.date.month(), gps.date.day(), gps.date.year());

        // Time data string
        sprintf(gpsTime, "%d:%d:0%d", gps.time.hour(), gps.time.minute(), gps.time.second());

        // Print out data stream format (NMEA message)
        Serial.print("DATE\t");
        Serial.print("\tTIME\t");
        Serial.print("\tLATITUDE\t");
        Serial.print("LONGITUDE\t");
        Serial.print("ALTITUDE\t");
        Serial.print("COURSE\t");
        Serial.println("\tSPEED");

        // Print out received data
        Serial.print(gpsDate);
        Serial.print("\t");
        Serial.print(gpsTime);
        Serial.print("\t");
        Serial.print(gps.location.lat(), 6);
        Serial.print("\t");
        Serial.print(gps.location.lng(), 6);
        Serial.print("\t");
        Serial.print(gps.altitude.feet());
        Serial.print("\t\t");
        Serial.print(gps.course.deg(), 2);
        Serial.print("\t\t");
        Serial.println(gps.speed.mph(), 2);
    }

    // No NMEA messages
    else {
        Serial.print("Satellites in view: ");
        Serial.println(gps.satellites.value());
    }

    // Line break between readings
    Serial.println();

    // Wait between readings
    smartDelay(3000);
}

#endif