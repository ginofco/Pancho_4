//////////////////////////////////////////////
// Pancho 4: roboh radiocontrolado 
// Console, Module RRF (I2C slave)
//////////////////////////////////////////////
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define SLAVE_ADDRESS 0x08
#include <Wire.h>

RF24 radio(8,7);                  // canal de rádio via NRF24L01
const byte address[6] = "ROBOT";  // identificador da rádio

int error = 0; 
int LEDBLUE = 4;

struct DataPackage {
  int button2_state;
  int button3_state;
  int button4_state;
  int outputValue0;
  int outputValue1;
};
const int PACKAGE_SIZE = sizeof(DataPackage);
DataPackage receivedData;

void setup() {
  Wire.begin(SLAVE_ADDRESS); // join i2c bus with address #8
  Wire.onReceive(receiveData); // Registra callback para recepção de dados
  // Opcional: callback
  // Wire.onRequest(sendResponse);
     
  Serial.println("Escravo I2C pronto no endereço 0x08");
  
  pinMode(LEDBLUE, OUTPUT);
  
  Serial.begin(9600);
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  radio.write(&receivedData, sizeof(receivedData));

  digitalWrite(LEDBLUE, receivedData.button2_state);
  
  //delay(50);
}

// Função chamada quando dados são recebidos do mestre
void receiveData(int byteCount) {
  if(byteCount == PACKAGE_SIZE) {
    uint8_t *dataPtr = (uint8_t*)&receivedData;
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
  Serial.print("Modulo RRF. Mensagem: luz: ");
  Serial.print(receivedData.button2_state);
  Serial.print(" - direcao1: ");
  Serial.print(receivedData.button3_state);
  Serial.print(" - direcao2:");
  Serial.print(receivedData.button4_state);
  Serial.print(" - volante: ");
  Serial.print(receivedData.outputValue0);
  Serial.print(" - aceler: ");       // Isadora
  Serial.print(receivedData.outputValue1);
  Serial.println(" * ");
  //Serial.println("=====================\n");
}

// Função opcional para enviar resposta quando o mestre solicitar
void sendResponse() {
  byte response = 0xAA; // Código de confirmação
  Wire.write(response);
}
////////////////////////////////////////////////////////////////////////
// References:
// miniProject
// https://www.instructables.com/RC-Toy-Car-Using-NRF24L01/
////////////////////////////////////////////////////////////////////////

// CÓDIGO ANTIGO
/*  
int BUTTON_2 = A2;
int BUTTON_3 = A3;
int BUTTON_4 = A4;
int POT_0    = A0;
int POT_1    = A1;
int sensorValue0;
int sensorValue1;

  int aux=0;
  data.button2_state = digitalRead(BUTTON_2);
  data.button3_state = digitalRead(BUTTON_3);
  data.button4_state = digitalRead(BUTTON_4);

  sensorValue0 = analogRead(POT_0);
  data.outputValue0 = map(sensorValue0, 0, 1023, 0, 255);
  sensorValue1 = analogRead(POT_1);
  data.outputValue1 = map(sensorValue1, 0, 1023, 0, 255);
if(aux==0) {
  data.button2_state = 0;
  data.button3_state = 0;
  data.button4_state = 1;
  data.outputValue0 = 0;
  data.outputValue1 = 0;
  aux=1;
}
else {
  data.button2_state = 1;
  data.button3_state = 0;
  data.button4_state = 1;
  data.outputValue0 = 250;
  data.outputValue1 = 250;
  aux=0;
}*/

// FUNÇÃO ANTIGA
/*
byte c;
//void receiveEvent(int howMany) {
void receiveEvent(struct Data_Package data) {
  
   c = Wire.read(); // receive a character
   if(c == 0){
     // do nothing
     digitalWrite(LEDBLUE, LOW);
   }//byte c
   if(c == 1){
     //play_song();
     digitalWrite(LEDBLUE, HIGH);
   }
   
   data = Wire.read();
}
*/
