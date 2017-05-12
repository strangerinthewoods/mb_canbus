#include <SPI.h>
#include <mcp_can.h>
#include "Configuration.h"
#include "DebugUtils.h"

// Globals
MCP_CAN CAN(SPI_CS_PIN);
long unsigned int rxId;
unsigned char len = 0;
unsigned char buf[8];


void setup()
{
  #ifdef DEBUG
  Serial.begin(115200);
  #endif

  DEBUG_PRINT("Starting can bus controller...");
  while (CAN_OK != CAN.begin(MCP_ANY, CAN_250KBPS, MCP_8MHZ))
  {
    DEBUG_PRINT("CAN BUS Shield init: ERROR");
    delay(500);
  }

  // Set operation mode to normal so the MCP2515 sends acks to received data.
  CAN.setMode(MCP_NORMAL);

  // Configuring pin for /INT input
  pinMode(CAN_INT_PIN, INPUT);
  
  DEBUG_PRINT("CAN BUS Shield init: OK");
}


void loop() {

  // Receipt message
  // *************************************
  // If CAN_INT_PIN pin is low, read receive buffer
  if(!digitalRead(CAN_INT_PIN))
  {
    char msgString[128];

    // Read data: len = data length, buf = data byte(s)
    CAN.readMsgBuf(&rxId, &len, buf);

    // Determine if ID is standard (11 bits) or extended (29 bits)
    if((rxId & 0x80000000) == 0x80000000)
      sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    else
      sprintf(msgString, "Standard ID: 0x%.3lX  DLC: %1d  Data:", rxId, len);
    Serial.print(msgString);

    // Determine if message is a remote request frame
    if((rxId & 0x40000000) == 0x40000000)
    {
      sprintf(msgString, " REMOTE REQUEST FRAME");
      Serial.print(msgString);
    } else {
      for(byte i = 0; i < len; i++)
      {
        sprintf(msgString, " 0x%.2X", buf[i]);
        Serial.print(msgString);
      }
    }
    Serial.println();

    switch(rxId)
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
