#ifndef HUMIDITY_H
#define HUMIDITY_H

//// DEPENDENCIES ////
#include "System_Configuration.h"

// ---------------------------------------------------
// ---------------------------------------------------
class Humidity {
  private:

    Adafruit_ADS1115* adc;
    int outputPin;
    int lowerBound;
    int upperBound;
    int numReadings;

    safeValues(float *);

  public:

    Humidity(const Adafruit_ADS1115* ,const int ,const int ,const  float ,const int );

    float readHumidity();

    float readHumidity_V();

    printSensorReading(const float ,const char);

}; // class


#endif
