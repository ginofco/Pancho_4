// Testando circuitos para limpeza de bugs
//////////////////////////////////////////////
// Pancho 4: robô radiocontrolado 
// Robot, Module RRF
//////////////////////////////////////////////
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define LEDBLUE     4

#define CE_PIN 7
#define CSN_PIN 8
// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);  // CE, CSN

const byte address[6] = "PNCHO";  // identificador da rádio
int error = 0;
int buttonState = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Receptor: inicinando leitura.");
  //radio.begin();

  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}  // hold in infinite loop
  }
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  
  pinMode(LEDBLUE,   OUTPUT);
}

void loop() {
  Serial.print("Receptor: estado =");
  if (radio.available()) {
    radio.read(&buttonState, sizeof(buttonState));
    if (buttonState == HIGH) {
      digitalWrite(LEDBLUE, HIGH);
    } else {
      digitalWrite(LEDBLUE, LOW);
    }
    Serial.print(buttonState);
    Serial.println("  - RF: OK");
  }
  else Serial.println("  - RF: FAIL");
}
