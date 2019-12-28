#ifndef PLUVIOMETER_H
#define PLUVIOMETER_H

//// DEPENDENCIES ////
#include "System_Configuration.h"

// ---------------------------------------------------
// ---------------------------------------------------
class Pluviometer {
  private:

    int POWER_PIN;
    int ECHO_PIN;

  public:

    Pluviometer();

    int readPluviometer();

}; // class
