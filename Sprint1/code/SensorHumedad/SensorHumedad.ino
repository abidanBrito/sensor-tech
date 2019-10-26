/*  ------------------------------------------------------------------------
    AUTHOR:        Abidan Brito, Elvira Montagud, Luis Belloch, Pablo Enguix
    FILE:          SensorHumedad.ino
    DATE:          22/10/2019
    STATE:         DONE
    FUNCTIONALITY: Describe what this file is used for.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019. All rights reserved.
    ------------------------------------------------------------------------ */

//// IMPORT EXTERNAL LIBRARIES ////
#include <Wire.h>
#include <Adafruit_ADS1015.h>       // ADS library

//// MACRO DEFINITIONS ////
#define POWER_PIN                   5     // Digital I/O
#define INPUT_PIN_HUMIDITY          0     // Input
#define HUMIDITY_RANGE_LOW          1700  // Humidity threshold -> Dry value (lower bound)
#define HUMIDITY_RANGE_HIGH         400   // Humidity threshold -> Soaked value (upper bound)

// Create an ADC object
Adafruit_ADS1115 ads1115(0x48);     // Defined at address '0x48'

//----------------------------------------------------------------------
// Initial configuration
//----------------------------------------------------------------------
void setup() {
    // Set data rate for serial data transmission
    Serial.begin(9600);

    // Turn on ADS1115
    ads1115.begin();

    // Gain (ADC Range) -> +/- 4.096 V (1 bit = 2 mV)
    ads1115.setGain(GAIN_ONE);
} // setup()

//----------------------------------------------------------------------
// Runtime execution
//----------------------------------------------------------------------
void loop() {
    const int segundosDormido = 60;

    // Humidity measure
    float humedad = readHumidity();
    printHumidityReading(humedad);

    // Hibernate for a minute
    ESP.deepSleep(segundosDormido * 1000000);
} // loop()

//----------------------------------------------------------------------
// Several humidity readings. Return the average
//----------------------------------------------------------------------
int readHumidity(){

  int16_t datos[10];
  int16_t adc0;
  float humedad;
  int sumatorio;

  //
  // Calcula la media de 10 datos
  //
  for(int i=0; i < 10; i++){

  adc0 = ads1115.readADC_SingleEnded(0);

  datos[i] = 100*aire/(aire-agua)-adc0*100/(aire-agua);

  sumatorio += datos[i];

  delay(50);

  } // for

  humedad = sumatorio / 10;

  return(humedad);

} // readHumidity()

//----------------------------------------------------------------------
// Print out received data into the Serial Monitor
//----------------------------------------------------------------------
void printHumidityReading(float humedad){

  //
  // Mostramos la medida de humedad
  //
  Serial.print("HR (%): ");
  Serial.print(humedad);
  Serial.println("%");
} // printHumidityReading()