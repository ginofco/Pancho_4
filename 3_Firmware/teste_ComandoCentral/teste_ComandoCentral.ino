// Pancho 4: robot radiocontrolado
// Teste - NODE_CENTRAL // Comando Central
//
// NODE_ADDRESS_3  0x03  // Manifesto (buzzer e display)
// NODE_ADDRESS_4  0x04  // Casa_das_Maquinas
// NODE_ADDRESS_5  0x05  // Braço_Robótico
// NODE_ADDRESS_6  0x06  // Touchy
// NODE_ADDRESS_7  0x07  // Comms_RRF

#include <Wire.h>  // I2C
#define NODE_ADDRESS_3  0x03
#define NODE_ADDRESS_4  0x04
#define NODE_ADDRESS_5  0x05
#define NODE_ADDRESS_6  0x06
#define NODE_ADDRESS_7  0x07

struct DataPackage {
  int var_1;
  int var_2;
  int var_3;
} data_to_node_3;

const int PACKAGE_SIZE = sizeof(DataPackage);

void setup() {
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.println("Pancho 4 - Teste do NODE_CENTRAL (Comando Central).");
  Serial.println("Pausa 5s.");
  delay(5000);
}

void loop() {
  data_to_node_3.var_1 = 250;
  data_to_node_3.var_2 = 500;
  data_to_node_3.var_3 = 1000;
  Serial.print("Pancho 4 - Enviando ao Manifesto os dados: var1=");
  Serial.print(data_to_node_3.var_1);
  Serial.print(", var2=");
  Serial.print(data_to_node_3.var_2);
  Serial.print(", var3=");
  Serial.println(data_to_node_3.var_3);
  transmitData_Node_3();
  data_to_node_3.var_1 = 1000;
  data_to_node_3.var_2 = 500;
  data_to_node_3.var_3 = 250;
  Serial.print("Pancho 4 - Enviando ao Braço Robótico os dados: var1=");
  Serial.print(data_to_node_3.var_1);
  Serial.print(", var2=");
  Serial.print(data_to_node_3.var_2);
  Serial.print(", var3=");
  Serial.println(data_to_node_3.var_3);
  transmitData_Node_5();
}

void transmitData_Node_3() {
  Serial.println(" Entrando ");
  Wire.beginTransmission(NODE_ADDRESS_3);
  Serial.println(" begin ");
  // Envia byte a byte da estrutura
  uint8_t *dataPtr = (uint8_t*)&data_to_node_3;
  for(size_t i = 0; i < PACKAGE_SIZE; i++) {
    Wire.write(dataPtr[i]);
  }
  Serial.println(" loop ");
  byte error = Wire.endTransmission();
  Serial.println(" end ");
}

void transmitData_Node_5() {
  Serial.println(" Entrando ");
  Wire.beginTransmission(NODE_ADDRESS_5);
  Serial.println(" begin ");
  // Envia byte a byte da estrutura
  uint8_t *dataPtr = (uint8_t*)&data_to_node_3;
  for(size_t i = 0; i < PACKAGE_SIZE; i++) {
    Wire.write(dataPtr[i]);
  }
  Serial.println(" loop ");
  byte error = Wire.endTransmission();
  Serial.println(" end ");
}
