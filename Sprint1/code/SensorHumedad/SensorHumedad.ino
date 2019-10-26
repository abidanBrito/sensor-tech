#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads1115(0x48);

void setup() {

  Serial.begin(9600); // open serial port, set the baud rate as 9600 bps

  ads1115.begin();

  ads1115.setGain(GAIN_ONE);

}

void loop() {

  int val;

  val = ads1115.readADC_SingleEnded(0);

  Serial.println(val); //print the value to serial port

  delay(3000);
}
