//// IMPORT EXTERNAL LIBRARIES ////
#include <Wire.h>
#include <Adafruit_ADS1015.h>

// Create an ADC object
Adafruit_ADS1115 ads1115(0x48);

//// MACRO DEFINITIONS ////

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

    for(int i = 0; i < numReadings; i++){
        sum += ads1115.readADC_SingleEnded(outputPin);
        delay(10);
    }

    // Get average reading value
    averageReading = (sum / numReadings);

    // Convert it to (0 - 4.096 V) range
    averageReading = (float) map(averageReading, 0, 32768, 0, 4096) / 1000;

    if(averageReading>=0.05){
    return 0
    }else if(0.05<averageReading<3.7){
            if(averageReading<1){
                return 1;
            }else{
                return 2;
            }
    }
    
    
} // readLight()

void loop() {
    unsigned int lightState = 0;

    // Find light
    lightState = readVoltageLight(5, 3);

    //Print out result
   if(lightState==0){
    
    Serial.println("Oscuridad");
   }
   
   else if(lightState==1){
    Serial.println("Sombra");
    }else{
      Serial.println("Soleado");
   }

    delay(1000);
} // loop()
