//////////////////////////////////////////////
// Pancho 4: robô radiocontrolado 
// Console, Module RRF (I2C slave)
//////////////////////////////////////////////
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x08
#define LEDBLUE   4
            
#define CE_PIN 7
#define CSN_PIN 8
// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);  // CE, CSN

// canal de rádio via NRF24L01
const byte address[6] = "PNCHO";  // identificador da rádio
int error = 0; 
int buttonState = 0;

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

void setup() {
  Serial.begin(9600);
  Serial.println("Console - Transmissor RF: inicinando envio.");

  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}  // hold in infinite loop
  }
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  Wire.begin(SLAVE_ADDRESS);   // join i2c bus with address #8
  Wire.onReceive(ReceiveData); // Registra callback para recepção de dados (interrupção)
    
  pinMode(LEDBLUE, OUTPUT);
}

void loop() {
  // Estrutura de dados recebida via interrupção (Wire.onReceive(ReceiveData))
  buttonState = newReceivedData.ps2_PSB_BLUE; 

  // Enviando estrutura de dados para o r.Pancho
  //bool report = radio.write(&buttonState, sizeof(buttonState));
  bool report = radio.write(&newReceivedData, sizeof(newReceivedData));
  
  Serial.print("Transmissor: estado =");
  Serial.print(buttonState);
  if (report) Serial.println(" - RF: OK");
  else Serial.println(" - RF: FAIL");
  
  digitalWrite(LEDBLUE, buttonState);
  //delay(50);
}

// Função chamada quando dados são recebidos do I2C-mestre (Interrupção)
void ReceiveData(int byteCount) {
  if(byteCount == NEW_PACKAGE_SIZE) {
    uint8_t *dataPtr = (uint8_t*)&newReceivedData;
    for(int i = 0; i < NEW_PACKAGE_SIZE && Wire.available(); i++) {
      dataPtr[i] = Wire.read();
    }
    // Processar dados recebidos
    //displayData();
  } else {
    Serial.print("Tamanho inesperado: ");
    Serial.println(byteCount);
  }
  //radio.write(&newReceivedData, sizeof(newReceivedData));
  //digitalWrite(LEDBLUE, newReceivedData.ps2_PSB_BLUE);
}

void displayData() {
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

  if (newReceivedData.ps2_PSB_BLUE) acende_blue();
  else apaga_blue();
}

// Função opcional para enviar resposta quando o mestre solicitar
void sendResponse() {
  byte response = 0xAA; // Código de confirmação
  Wire.write(response);
}

void acende_blue() {
  digitalWrite(LEDBLUE, HIGH);
}
void apaga_blue() {
  digitalWrite(LEDBLUE, LOW);
}
