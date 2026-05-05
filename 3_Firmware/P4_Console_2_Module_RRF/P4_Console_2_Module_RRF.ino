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

struct NewDataPackage {
  boolean ps2_PSB_SELECT;  // buttons pressed, released or changed state
  boolean ps2_PSB_START;
  boolean ps2_PSB_PAD_UP;
  boolean ps2_PSB_PAD_RIGHT;
  boolean ps2_PSB_PAD_DOWN;
  boolean ps2_PSB_PAD_LEFT;
  boolean ps2_PSB_L2;
  boolean ps2_PSB_R2;
  boolean ps2_PSB_L1;
  boolean ps2_PSB_R1;
  boolean ps2_PSB_GREEN;
  boolean ps2_PSB_RED;
  boolean ps2_PSB_BLUE;
  boolean ps2_PSB_PINK;
  byte    ps2_PSS_RX;  // "Sticks" values
  byte    ps2_PSS_RY;
  byte    ps2_PSS_LX;
  byte    ps2_PSS_LY;
};
const int NEW_PACKAGE_SIZE = sizeof(NewDataPackage);
NewDataPackage newReceivedData;

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
  Wire.begin(SLAVE_ADDRESS);   // join i2c bus with address #8
  Wire.onReceive(newReceiveData); // Registra callback para recepção de dados (interrupção)
  // Opcional: callback
  // Wire.onRequest(sendResponse);
  Serial.println("Escravo I2C pronto no endereço 0x08");
  
  pinMode(LEDBLUE, OUTPUT);
  
  Serial.begin(57600);
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  radio.write(&newReceivedData, sizeof(newReceivedData));
  digitalWrite(LEDBLUE, newReceivedData.ps2_PSB_BLUE);
  //delay(50);
}

// Função chamada quando dados são recebidos do I2C-mestre (Interrupção)
void newReceiveData(int byteCount) {
  if(byteCount == NEW_PACKAGE_SIZE) {
    uint8_t *dataPtr = (uint8_t*)&newReceivedData;
    for(int i = 0; i < NEW_PACKAGE_SIZE && Wire.available(); i++) {
      dataPtr[i] = Wire.read();
    }
    // Processar dados recebidos
    processNewReceivedData();
  } else {
    Serial.print("Tamanho inesperado: ");
    Serial.println(byteCount);
  }
}

void processNewReceivedData() {
  //=== Dados Recebidos ===
  Serial.print("Console_RRF. Select: ");  Serial.print(newReceivedData.ps2_PSB_SELECT);
  Serial.print(" - Start: ");             Serial.print(newReceivedData.ps2_PSB_START);
  Serial.print(" - R1: ");                Serial.print(newReceivedData.ps2_PSB_R1);
  Serial.print(" - R2: ");                Serial.print(newReceivedData.ps2_PSB_R2);
  Serial.print(" - L1: ");                Serial.print(newReceivedData.ps2_PSB_L1);
  Serial.print(" - L2: ");                Serial.print(newReceivedData.ps2_PSB_L2);
  Serial.print(" - PAD_UP: ");            Serial.print(newReceivedData.ps2_PSB_PAD_UP);
  Serial.print(" - PAD_RIGHT: ");         Serial.print(newReceivedData.ps2_PSB_PAD_RIGHT);
  Serial.print(" - PAD_DOWN: ");          Serial.print(newReceivedData.ps2_PSB_PAD_DOWN);
  Serial.print(" - PAD_LEFT: ");          Serial.print(newReceivedData.ps2_PSB_PAD_LEFT);
  Serial.print(" - GREEN: ");             Serial.print(newReceivedData.ps2_PSB_GREEN);
  Serial.print(" - RED: ");               Serial.print(newReceivedData.ps2_PSB_RED);
  Serial.print(" - BLUE: ");              Serial.print(newReceivedData.ps2_PSB_BLUE);
  Serial.print(" - PINK: ");              Serial.print(newReceivedData.ps2_PSB_PINK);
  Serial.print(" - RX: ");                Serial.print(newReceivedData.ps2_PSS_RX);
  Serial.print(" - RY: ");                Serial.print(newReceivedData.ps2_PSS_RY);
  Serial.print(" - LX: ");                Serial.print(newReceivedData.ps2_PSS_LX);
  Serial.print(" - LY: ");                Serial.print(newReceivedData.ps2_PSS_LY);
  Serial.println(" * ");
}

//////////////////////FUNÇÕES ANTIGAS////////////////////////////
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
//////////////////////////////////////////////////////////////

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
