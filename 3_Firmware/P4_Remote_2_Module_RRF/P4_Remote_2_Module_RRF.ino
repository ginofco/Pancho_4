// RF Transmitter test
// Pancho 3: roboh radiocontrolado
// Codigo do Controle
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Segue trecho novo - com Wire
#include <Wire.h>
byte state = 0; // Robot state:  (Variavel global usada para comunicacao i2c.)
// Fim trecho novo - com Wire

int error = 0; 
byte type = 0;
byte vibrate = 0;

RF24 radio(8,7);  // create controle via NRF24L01

const byte address[6] = "ROBOT";
int BUTTON_2 = A2;
int BUTTON_3 = A3;
int BUTTON_4 = A4;
int POT_0    = A0;
int POT_1    = A1;

int sensorValue0;
int sensorValue1;

struct Data_Package {
  int button2_state;
  int button3_state;
  int button4_state;
  int outputValue0;
  int outputValue1;
} data;

void setup() {

  // Segue trecho novo - com Wire
  Wire.begin(); // join i2c bus (address optional for master)
  // Fim trecho novo - com Wire
  
  pinMode(BUTTON_2, INPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  data.button2_state = digitalRead(BUTTON_2);
  data.button3_state = digitalRead(BUTTON_3);
  data.button4_state = digitalRead(BUTTON_4);

  sensorValue0 = analogRead(POT_0);
  data.outputValue0 = map(sensorValue0, 0, 1023, 0, 255);
  sensorValue1 = analogRead(POT_1);
  data.outputValue1 = map(sensorValue1, 0, 1023, 0, 255);
  
  radio.write(&data, sizeof(data));

  Serial.print("Transmissor. Mensagem: luz: ");
  Serial.print(data.button2_state);
  Serial.print(" - direcao1: ");
  Serial.print(data.button3_state);
  Serial.print(" - direcao2:");
  Serial.print(data.button4_state);
  Serial.print(" - volante: ");
  Serial.print(data.outputValue0);
  Serial.print(" - aceler: ");
  Serial.print(data.outputValue1);
  Serial.println(" * ");

  // Segue trecho novo - com Wire
  Wire.beginTransmission(8); // transmit to device #8
  // Central de decisao
  state = 1;  // Default
  if (data.button2_state == HIGH) state = 2;
  Wire.write(state);         // sends one byte
  Wire.endTransmission();    // stop transmitting
  // Fim trecho novo - com Wire
  
  delay(200);
}


////////////////////////////////////////////////////////////////////////
// References:
// miniProject
// https://www.instructables.com/RC-Toy-Car-Using-NRF24L01/
////////////////////////////////////////////////////////////////////////
