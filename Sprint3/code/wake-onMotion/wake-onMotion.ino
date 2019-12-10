//------------------------------------------------
// Fecha: 19/11/2019
// Descripción: wake on motion
//------------------------------------------------

#include <Wire.h>

#define MPU9250_ADDRESS 0x68

#define PWR_MGMT_1      0x6B
#define PWR_MGMT_2      0x6C

#define ACCEL_CONFIG_2  0x1D
#define INT_ENABLE      0x38
#define MOT_DETECT_CTRL 0x69

#define WOM_THR         0x1F
#define LP_ACCEL_ODR    0x1E

  // Pin de interrupción
  const byte interruptPin = 4;

  volatile byte interruptCounter = 0;

// Funcion auxiliar de escritura en bits
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
   Wire.beginTransmission(Address);
   Wire.write(Register);
   Wire.write(Data);
   Wire.endTransmission();
}

//Funcion auxiliar lectura
void I2CreadByte(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
   Wire.beginTransmission(Address);
   Wire.write(Register);
   Wire.endTransmission();
 
   Wire.requestFrom(Address, Nbytes);
   uint8_t index = 0;
   while (Wire.available())
      Data[index++] = Wire.read();
}

ICACHE_RAM_ATTR // Arregla el error ISR not in IRAM
void handleInterrupt(){

  uint8_t status[1];
  I2CreadByte(MPU9250_ADDRESS, 0x3A, 1, status);

  interruptCounter++;

  Serial.println("Interrumpted");
  
}

void setup() {

  Wire.begin();
  Serial.begin(9600);
  Serial.println("configurando");

  //Configurar los bits necesarios
  I2CwriteByte(MPU9250_ADDRESS, PWR_MGMT_1, 0b00000000);

  I2CwriteByte(MPU9250_ADDRESS, PWR_MGMT_2, 0b00000111);

  I2CwriteByte(MPU9250_ADDRESS, ACCEL_CONFIG_2, 0b00001001);

  I2CwriteByte(MPU9250_ADDRESS, INT_ENABLE, 0x40);

  I2CwriteByte(MPU9250_ADDRESS, MOT_DETECT_CTRL, 0b11000000);

  I2CwriteByte(MPU9250_ADDRESS, WOM_THR, 0x02);

  I2CwriteByte(MPU9250_ADDRESS, LP_ACCEL_ODR, 0b00000100);

  I2CwriteByte(MPU9250_ADDRESS, 0x37, 128);

  I2CwriteByte(MPU9250_ADDRESS, PWR_MGMT_1, 0b00100000); 

  pinMode(interruptPin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, CHANGE);
  
  uint8_t status[1];
  I2CreadByte(MPU9250_ADDRESS, 0x3A, 1, status);
  
}

void loop() {
  // put your main code here, to run repeatedl

  Serial.println("Awaken");

  ESP.deepSleep(5000000);

//  
//  if(interruptCounter>0){
//
//    interruptCounter--;
//    
//  }

}
