// Pancho 4: robot radiocontrolado
// Codigo do Robot - Módulo "Controle Central"
// I2C Master

#include <Wire.h>  // I2C
#define SLAVE_ADDRESS_8 0x08  // Manifesto

byte state = 0;

struct DataPackage {
  int buzina;
  int controle_motores;
  int velocidade;
} dataToSend_Manifesto;

const int PACKAGE_SIZE = sizeof(DataPackage);

void setup() {
  Serial.begin(57600);
  Wire.begin(); // join i2c bus (address optional for master)

  Serial.println("Pancho 4 - Controle Central: ativado.");
  dataToSend_Manifesto.buzina = 0;
  dataToSend_Manifesto.controle_motores = 0;
  dataToSend_Manifesto.velocidade = 200;
}

void loop() {
    Serial.print("Master. Enviando dados: ");    
    Serial.print(" - buzina: ");
    Serial.print(dataToSend_Manifesto.buzina);
    Serial.print(" - controle_motores: ");
    Serial.print(dataToSend_Manifesto.controle_motores);
    Serial.print(" - Velocidade: ");
    Serial.print(dataToSend_Manifesto.velocidade);
    Serial.println(" ");

    transmitData_Manifesto();

    dataToSend_Manifesto.buzina++;
    if (dataToSend_Manifesto.buzina>1) dataToSend_Manifesto.buzina=0;
    dataToSend_Manifesto.controle_motores++;
    if (dataToSend_Manifesto.controle_motores>9) dataToSend_Manifesto.controle_motores=0;
}


void transmitData_Manifesto() {
  Wire.beginTransmission(SLAVE_ADDRESS_8);
  // Envia byte a byte da estrutura
  uint8_t *dataPtr = (uint8_t*)&dataToSend_Manifesto;
  for(size_t i = 0; i < PACKAGE_SIZE; i++) {
    Wire.write(dataPtr[i]);
  }
  byte error = Wire.endTransmission();
}

////////////////////////////////////////////////////////////////////////
