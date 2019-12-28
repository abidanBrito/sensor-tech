#ifndef SALINITY_H
#define SALINITY_H

//// DEPENDENCIES ////
#include "System_Configuration.h"


// ---------------------------------------------------
// ---------------------------------------------------
class Salinity {
  private:

    safeValues(const float*);

    Adafruit_ADS1115* adc;
    int powerPin;
    int inputPin;
    int lowerBound;
    int upperBound;
    int numReadings;

  public:

    Salinity(const Adafruit_ADS1115*,const int,const int ,
                        const int ,const int ,const int );

    float readSalinity();

    float readSalinity_V(const Adafruit_ADS1115*,const int ,const int );

    printSensorReading(float, char)


}; // class

#endif
