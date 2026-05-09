// RF Receiver (slave) test
// Pancho 4: robot radiocontrolado
// Codigo do Robot
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#define LEDBLUE   2

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
  Wire.begin(); // join i2c bus (address optional for master)

  pinMode(LEDBLUE,   OUTPUT);
  
  Serial.begin(57600);
  Serial.println("Entrei");
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&newReceivedData, sizeof(newReceivedData));
    
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
    
    Wire.beginTransmission(8); // transmit to device #8
    
    state = 0;  // Default
    if (newReceivedData.ps2_PSB_BLUE == 1) state = 1;
    
    Wire.write(state);         // sends one byte
    Wire.endTransmission();
    delay(50);
  }
}
