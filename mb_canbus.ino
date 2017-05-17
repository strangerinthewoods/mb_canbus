#include <SPI.h>
#include <mcp_can.h>
#include "Configuration.h"
#include "DebugUtils.h"

// Globals
MCP_CAN CAN(SPI_CS_PIN);

// CAN RX Variables
long unsigned int rxId;
unsigned char len = 0;
unsigned char buf[8];


void setup()
{
  #ifdef DEBUG
    Serial.begin(115200);
    while (!Serial);
  #endif

  DEBUG_PRINT("CAN BUS: starting controller");
  while (CAN_OK != CAN.begin(MCP_STDEXT, CAN_500KBPS, MCP_8MHZ))
  {
    DEBUG_PRINT("CAN BUS: starting error! Trying again...");
    delay(500);
  }

  // Allow all Standard IDs
  DEBUG_PRINT("CAN BUS: setting standard filters");
  CAN.init_Mask(0,0x0000000);                // Init first mask...
  CAN.init_Filt(0,0x0000000);                // Init first filter...
  CAN.init_Filt(1,0x0000000);                // Init second filter...
  // Allow all Extended IDs
  DEBUG_PRINT("CAN BUS: setting extended filters");
  CAN.init_Mask(1,0x8000000);                // Init second mask...
  CAN.init_Filt(2,0x8000000);                // Init third filter...
  CAN.init_Filt(3,0x8000000);                // Init fouth filter...
  CAN.init_Filt(4,0x8000000);                // Init fifth filter...
  CAN.init_Filt(5,0x8000000);                // Init sixth filter...
  
  // Set operation mode to normal so the MCP2515 sends acks to received data.
  DEBUG_PRINT("CAN BUS: setting mode normal");
  CAN.setMode(MCP_NORMAL);

  // Configuring pin for /INT input
  DEBUG_PRINT("CAN BUS: setting input interrupt");
  pinMode(CAN_INT_PIN, INPUT);
  
  DEBUG_PRINT("CAN BUS: shield init successful");
}


void loop()
{

  // Receipt message
  // *************************************
  // If CAN_INT_PIN pin is low, read receive buffer
  if (LOW == digitalRead(CAN_INT_PIN))
  {
    // Read data: len = data length, buf = data byte(s)
    CAN.readMsgBuf(&rxId, &len, buf);

    switch (rxId)
    {
//      case 1:
//        DEBUG_PRINT("[RECV] Ignition On/Off");
//        break;
//      case 15:
//        DEBUG_PRINT("[RECV] Light On/Off");
//        break;

        default:
          #ifdef DEBUG
            Serial.print("<");
            Serial.print(rxId);
            Serial.print(",");
            for(int i = 0; i < len; i++)
            {
              Serial.print(buf[i]);
              Serial.print(",");
            }
            Serial.print(">");
            Serial.println();
          #endif
          break;
    }
    
  }

  
}
