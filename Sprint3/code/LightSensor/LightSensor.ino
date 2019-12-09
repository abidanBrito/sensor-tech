//// DEPENDENCIES ////
#include <Wire.h>
#include <Adafruit_ADS1015.h>

// Create an ADC object
Adafruit_ADS1115 myADC(0x48);

void setup() {
    // Set data rate for serial data transmission
    Serial.begin(9600);

    // Turn on ADS1115
    myADC.begin();

    // Gain (ADC Range) -> +/- 4.096 V (1 bit = 2 mV)
    myADC.setGain(GAIN_ONE);
} // setup()

unsigned int readVoltageLight(Adafruit_ADS1115* adc, int outputPin) {
    int16_t reading = 0;
    float voltage = 0.0f;

    reading = (*adc).readADC_SingleEnded(outputPin);

    // Convert it to (0 - 4.096 V) range
    voltage = (float) map(reading, 0, 32768, 0, 4096);

    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println(" mV");

    if(0 <= voltage <= 120) {
        return 0;
    }
    else if (120 < voltage <= 3700) {
        if(voltage < 350) {
            return 1;
        }
        else if (voltage < 1200) {
            return 2;
        }
        else {
            return 3;
        }
    }
} // readVoltageLight()

void loop() {
    unsigned int lightState = 0;

    // Find light
    lightState = readVoltageLight(&myADC, 3);

    //Print out result
    if(lightState == 0) {
        Serial.println("Está oscuro.");
    }
    else if(lightState == 1) {
        Serial.println("Está nublado o en sombra.");
    }
    else if(lightState == 2) {
        Serial.println("Está despejado.");
    }
    else {
        Serial.println("Está soleado.");
    }

    delay(1000);
} // loop()
