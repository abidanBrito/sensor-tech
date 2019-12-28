
#include "Himidty.h"

// ---------------------------------------------------
// ---------------------------------------------------
Humidity::Humidity(Adafruit_ADS1115* adc_in, int outputPin_in, int lowerBound_in,int upperBound_in, int numReadings_in){

    *adc = *adc_in;
    outputPin = outputPin_in;
    lowerBound = lowerBound_in;
    upperBound = upperBound_in;
    numReadings = numReadings_in;

} // ()

//-----------------------------------------------------------------------
// Several humidity readings. Return the average
//-----------------------------------------------------------------------
float Humidity::readHumidity() {
    float averageReading = 0.0f;
    int percentageSum = 0;

    for(int i = 0; i < numReadings; i++) {
        delay(100);                         // Wait for sensor to settle

        // Get new reading
        int16_t reading = (*adc).readADC_SingleEnded(outputPin);

        int percentage = map(reading, upperBound, lowerBound, 100, 0);
        percentageSum += percentage;    // Add current percentage to the sum

        delay(25);                          // Wait between readings
    } // for

    // Get average reading value
    averageReading = percentageSum / numReadings;

    // Safety net (values within bounds)
    safeValues(&averageReading);

    return averageReading;
} // readHumidity()

//-----------------------------------------------------------------------
// One humidity reading. Return the voltage
//-----------------------------------------------------------------------
float Humidity::readHumidity_V() {

    // Get new reading
    int16_t reading = (*adc).readADC_SingleEnded(outputPin);

    return reading;
} // readHumidity()


//----------------------------------------------------------------------
// Make sure provided reading doesn't exceed bounds (0 - 100)
//----------------------------------------------------------------------
Humidity::safeValues(float *reading) {
    float upperBound = 100.0, lowerBound = 0.0;

    if(*reading > upperBound) {
        *reading = upperBound;
    }
    else if(*reading < lowerBound) {
        *reading = lowerBound;
    }
} // safeValues()

//----------------------------------------------------------------------
// Print out received data into the Serial Monitor
//----------------------------------------------------------------------
Humidity::printSensorReading(float measureValue, char StrLiteral[]) {
    // Print out measure in new range
    Serial.print(StrLiteral);
    Serial.print(" percentage: ");
    Serial.print(measureValue);
    Serial.println(" %");
} // printSensorReading()
