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

PS2X ps2x; // create PS2 Controller Class
int error = 0; 
byte type = 0;
byte vibrate = 0;

struct NewDataPackage {
  boolean ps2_PSB_SELECT;  // buttons pressed, released or changed state
  boolean ps2_PSB_L3;
  boolean ps2_PSB_R3;
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
  byte    ps2_PSAB_PAD_RIGHT; // How strong pressed
  byte    ps2_PSAB_PAD_UP;
  byte    ps2_PSAB_PAD_DOWN;
  byte    ps2_PSAB_PAD_LEFT;
  byte    ps2_PSAB_L2;
  byte    ps2_PSAB_R2;
  byte    ps2_PSAB_L1;
  byte    ps2_PSAB_R1;
  byte    ps2_PSAB_GREEN;
  byte    ps2_PSAB_RED;
  byte    ps2_PSAB_BLUE;
  byte    ps2_PSAB_PINK;
} newdataToSend;


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
