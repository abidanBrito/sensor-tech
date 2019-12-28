#ifndef LIGHT_H
#define LIGHT_H

//// DEPENDENCIES ////
#include "System_Configuration.h"

// ---------------------------------------------------
// ---------------------------------------------------
class Light {
  private:

    Adafruit_ADS1115* adc;
    int outputPin;

  public:

    Light(const Adafruit_ADS1115*,const int);

    unsigned int readVoltageLight();

}; // class

#endif
