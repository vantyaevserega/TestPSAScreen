#include <mcp2515.h>
#include <CanFrameLog.h>
#include <EmulateBSIPSA.h>
#include <SPI.h>

CanFrameLog lg;
struct can_frame canMsg;
MCP2515 mcp2515(10);
EmulateBSIPSA car(&mcp2515, &lg);

void setup() 
{
  Serial.begin(115200);
  Serial.println("Start work");
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS, MCP_8MHZ);  
  mcp2515.setNormalMode();
  car.SetState(true);
}

void loop() 
{
  unsigned long now = millis();
  // обработка серийного порта
  if (Serial.available() > 0) 
  {
    char readed = (char)Serial.read();
    if(readed == 'A')
    {
      car.StartMessages(now);
    }
    else if(readed == 'B')
    { 
      car.SetState(true);
    }
    else if(readed == 'C')
    { 
      car.SetState(false);
    }    
  }
  
  car.DoWork(now);
}
