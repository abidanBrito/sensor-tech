/*  ------------------------------------------------------------------------
    AUTHOR:         Abidan Brito Clavijo
    FILE:           REST_Server.h
    DATE:           28/12/2019
    STATE:          DONE
    FUNCTIONALITY:  REST server API. It is set to use ThingSpeak by default.
                    It can, however, be changed to use Dweet. Both GET and
                    POST methods are supported.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */

#ifndef REST_SERVER_API_H
#define REST_SERVER_API_H

//// WIFI LIBRARY ////
#include <ESP8266WiFi.h>

// NOTE(abi): Comment / uncomment for logging purposes.
#define PRINT_DEBUG_MESSAGES    // Serial Monitor
//#define PRINT_HTTP_RESPONSE     // HTTP Server response

// NOTE(abi): Comment / uncomment to connect to UPV / local wireless network.
//#define WiFi_CONNECTION_UPV

// NOTE(abi): Pick REST server. Comment the one to be used; uncomment the other.
#define REST_SERVER_THINGSPEAK  // ThingSpeak
//#define REST_SERVER_DWEET       // Dweet

// Fields to be sent to REST server. It must be contained in [1, 8].
#define NUM_FIELDS_TO_SEND 2

//// PIN DEFINITIONS ////
const int LED_PIN = 5;          // Thing Dev's onboard (green LED).

//// WIFI DEFINITIONS ////
// --------------------------------------------------------------------------------
// UPV connection
#ifdef WiFi_CONNECTION_UPV
const char WiFiSSID[] = "GTI1";
const char WiFiPSK[] = "1PV.arduino.Toledo";

// External connection
#else
const char WiFiSSID[] = "YourSSID";
const char WiFiPSK[] = "YourPassWord";
#endif
// --------------------------------------------------------------------------------

//// SERVER DEFINITIONS ////
// --------------------------------------------------------------------------------
WiFiClient client;  // WiFi client object declaration.

// UPV connection
#if defined(WiFi_CONNECTION_UPV)
const char Server_Host[] = "proxy.upv.es";
const int Server_HttpPort = 8080;

// External connection
#elif defined(REST_SERVER_THINGSPEAK)
const char Server_Host[] = "api.thingspeak.com";
const int Server_HttpPort = 80;
#else
const char Server_Host[] = "dweet.io";
const int Server_HttpPort = 80;
#endif
// --------------------------------------------------------------------------------

//// HTTP REST CONNECTION ////
// --------------------------------------------------------------------------------
#ifdef REST_SERVER_THINGSPEAK
const char Rest_Host[] = "api.thingspeak.com";
String MyWriteAPIKey="GX1NF0HUTYUTSXVC";  // ThingSpeak API write key.
#else
const char Rest_Host[] = "dweet.io";
String MyWriteAPIKey="cdiocurso2019g02";  // Dweet API write key.
#endif
// --------------------------------------------------------------------------------

//// WIFI CONNECTION ////
// This function establishes the WiFi connection.
void connectWiFi() {
    byte ledStatus = LOW;

#ifdef PRINT_DEBUG_MESSAGES
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());
#endif

    WiFi.begin(WiFiSSID, WiFiPSK);

    while (WiFi.status() != WL_CONNECTED) {
        // Blink LED
        digitalWrite(LED_PIN, ledStatus); // Write LED (HIGH/LOW)
        ledStatus = (ledStatus == HIGH) ? LOW : HIGH;
#ifdef PRINT_DEBUG_MESSAGES
        Serial.println(".");
#endif
        delay(500);
    }

#ifdef PRINT_DEBUG_MESSAGES
    Serial.println("WiFi Connected");
    Serial.println(WiFi.localIP()); // Print IP address
#endif
}

//// HTTP POST (ThingSpeak) ////
// This function constructs the data string to be sent to ThingSpeak via HTTP POST
// method. It sends "numFields" fields from "fieldData" array.
//
// NOTE(abi): Make sure to adjust "numFields" to the right number of fields.
// Likewise, enable as many fields in your web channel.
void HTTPPost(String fieldData[], int numFields) {
    if(client.connect(Server_Host , Server_HttpPort)) {
        // Build data string.
        // NOTE(abi): If you have multiple fields, make sure not to exceed 1440 characters.
        String PostData = "api_key=" + MyWriteAPIKey;
        for(int field = 1; field <= numFields; field++) {
            PostData += "&field" + String(field) + "=" + fieldData[field];
        }

        // POST data via HTTP
#ifdef PRINT_DEBUG_MESSAGES
        Serial.println("Connecting to ThingSpeak for update...");
#endif
        client.println("POST http://" + String(Rest_Host) + "/update HTTP/1.1");
        client.println("Host: " + String(Rest_Host));
        client.println("Connection: close");
        client.println("Content-Type: application/x-www-form-urlencoded");
        client.println("Content-Length: " + String( PostData.length()));
        client.println();
        client.println(PostData);

#ifdef PRINT_DEBUG_MESSAGES
        Serial.println(PostData);
        Serial.println();

        // HTTP server response log
    #ifdef PRINT_HTTP_RESPONSE
        delay(500);
        Serial.println();
        while(client.available()) {
            String line = client.readStringUntil('\r');
            Serial.print(line); }
        Serial.println();
        Serial.println();
    #endif
#endif
    }
}

