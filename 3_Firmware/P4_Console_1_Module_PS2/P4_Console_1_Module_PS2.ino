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
 error = ps2x.config_gamepad(13,11,10,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
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

  Serial.print("Transmissor. Mensagem: luz: ");
  Serial.print(dataToSend.button2_state);
  Serial.print(" - direcao1: ");
  Serial.print(dataToSend.button3_state);
  Serial.print(" - direcao2:");
  Serial.print(dataToSend.button4_state);
  Serial.print(" - volante: ");
  Serial.print(dataToSend.outputValue0);
  Serial.print(" - aceler: ");
  Serial.print(dataToSend.outputValue1);
  Serial.println(" * ");
  
  // Transmitir dados via I2C
  transmitData();

  /*
  // Segue trecho novo - com Wire
  Wire.beginTransmission(SLAVE_ADDRESS); // transmit to device #8
  // Envia estrutura de dados 'data'
  state = 0;  // Default
  if (ps2x.NewButtonState(PSB_BLUE)) state = 1; 
  //Wire.write(state);         // sends one byte
  Wire.write(data);
  Wire.endTransmission();    // stop transmitting
  // Fim trecho novo - com Wire
  */
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
  //if(error == 0) {
  //  Serial.println("Dados enviados com sucesso!");
  //}
}


//////////////////////////////////////////
// CÓDIGO ORIGINAL ///////////////////////
//////////////////////////////////////////
// EM "setup()"
/*
 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
   Serial.println("holding L1 or R1 will print out the analog stick values.");
   Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   //Serial.print(ps2x.Analog(1), HEX);
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }
*/

// EM "loop()"
/*
   You must Read Gamepad to get new values
   Read GamePad and set vibration values ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
   if you don't enable the rumble, use ps2x.read_gamepad(); with no values    you should call this at least once a second
*/ 
/*
  if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
    Serial.println("Start is being held");
  if(ps2x.Button(PSB_SELECT))
    Serial.println("Select is being held");
  if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
    Serial.print("Up held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
  }
  if(ps2x.Button(PSB_PAD_RIGHT)){
    Serial.print("Right held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
  }
  if(ps2x.Button(PSB_PAD_LEFT)){
    Serial.print("LEFT held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
  }
  if(ps2x.Button(PSB_PAD_DOWN)){
    Serial.print("DOWN held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
  }
  vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on 
                                              //how hard you press the blue (X) button    
  if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
    {
      if(ps2x.Button(PSB_L3))
        Serial.println("L3 pressed");
      if(ps2x.Button(PSB_R3))
        Serial.println("R3 pressed");
      if(ps2x.Button(PSB_L2))
        Serial.println("L2 pressed");
      if(ps2x.Button(PSB_R2))
        Serial.println("R2 pressed");
      if(ps2x.Button(PSB_GREEN))
        Serial.println("Triangle pressed");
  }
  if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
    Serial.println("Circle just pressed");
         
  if(ps2x.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
    Serial.println("Square just released");     
    
  if(ps2x.NewButtonState(PSB_BLUE))            //will be TRUE if button was JUST pressed OR released
    Serial.println("X just changed");
  if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
    {
      Serial.print("Stick Values:");
      Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_LX), DEC); 
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_RY), DEC); 
      Serial.print(",");
      Serial.println(ps2x.Analog(PSS_RX), DEC); 
  }   
*/

// CÓDIGO ALTERNATIVO // Isadora
/*
  if(ps2x.Button(PSB_BLUE)) {
   Serial.print("Transmissor. Mensagem: luz: ");
   Serial.println("BLUE pressed");
   data.button2_state = 1;
  }
  if(ps2x.Button(PSB_PAD_UP)) {
   Serial.println("PAD_UP pressed");
   data.button3_state = 1;
  }
  if(ps2x.Button(PSB_PAD_DOWN)) {
   Serial.println("PAD_DOWN pressed");
   data.button4_state = 1;
  }
  
  if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) { // print stick values if either is TRUE
   data.outputValue0 = ps2x.Analog(PSS_RY);
   Serial.print(ps2x.Analog(PSS_RY), DEC);
   Serial.print(",");
   Serial.print( data.outputValue0 ); 
   Serial.print(",");
   data.outputValue1 = ps2x.Analog(PSS_RX);
   Serial.print( data.outputValue1 ); 
   Serial.print(",");
   Serial.println(ps2x.Analog(PSS_RX), DEC); 
  } 
*/        
