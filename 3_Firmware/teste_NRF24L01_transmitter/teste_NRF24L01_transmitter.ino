// Testando circuitos para limpeza de bugs
//////////////////////////////////////////////
// Pancho 4: robô radiocontrolado 
// Console, Module RRF
//////////////////////////////////////////////
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define BUTTONPIN   3
#define LEDBLUE     4

#define CE_PIN 7
#define CSN_PIN 8
// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);  // CE, CSN

const byte address[6] = "PNCHO";  // identificador da rádio
int error = 0;
int buttonState = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Transmissor: inicinando envio.");
  //radio.begin();
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}  // hold in infinite loop
  }
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
  pinMode(BUTTONPIN, INPUT);
  pinMode(LEDBLUE,   OUTPUT);
}

int c=0; // contador
void loop() {
  //buttonState = digitalRead(BUTTONPIN);
  if (c>100) { buttonState = 1; if (c>200) c=0; }
  else buttonState=0;
  c++;
  Serial.print("Transmissor: c =");
  Serial.print(c);
  Serial.print("- estado =");
  Serial.print(buttonState);
  
  bool report = radio.write(&buttonState, sizeof(buttonState));
  if (report) Serial.println(" - RF: OK");
  else Serial.println(" - RF: FAIL");
  
  if (buttonState == HIGH) {
    digitalWrite(LEDBLUE, HIGH);
  } else {
    digitalWrite(LEDBLUE, LOW);
  }
}
