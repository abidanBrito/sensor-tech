//-----------------------------------------------------------
// Autores: Pablo Enguix y Luis Belloch
// Fecha: 29/10/2019
//-----------------------------------------------------------

//
//Librerías del Ads
//
#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads1115(0x48);

#define power_pin 13

void setup() {

  //
  // Se prepara el pin de alimentación
  //
  pinMode (power_pin, OUTPUT);

  //
  // Se prepara el serial plot
  //
  Serial.begin(9600);

  //
  // Se enciende el ads y se pone a gain one: +/- 4.096V (1 bit=2mV)
  //
  ads1115.begin();

  ads1115.setGain(GAIN_ONE);

}

//-----------------------------------------------------------
// Z, Z, Z, Z -> medirTemperatura -> R
//-----------------------------------------------------------
float medirTemperatura(int cantidadMedidas, int limiteBajo, int limiteAlto, int ADC){

  float medida = 0.0;
  int16_t sum = 0;
  float porcentaje = 0.0;

  digitalWrite(power_pin, HIGH);

  //
  // Bucle de medidas y media artimética
  //
  for(int i = 0; i < cantidadMedidas; i++){

  sum += ads1115.readADC_SingleEnded(ADC);
    
  }

  medida = sum/cantidadMedidas;
  
  digitalWrite(power_pin, LOW);

  porcentaje = map(medida, limiteBajo, limiteAlto, 25000, 40000)/1000.00;

  return porcentaje;
  
}

void loop() {

  float medida = medirTemperatura(10, -111, -80, 2);

  Serial.println(medida);

  delay(1000);

}
