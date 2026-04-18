//////////////////////////////////////////////
// Pancho 4: roboh radiocontrolado 
// Console, Modulo PS2 (I2C master)
//////////////////////////////////////////////
#include <SPI.h>
#include <PS2X_lib.h>

// Segue trecho novo - com Wire
#include <Wire.h>
byte state = 0; // Robot state:  (Variavel global usada para comunicacao i2c.)
// Definir o endereço I2C do escravo
#define SLAVE_ADDRESS 0x08
// Fim trecho novo - com Wire

PS2X ps2x; // create PS2 Controller Class
int error = 0; 
byte type = 0;
byte vibrate = 0;

struct DataPackage {
  int button2_state;
  int button3_state;
  int button4_state;
  int outputValue0;
  int outputValue1;
} dataToSend;
const int PACKAGE_SIZE = sizeof(DataPackage);

void setup(){
 Serial.begin(57600);
 // Segue trecho novo - com Wire
 Wire.begin(); // join i2c bus (address optional for master)
 // Fim trecho novo - com Wire
 error = ps2x.config_gamepad(13,11,10,12, true, true);   
 //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) 
 //check for error
 if(error == 0) Serial.println("Found Controller, configured successful");
  else if(error == 1) Serial.println("No controller found, check wiring, ");
  else if(error == 2) Serial.println("Controller found but not accepting commands");
  else if(error == 3) Serial.println("Controller refusing to enter Pressures mode.");
}

void loop(){
 if(error == 1) // No controller found
  return; 
 else { 
  ps2x.read_gamepad(false, vibrate);  //read controller, set'vibrate' speed
  dataToSend.button2_state = ps2x.Button(PSB_BLUE);
  dataToSend.button3_state = ps2x.Button(PSB_PAD_UP);
  dataToSend.button4_state = ps2x.Button(PSB_PAD_DOWN);
  dataToSend.outputValue0  = ps2x.Analog(PSS_RX);
  dataToSend.outputValue1  = ps2x.Analog(PSS_RY);
  Serial.print("Transmissor. Mensagem: luz: ");  Serial.print(dataToSend.button2_state);
  Serial.print(" - direcao1: ");                 Serial.print(dataToSend.button3_state);
  Serial.print(" - direcao2:");                  Serial.print(dataToSend.button4_state); 
  Serial.print(" - volante: ");                  Serial.print(dataToSend.outputValue0);  
  Serial.print(" - aceler: ");                   Serial.print(dataToSend.outputValue1);
  Serial.println(" * ");
  // Transmitir dados via I2C
  transmitData();
 }
 delay(50);
}

void transmitData() {
  Wire.beginTransmission(SLAVE_ADDRESS);
  // Envia byte a byte da estrutura
  uint8_t *dataPtr = (uint8_t*)&dataToSend;
  for(size_t i = 0; i < PACKAGE_SIZE; i++) {
    Wire.write(dataPtr[i]);
  }
  byte error = Wire.endTransmission();
}
