#define ECHO_PIN 0
#define POWER_PIN 5
#define TAZA_ASUN_ML 402.12f

#include <Adafruit_ADS1015.h>       // ADS library
Adafruit_ADS1115 adc(0x48);
#define OUTPUT_PIN_SALINITY     5
#define LOWER_BOUND_SALINITY    1150
#define UPPER_BOUND_SALINITY    22000
#define NUM_READINGS            5


void setup() {
   Serial.begin(9600);
   pinMode(POWER_PIN, OUTPUT);
   pinMode(ECHO_PIN, INPUT);
   adc.begin();

   // Gain (ADC Range) -> +/- 4.096 V (1 bit = 2 mV)
   adc.setGain(GAIN_ONE);
}

void loop() {

  double salinity;
  salinity = readSalinityV2(NUM_READINGS);

  Serial.print("Salinity percentage: ");
  Serial.print(salinity);
  Serial.println(" %");

  readPluviometer();
  delay(1000);
}

int readPluviometer() {
  double pi = 3.141539;
  int height, duration;

  digitalWrite(POWER_PIN, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(POWER_PIN, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(POWER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);  //medimos el tiempo entre pulsos, en microsegundos

  height = duration * 10 / 292/ 2;   //convertimos a distancia, en cm

  double water = (pi * 4*4 * height)/1000;

  Serial.print("Volumen del vaso: ");
  Serial.print(water);
  Serial.println(" L");
}

float readSalinityV2(int numReadings) {
    //  Float for precision and prevent overflow
    float averageReading = 0.0, salinityPercentage = 0.0;
    int sum = 0;

    for (int i = 0; i < numReadings; i++) {
        digitalWrite(POWER_PIN, HIGH);                           //  Supply power to the sensor
        delay(100);                                              //  Wait for sensor to settle

        // Returns '16-bit int' (using ' 32-bit int' to avoid overflow)
        sum += adc.readADC_SingleEnded(ECHO_PIN);  //  Add reading to the running sum
        digitalWrite(POWER_PIN, LOW);                            //  Turn off power to the sensor
        delay(10);                                               //  Wait between readings
    } // for

    // Get average reading value
    averageReading = sum / numReadings;

    // Get percentage
    salinityPercentage = map(averageReading, LOWER_BOUND_SALINITY,
                                UPPER_BOUND_SALINITY, 0, 100);

    return salinityPercentage;
} // readSalinityV2()