//// HTTP GET (ThingSpeak or Dweet) ////
// This function constructs the data string to be sent to the server via the HTTP GET
// method. It sends "numFields" fields from "fieldData" array.
//
// NOTE(abi): Make sure to adjust "numFields" to the right number of fields.
// Likewise, enable as many fields in your web channel.
void HTTPGet(String fieldData[], int numFields) {
    if(client.connect(Server_Host , Server_HttpPort)) {
#ifdef REST_SERVER_THINGSPEAK
        String PostData = "GET https://api.thingspeak.com/update?api_key=";
        PostData += MyWriteAPIKey;
#else
        String PostData = "GET http://dweet.io/dweet/for/";
        PostData += MyWriteAPIKey + "?";
#endif

        for(int field = 1; field <= numFields; field++){
            PostData += "&field" + String(field) + "=" + fieldData[field];
        }

#ifdef PRINT_DEBUG_MESSAGES
        Serial.println("Connecting to Server for update...");
#endif
        client.print(PostData);
        client.println(" HTTP/1.1");
        client.println("Host: " + String(Rest_Host));
        client.println("Connection: close");
        client.println();

#ifdef PRINT_DEBUG_MESSAGES
        Serial.println(PostData);
        Serial.println();

    // HTTP Server response log
    #ifdef PRINT_HTTP_RESPONSE
        delay(500);
        Serial.println();
        while(client.available()) {
            String line = client.readStringUntil('\r');
            Serial.print(line);
        }
        Serial.println();
        Serial.println();
    #endif
#endif
    }
}

//// HTTP SETUP ////
// This function configures the HTTP server.
// It gets called from setup().
void setupHTTP() {
#ifdef PRINT_DEBUG_MESSAGES
    Serial.begin(9600);
#endif

    connectWiFi();
    digitalWrite(LED_PIN, HIGH);

#ifdef PRINT_DEBUG_MESSAGES
    Serial.print("Server_Host: ");
    Serial.println(Server_Host);
    Serial.print("Port: ");
    Serial.println(String(Server_HttpPort));
    Serial.print("Server_Rest: ");
    Serial.println(Rest_Host);
#endif
}

//// DEBUG DATA ////
// This function prints out the data pointed by "index" from "data[]" into the
// Serial Monitor.
void debugDATA( String data[], const unsigned int index, const char* strLiteral) {
#ifdef PRINT_DEBUG_MESSAGES
    Serial.print(strLiteral);
    Serial.print(" = ");
    Serial.println(data[index]);
#endif
}

//// HTTP LOOP ////
// This function fills in the data string given the given sensor readings. It then
// sends it to ThingSpeak or Dweet, using either the GET or POST method.
// It gets called from loop().
void loopHTTP(double& salinity, double& humidity, double& temperature,
              double& luminosity, double& barometricPressure, double& rainfall,
              double& longitude, double& latitude) {
    // Up to 8 cells (maximum)
    String data[NUM_FIELDS_TO_SEND + 1];

    data[1] = String(salinity);
    debugData(data, 1, "SALINITY");

    data[2] = String(humidity);
    debugData(data, 2, "HUMIDITY");

    data[3] = String(temperature);
    debugData(data, 3, "TEMPERATURE");

    data[4] = String(luminosity);
    debugData(data, 4, "LUMINOSITY");

    data[5] = String(barometricPressure);
    debugData(data, 5, "BAROMETRIC PRESSURE");

    data[6] = String(rainfall);
    debugData(data, 6, "RAINFALL");

    data[7] = String(longitude);
    debugData(data, 7, "LONGITUDE");

    data[8] = String(latitude);
    debugData(data, 8, "LATITUDE");

    // NOTE(abi): Pick method: GET(ThingSpeak or Dweet) or POST(ThingSpeak).
    HTTPGet(data, NUM_FIELDS_TO_SEND);
    //HTTPPost(data, NUM_FIELDS_TO_SEND);
}

#endif
