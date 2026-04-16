// Pancho 4: robot radiocontrolado
// Codigo do Robot - Módulo "Manifesto"
// I2C Slave
// https://www.arduino.cc/en/Tutorial/Tone

#include <Wire.h>
#include "pitches.h"
#define LEDBLUE 8
#define dirFrente 5
#define dirTras 3
#define esqFrente 9
#define esqTras 6

int volante;
int marcha_frente;
int marcha_tras;
int velocidade=200;
int comando;

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  Serial.begin(9600);
  Serial.println("Pancho 4 - Manifesto: ativado.");
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent);
  pinMode(esqFrente, OUTPUT);
  pinMode(esqTras, OUTPUT);
  pinMode(dirTras, OUTPUT);
  pinMode(dirFrente, OUTPUT);
  pinMode(LEDBLUE, OUTPUT);
}
byte c1=0;
byte c=0;
void receiveEvent(int howMany) {
   c = Wire.read();
}

void loop() {
  /*if(c == 0){
     // do nothing
   }
   if(c == 1){
     play_song();
   }*/
   Serial.print("Pancho 4 - c = ");
   Serial.println(c);

   switch(c) {
    case 0:
      apaga_todos();
      break;
    case 1:
      move_p_frente(velocidade);
      break;
    case 2:
      move_p_esquerda_frente(velocidade);
      break;
    case 3:
      move_p_direita_frente(velocidade);
      break;
    case 4:
      move_p_tras(velocidade);
      break;
    case 5:
      move_p_esquerda_tras(velocidade);
      break;
    case 6:
      move_p_direita_tras(velocidade);
      break;
    case 8:
      //play_song();
      acende_blue();
      break;
    case 9:
      //play_song();
      apaga_blue();
      break;
  }
  //c++; delay(500);
}

void play_song() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
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
