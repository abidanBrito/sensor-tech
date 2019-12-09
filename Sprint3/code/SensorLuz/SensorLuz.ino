//// DEPENDENCIES ////
#include <Wire.h>
#include <Adafruit_ADS1015.h>

// Create an ADC object
Adafruit_ADS1115 ads1115(0x48);

void setup() {
    // Set data rate for serial data transmission
    Serial.begin(9600);

    // Turn on ADS1115
    ads1115.begin();

    // Gain (ADC Range) -> +/- 4.096 V (1 bit = 2 mV)
    ads1115.setGain(GAIN_ONE);
} // setup()

unsigned int readVoltageLight(int numReadings, int outputPin){
    float averageReading = 0.0;
    int16_t sum = 0;

    for(int i = 0; i < numReadings; i++) {
        sum += ads1115.readADC_SingleEnded(outputPin);
        delay(10);
    }

    // Get average reading value
    averageReading = (sum / numReadings);

    // Convert it to (0 - 4.096 V) range
    averageReading = (float) map(averageReading, 0, 32768, 0, 4096) / 1000;

    if(0 <= averageReading <= 120) {
        return 0;
    }
    else if (120 < averageReading <= 3700) {
        if(averageReading < 350) {
            return 1;
        }
        else if (averageReading < 1200) {
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
    lightState = readVoltageLight(5, 3);

    //Print out result
    if(lightState == 0) {

        Serial.println("Está oscuro.");
    }

    else if(lightState == 1) {
        Serial.println("Está nublado o en sombra.");
    }
    else if(lightState==2) {
        Serial.println("Está despejado.");
    }
    else {
        Serial.println("Está soleado.");
    }

    delay(1000);
} // loop()
