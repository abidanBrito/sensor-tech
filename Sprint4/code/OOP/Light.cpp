
#include "Light.h"

// ---------------------------------------------------
// ---------------------------------------------------
Light::Light(Adafruit_ADS1115* adc_in, int outputPin_in){

  *adc = *adc_in;
  outputPin = outputPin_in;

}

//-----------------------------------------------------------------------
// Amount of light reading. Returns int assigned to printLightState()
//-----------------------------------------------------------------------
unsigned int Light::readVoltageLight() {
    int16_t reading = 0;
    unsigned int voltage = 0;

    reading = (*adc).readADC_SingleEnded(outputPin);

    // Convert it to (0 - 4.096 V) range
    voltage = map(reading, 0, 32768, 0, 4096);

    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println(" (mV)");

    if(voltage <= 30) {
        return 0;
    }
    else if (voltage <= 3700) {
        if(voltage <= 150) {
            return 1;
        }
        else if (voltage < 1500) {
            return 2;
        }
        else {
            return 3;
        }
    }
} // readVoltageLight()

Light::printLightState(unsigned int lightState) {
    //Print out result
    Serial.print("Intensidad de luz: ");
    if(lightState == 0) {
        Serial.println("está oscuro.");
    }
    else if(lightState == 1) {
        Serial.println("está nublado o en sombra.");
    }
    else if(lightState == 2) {
        Serial.println("está despejado.");
    }
    else {
        Serial.println("está soleado.");
    }
    Serial.println();
} // lightState()
