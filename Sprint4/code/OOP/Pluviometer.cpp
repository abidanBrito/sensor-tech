
#include "Pluviometer.h"

Pluviometer::Pluviometer(int POWER_PIN_IN, int ECHO_PIN_IN){

  ECHO_PIN = ECHO_PIN_IN;
  POWER_PIN = POWER_PIN_IN;

} //()

int Pluviometer::readPluviometer() {
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
