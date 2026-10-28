// Pancho 4: robot radiocontrolado
// Teste - NODE_5
//
// NODE_ADDRESS_5  0x05  // Braço_Robótico

#include "pitches.h"
#include <Wire.h>  // I2C

#define NODE_ADDRESS_5  0x05
#define LEDBLUE 3

struct DataPackage {
  int var_1 = 200;
  int var_2 = 200;
  int var_3 = 200;
} received_data;

const int PACKAGE_SIZE = sizeof(DataPackage);

void setup() {
  Serial.begin(9600);
  Serial.println("Pancho 4 - Teste I2C do NODE_5 (Braço_Robótico).");
  Wire.begin(NODE_ADDRESS_5); // join i2c bus
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
  Serial.print("Pancho 4 - Node recebe dados: var1=");
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



/*
  teste casa-das-maquinas



#define DIR1 3
#define DIR2 5
#define ESQ1 6
#define ESQ2 9
#define BLUE 2

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(ESQ1, OUTPUT);
  pinMode(ESQ2, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(DIR1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(DIR1, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  digitalWrite(DIR2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(DIR2, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  digitalWrite(ESQ1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(ESQ1, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  digitalWrite(ESQ2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(ESQ2, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  digitalWrite(BLUE, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(BLUE, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);// wait for a second
}

*/
