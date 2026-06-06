// Pancho 4: robot radiocontrolado
// Codigo do Robot - Módulo "Controle Central"
// I2C Master

#include <Wire.h>  // I2C
#define SLAVE_ADDRESS_7 0x07  // Comms_RRF
#define SLAVE_ADDRESS_8 0x08  // Manifesto

byte state = 0;

struct DataPackage {
  int buzina;
  int controle_motores;
  int velocidade;
} dataToSend_Manifesto;
const int PACKAGE_SIZE = sizeof(DataPackage);

struct NewDataPackage {
  boolean ps2_PSB_SELECT;  // buttons pressed, released or changed state
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
} newReceivedData;

const int NEW_PACKAGE_SIZE = sizeof(NewDataPackage);

void setup() {
  Serial.begin(57600);
  Wire.begin(); // join i2c bus (address optional for master)
  
  iniciaEstrutura();
  
  Serial.println("Pancho 4 - Controle Central: ativado.");
  dataToSend_Manifesto.buzina = 0;
  dataToSend_Manifesto.controle_motores = 0;
  dataToSend_Manifesto.velocidade = 200;
}

void loop() {
    //Serial.print("Master. Recebendo dados: ");   
    // Solicita dados do slave
    requestDataFromSlave();
    
    //displayData();
    
    dataToSend_Manifesto.buzina           = newReceivedData.ps2_PSB_BLUE;
    dataToSend_Manifesto.controle_motores = newReceivedData.ps2_PSS_RY;
    dataToSend_Manifesto.velocidade       = newReceivedData.ps2_PSS_LY;
  
    Serial.print("Master. Enviando dados: ");    
    Serial.print(" - buzina: ");
    Serial.print(dataToSend_Manifesto.buzina);
    Serial.print(" - controle_motores: ");
    Serial.print(dataToSend_Manifesto.controle_motores);
    Serial.print(" - Velocidade: ");
    Serial.print(dataToSend_Manifesto.velocidade);
    Serial.println(" ");

    transmitData_Manifesto();

    //dataToSend_Manifesto.buzina++;
    //if (dataToSend_Manifesto.buzina>1) dataToSend_Manifesto.buzina=0;
    //dataToSend_Manifesto.controle_motores++;
    //if (dataToSend_Manifesto.controle_motores>9) dataToSend_Manifesto.controle_motores=0;

    // Aguarda um tempo antes da próxima leitura
    delay(50);
}

void requestDataFromSlave() {
  // Solicita o número de bytes igual ao tamanho da estrutura
  Wire.requestFrom(SLAVE_ADDRESS_7, sizeof(NewDataPackage));
  
  // Verifica se recebeu a quantidade correta de bytes
  uint8_t bytesReceived = 0;
  if(Wire.available() >= sizeof(NewDataPackage)) {
    
    // Lê os bytes diretamente para a estrutura
    for(uint8_t i = 0; i < sizeof(NewDataPackage); i++) {
      ((uint8_t*)&newReceivedData)[i] = Wire.read();
    }
    bytesReceived = sizeof(NewDataPackage);
    
    // Processa os dados recebidos
    //displayReceivedData();
    
  } else {
    Serial.print("Erro: Recebido apenas ");
    Serial.print(Wire.available());
    Serial.print(" de ");
    Serial.print(sizeof(NewDataPackage));
    Serial.println(" bytes esperados");
  }
}

void transmitData_Manifesto() {
  Wire.beginTransmission(SLAVE_ADDRESS_8);
  // Envia byte a byte da estrutura
  uint8_t *dataPtr = (uint8_t*)&dataToSend_Manifesto;
  for(size_t i = 0; i < PACKAGE_SIZE; i++) {
    Wire.write(dataPtr[i]);
  }
  byte error = Wire.endTransmission();
}

void iniciaEstrutura() {
  newReceivedData.ps2_PSB_SELECT    = false;
  newReceivedData.ps2_PSB_START     = false;
  newReceivedData.ps2_PSB_R1        = false;
  newReceivedData.ps2_PSB_R2        = false;
  newReceivedData.ps2_PSB_L1        = false;
  newReceivedData.ps2_PSB_L2        = false;
  newReceivedData.ps2_PSB_PAD_UP    = false;
  newReceivedData.ps2_PSB_PAD_RIGHT = false;
  newReceivedData.ps2_PSB_PAD_DOWN  = false;
  newReceivedData.ps2_PSB_PAD_LEFT  = false;
  newReceivedData.ps2_PSB_GREEN     = false;
  newReceivedData.ps2_PSB_RED       = false;
  newReceivedData.ps2_PSB_BLUE      = false;
  newReceivedData.ps2_PSB_PINK      = false;
  newReceivedData.ps2_PSS_RX        = 128;
  newReceivedData.ps2_PSS_RY        = 128;
  newReceivedData.ps2_PSS_LX        = 128;
  newReceivedData.ps2_PSS_LY        = 128;
}

void displayData() {
    Serial.print("P4_ModuloRRF. - Select: "); Serial.print(newReceivedData.ps2_PSB_SELECT);
    Serial.print(" - Start: ");             Serial.print(newReceivedData.ps2_PSB_START);
    Serial.print(" - R1: ");                Serial.print(newReceivedData.ps2_PSB_R1);
    Serial.print(" - R2: ");                Serial.print(newReceivedData.ps2_PSB_R2);
    Serial.print(" - L1: ");                Serial.print(newReceivedData.ps2_PSB_L1);
    Serial.print(" - L2: ");                Serial.print(newReceivedData.ps2_PSB_L2);
    Serial.print(" - PAD_UP: ");            Serial.print(newReceivedData.ps2_PSB_PAD_UP);
    Serial.print(" - PAD_RIGHT: ");         Serial.print(newReceivedData.ps2_PSB_PAD_RIGHT);
    Serial.print(" - PAD_DOWN: ");          Serial.print(newReceivedData.ps2_PSB_PAD_DOWN);
    Serial.print(" - PAD_LEFT: ");          Serial.print(newReceivedData.ps2_PSB_PAD_LEFT);
    Serial.print(" - GREEN: ");             Serial.print(newReceivedData.ps2_PSB_GREEN);
    Serial.print(" - RED: ");               Serial.print(newReceivedData.ps2_PSB_RED);
    Serial.print(" - BLUE: ");              Serial.print(newReceivedData.ps2_PSB_BLUE);
    Serial.print(" - PINK: ");              Serial.print(newReceivedData.ps2_PSB_PINK);
    Serial.print(" - RX: ");                Serial.print(newReceivedData.ps2_PSS_RX);
    Serial.print(" - RY: ");                Serial.print(newReceivedData.ps2_PSS_RY);
    Serial.print(" - LX: ");                Serial.print(newReceivedData.ps2_PSS_LX);
    Serial.print(" - LY: ");                Serial.print(newReceivedData.ps2_PSS_LY);
    Serial.println(" * ");
}

////////////////////////////////////////////////////////////////////////
