// RF Receiver test
// Pancho 4: robot radiocontrolado
// Codigo do Robot

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <Wire.h>
byte state = 0;

#define dirFrente 5
#define dirTras 3
#define esqFrente 6
#define esqTras 9

RF24 radio(8,7);

const byte address[6] = "ROBOT";
int LEDBLUE = 2;

int volante;
int buzina;
int marcha_frente;
int marcha_tras;
int velocidade;

struct Data_Package {
  int button2_state;
  int button3_state;
  int button4_state;
  int outputValue0;
  int outputValue1;
} data;

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  
  pinMode(esqFrente, OUTPUT);
  pinMode(esqTras, OUTPUT);
  pinMode(dirTras, OUTPUT);
  pinMode(dirFrente, OUTPUT);

  pinMode(LEDBLUE, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Entrei");
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {

/*
  acende_0(200);
  acende_1(200);
  acende_2(200);
  acende_3(200);
  acende_blue();
  delay(500);
  apaga_0();
  apaga_1();
  apaga_2();
  apaga_3();
  apaga_blue();
  delay(500);
  */
  if (radio.available()) {
    radio.read(&data, sizeof(data));
    
    volante = 255 - data.outputValue0;
    buzina = data.button2_state;
    marcha_frente = data.button3_state;
    marcha_tras = data.button4_state;
    velocidade = data.outputValue1 / 2 ;
    
    Serial.print("Receptor. Dados: ");    
    Serial.print(" - volante: ");
    Serial.print(volante);
    Serial.print(" - buzina: ");
    Serial.print(buzina);
    Serial.print(" - marcha_frente: ");
    Serial.print(marcha_frente);
    Serial.print(" - marcha_tras: ");
    Serial.print(marcha_tras);
    Serial.print(" - Velocidade: ");
    Serial.print(velocidade);
    Serial.println(" ");
    
    if (buzina == 1) acende_blue();
    else apaga_blue();

    if ((marcha_frente == 1)&(marcha_tras == 0)) {
      if ((volante > 100) & (volante<200)) move_p_frente(velocidade);
      if (volante <= 100) move_p_esquerda_frente(velocidade);
      if (volante >= 200) move_p_direita_frente(velocidade);
    }
    if ((marcha_frente == 0)&(marcha_tras == 1)) {
      if ((volante > 100) & (volante<200)) move_p_tras(velocidade);
      if (volante <= 100) move_p_direita_tras(velocidade);
      if (volante >= 200) move_p_esquerda_tras(velocidade);
    }
    if ((marcha_frente == 0)&(marcha_tras == 0)) {
      apaga_todos();
    }
    if ((marcha_frente == 1)&(marcha_tras == 1)) {
      apaga_todos();
    }
    
    Wire.beginTransmission(8); // transmit to device #8
    state = 0;  // Default
    if (buzina == 1) state = 1;
    Wire.write(state);         // sends one byte
    Wire.endTransmission();
    delay(50);
  }
}

void move_p_frente(int velocidade) {
  acende_0(velocidade);
  apaga_1();
  acende_2(velocidade);
  apaga_3();
}
void move_p_tras(int velocidade) {
  apaga_0();
  acende_1(velocidade);  
  apaga_2();
  acende_3(velocidade);
}
void move_p_esquerda_frente(int velocidade) {
  acende_0(velocidade);
  apaga_1();
  apaga_2();
  apaga_3();
}
void move_p_direita_frente(int velocidade) {
  apaga_0();
  apaga_1();
  acende_2(velocidade);
  apaga_3();
}
void move_p_esquerda_tras(int velocidade) {
  apaga_0();
  apaga_1();
  apaga_2();
  acende_3(velocidade);
}
void move_p_direita_tras(int velocidade) {
  apaga_0();
  acende_1(velocidade);
  apaga_2();
  apaga_3();
}
void apaga_todos() {
  apaga_0();
  apaga_1();  
  apaga_2();
  apaga_3();
}

void acende_0(int velocidade) {
  analogWrite(esqFrente, velocidade);
}
void acende_1(int velocidade) {
  analogWrite(esqTras, velocidade);
}
void acende_2(int velocidade) {
  analogWrite(dirTras, velocidade);
}
void acende_3(int velocidade) {
  analogWrite(dirFrente, velocidade);
}

void apaga_0() {
  digitalWrite(esqFrente, LOW);
}
void apaga_1() {
  digitalWrite(esqTras, LOW);
}
void apaga_2() {
  digitalWrite(dirTras, LOW);
}
void apaga_3() {
  digitalWrite(dirFrente, LOW);
}

void acende_blue() {
  digitalWrite(LEDBLUE, HIGH);
}
void apaga_blue() {
  digitalWrite(LEDBLUE, LOW);
}
////////////////////////////////////////////////////////////////////////
// References:
// miniProject
// https://www.instructables.com/RC-Toy-Car-Using-NRF24L01/
////////////////////////////////////////////////////////////////////////
