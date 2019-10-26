//-----------------------------------------------------------------------
// Fecha: 21/10/2019
// Autores/as: Pablo Enguix, Abidán Brito, Elvira Montagud y Luis Belloch
//-----------------------------------------------------------------------

#include <Wire.h>

//
// Librería ADS
//
#include <Adafruit_ADS1015.h>

//
// se define el ads1115 en la dirección 0x48
//
Adafruit_ADS1115 ads1115(0x48);

//
// Medimos valor en seco ~0%
//
const int aire = 1700;

//
// Medimos en agua ~100%
//
const int agua = 400;

void setup() {

  Serial.begin(9600);

  //
  // Encendemos el ads1115
  //
  ads1115.begin();                                                               //Inicializar el ADS

  //
  // Situamos el rango del ADC: +/- 4.096V (1 bit=2mV)
  //
  ads1115.setGain(GAIN_ONE);

} // ()

//-----------------------------------------------------------------------
// MedirHumedad -> R
//-----------------------------------------------------------------------
int MedirHumedad(){

  int16_t datos[10];
  int16_t adc0;
  float humedad;
  int sumatorio;


  //
  // Calcula la media de 10 datos
  //
  for(int i=0; i < 10; i++){

  adc0 = ads1115.readADC_SingleEnded(0);

  datos[i] = 100*aire/(aire-agua)-adc0*100/(aire-agua);

  sumatorio += datos[i];

  delay(50);

  } // for

  humedad = sumatorio / 10;

  return(humedad);

} // ()

//-----------------------------------------------------------------------
// MedirSalinidad -> R
//-----------------------------------------------------------------------
int MedirSalinidad(){

  float salinidad;

  return(salinidad);

} // ()

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
void MostrarDatos(float humedad, float salinidad){

  //
  // Mostramos la medida de humedad
  //
  Serial.print("HR (%): ");
  Serial.print(humedad);
  Serial.println("%");

  //
  // Mostramos la medida de salinidad
  //
  Serial.print("SAL (%): ");
  Serial.print(salinidad);
  Serial.println("%");

}



void loop() {

  float humedad;
  float salinidad;
  const int segundosDormido = 60;

  humedad = MedirHumedad();

  salinidad = MedirSalinidad();

  MostrarDatos(humedad, salinidad);

  ESP.deepSleep(segundosDormido * 1000000);

} // ()