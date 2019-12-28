#ifndef TEMPERATURE_H
#define TEMPERATURE_H

//// DEPENDENCIES ////
#include "System_Configuration.h"

// ---------------------------------------------------
// ---------------------------------------------------
class Temperature {
  private:

    Adafruit_ADS1115* adc;
    int numReadings;
    int outputPin;
    float y_Intercept;
    float slope;
    float d_Temp;

  public:

    Temperature(const Adafruit_ADS1115* ,const int ,const int ,
                        const  float ,const float,const float );

    float readTemperature();

    float readTemperature_V(Adafruit_ADS1115*);

    float voltageToTemperature(const float ,const float,const float ,const float);

    printTemperature(float temperature);

}; // class

#endif
