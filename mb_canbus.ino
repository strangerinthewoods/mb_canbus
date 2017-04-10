#include "Configuration.h"
#include "DebugUtils.h"
#include <SPI.h>
#include <mcp_can.h>

MCP_CAN CAN(10); // Set CS to pin 10

void setup()
{

  DEBUG_PRINT("Starting serial console...");
  #ifdef DEBUG
    Serial.begin(38400);
    delay(5000);
  #endif

  DEBUG_PRINT("Starting can bus controller...");
  while (CAN_OK != CAN.begin(CAN_125KBPS, MCP_8MHz))
  {
    DEBUG_PRINT("CAN BUS Shield init: ERROR");
    delay(300);
  }
  DEBUG_PRINT("CAN BUS Shield init: OK");

}


void loop() {

  unsigned char len = 0;
  unsigned char buf[8];

  // Receipt message
  // *************************************
  if(CAN_MSGAVAIL == CAN.checkReceive())
  {
    CAN.readMsgBuf(&len, buf);
    long unsigned int canId = CAN.getCanId();

    switch(canId)
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
          Serial.print(canId);
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

//  unsigned char stmp[8] = {0, 1, 2, 3, 4, 5, 6, 7};
//  CAN.sendMsgBuf(0x00, 0, 8, stmp);
//  delay(100);

  DEBUG_PRINT("=== loop ===");
}
