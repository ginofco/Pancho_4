// P3_Casa_das_Maquinas

//#include <Wire.h>
//byte state = 0;

#define dirFrente 5
#define dirTras 3
#define esqFrente 9
#define esqTras 6

int volante;
int marcha_frente;
int marcha_tras;
int velocidade;
int comando;

void setup() {
  // put your setup code here, to run once:
  //Wire.begin(); // join i2c bus (address optional for master)

  pinMode(esqFrente, OUTPUT);
  pinMode(esqTras, OUTPUT);
  pinMode(dirTras, OUTPUT);
  pinMode(dirFrente, OUTPUT);
}
int i=0;
void loop() {
  
  velocidade = 200;
  
  comando = i;
  i++;
  if (i>6) i=0;

  switch(comando) {
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
  }
  delay(1000);apaga_todos();delay(1000);

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
/*
void acende_blue() {
  digitalWrite(LEDBLUE, HIGH);
}
void apaga_blue() {
  digitalWrite(LEDBLUE, LOW);
}*/
