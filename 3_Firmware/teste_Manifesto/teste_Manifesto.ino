// Pancho 4: robot radiocontrolado
// Teste - NODE_3 // Manifesto
//
// NODE_ADDRESS_3  0x03  // Manifesto (buzzer e display)

#include "pitches.h"
#include <Wire.h>  // I2C

#define NODE_ADDRESS_3  0x03
#define LEDBLUE 3

struct DataPackage {
  int var_1 = 200;
  int var_2 = 200;
  int var_3 = 200;
} received_data;

const int PACKAGE_SIZE = sizeof(DataPackage);

void setup() {
  Serial.begin(9600);
  Serial.println("Pancho 4 - Teste do NODE_3 (Manifesto).");
  Wire.begin(NODE_ADDRESS_3); // join i2c bus
  Wire.onReceive(getData);
  pinMode(LEDBLUE, OUTPUT);
}

void loop() {
  /*Serial.print("Pancho 4 - Manifesto recebe dados: var1=");
  Serial.print(received_data.var_1);
  Serial.print(", var2=");
  Serial.print(received_data.var_2);
  Serial.print(", var3=");
  Serial.println(received_data.var_3);*/
  acende_blue();
  delay(received_data.var_1);
  apaga_blue();
  delay(received_data.var_2);
  acende_blue();
  delay(received_data.var_2);
  apaga_blue();
  delay(received_data.var_3);
}

// Função chamada quando dados são recebidos do mestre
void getData(int byteCount) {
  Serial.print(" recebido ");
  if(byteCount == PACKAGE_SIZE) {
    uint8_t *dataPtr = (uint8_t*)&received_data;
    for(int i = 0; i < PACKAGE_SIZE && Wire.available(); i++) {
      dataPtr[i] = Wire.read();
    }
    // Processar dados recebidos
    processReceivedData();
  } else {
    Serial.print("Tamanho inesperado: ");
    Serial.println(byteCount);
  }
}

void processReceivedData() {
  //Serial.println("\n=== Dados Recebidos ===");
  Serial.print("Pancho 4 - Manifesto recebe dados: var1=");
  Serial.print(received_data.var_1);
  Serial.print(", var2=");
  Serial.print(received_data.var_2);
  Serial.print(", var3=");
  Serial.println(received_data.var_3);
}

void acende_blue() {
  digitalWrite(LEDBLUE, HIGH);
}
void apaga_blue() {
  digitalWrite(LEDBLUE, LOW);
}
