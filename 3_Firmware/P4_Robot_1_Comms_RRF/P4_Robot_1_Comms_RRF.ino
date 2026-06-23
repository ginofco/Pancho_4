// Pancho 4: robô radiocontrolado
// Código do Robô: Módulo "Comms RRF" - Comunicações Remotas por Radiofrequência
// I2C Slave 7
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

#define SLAVE_ADDRESS_7 0x07
#define LEDBLUE   4

RF24 radio(8,7);                  // canal de rádio via NRF24L01
const byte address[6] = "ROBOT";  // identificador da rádio
byte state = 0;

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
} newReceivedData;

void setup() {
  Serial.begin(57600);
  Serial.println("Pancho 4: Módulo Comms_RRF pronto no endereço 0x07");
  // Registra o callback para quando o master solicitar dados
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  pinMode(LEDBLUE, OUTPUT);
  
  Wire.begin(SLAVE_ADDRESS_7);
  Wire.onRequest(requestEvent);  // Função chamada quando master pede dados

  //Serial.println("Pancho 4: passei");

  //iniciaEstrutura();
  
}

void loop() {
  if (radio.available()) {
    radio.read(&newReceivedData, sizeof(newReceivedData));
    digitalWrite(LEDBLUE, newReceivedData.ps2_PSB_BLUE);
    
    displayData();

    //delay(50); // Pequeno delay para evitar leituras muito rápidas
  }
}

// Função chamada automaticamente quando o master solicita dados
void requestEvent() {
  if (radio.available()) {
    radio.read(&newReceivedData, sizeof(newReceivedData));
    digitalWrite(LEDBLUE, newReceivedData.ps2_PSB_BLUE);
    
    displayData();

    //delay(50); // Pequeno delay para evitar leituras muito rápidas
  }
  
  // Envia toda a estrutura de uma vez como bytes
  Wire.write((uint8_t*)&newReceivedData, sizeof(newReceivedData));
  
  // Opcional: debug
  //Serial.println("Robot_1_Comms_RRF: Dados enviados ao master");
}

void iniciaEstrutura() {
  newReceivedData.ps2_PSB_SELECT    = false;
  newReceivedData.ps2_PSB_START     = false;
  newReceivedData.ps2_PSB_R1        = false;
  newReceivedData.ps2_PSB_R2        = false;
  newReceivedData.ps2_PSB_L1        = false;
  newReceivedData.ps2_PSB_L2        = false;
  newReceivedData.ps2_PSB_PAD_UP    = false;
  newReceivedData.ps2_PSB_PAD_RIGHT = false;
  newReceivedData.ps2_PSB_PAD_DOWN  = false;
  newReceivedData.ps2_PSB_PAD_LEFT  = false;
  newReceivedData.ps2_PSB_GREEN     = false;
  newReceivedData.ps2_PSB_RED       = false;
  newReceivedData.ps2_PSB_BLUE      = false;
  newReceivedData.ps2_PSB_PINK      = false;
  newReceivedData.ps2_PSS_RX        = 128;
  newReceivedData.ps2_PSS_RY        = 128;
  newReceivedData.ps2_PSS_LX        = 128;
  newReceivedData.ps2_PSS_LY        = 128;
}

void displayData() {
    Serial.print("P4_ModuloRRF. - Select: "); Serial.print(newReceivedData.ps2_PSB_SELECT);
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
