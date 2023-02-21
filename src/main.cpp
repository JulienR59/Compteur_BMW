#include <Arduino.h>
#include <CAN_commands/CAN_commands.h>
#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>

void setup() {
  Serial.begin(9600);

  if(Canbus.init(9))  /* Initialise MCP2515 CAN controller at the specified speed */
  {
    Serial.println("CAN Init ok");
  } else
  {
    Serial.println("Can't init CAN");
  } 

}

void loop() {
  CAN_ignition_status();
  CAN_lighting_status(true);
  CAN_send_speed(90);
  
  delay(100);
}