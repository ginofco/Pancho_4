// Pancho 4: robot radiocontrolado
// Codigo do Robot - Módulo "Controle Central"
// I2C Master

#include <Wire.h>

byte state = 0;

struct DataPackage {
  int buzina;
  int controle_motores;
  int velocidade;
} data;

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  
  Serial.begin(9600);
  Serial.println("Pancho 4 - Controle Central: ativado.");

  data.buzina = 0;
  data.controle_motores = 0;
  data.velocidade = 200;

}


void loop() {
  
    Serial.print("Master. Enviando dados: ");    
    Serial.print(" - buzina: ");
    Serial.print(data.buzina);
    Serial.print(" - controle_motores: ");
    Serial.print(data.controle_motores);
    Serial.print(" - Velocidade: ");
    Serial.print(data.velocidade);
    Serial.println(" ");
    
    Wire.beginTransmission(8); // transmit to device #8
    state = 9;  // Default
    if (data.buzina == 1) state = 8;
    Wire.write(state);         // sends one byte
    Wire.endTransmission();
    delay(500);

    data.buzina++;
    if (data.buzina>1) data.buzina=0;
    data.controle_motores++;
    if (data.controle_motores>9) data.controle_motores=0;
  
}

////////////////////////////////////////////////////////////////////////
