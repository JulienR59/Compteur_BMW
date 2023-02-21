//Includes
#include <Arduino.h>
#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>
#include <CAN_commands/CAN_commands.h>

//Local variables


//Exported functions
void CAN_lighting_status(bool dip_beam)
{
    uint8_t exterior_lighting;
    if (dip_beam = true)
    {
        exterior_lighting = 0x05;
    }
    else
    {
        exterior_lighting = 0x00;
    }


    tCAN message;

    message.id = 0x21A; //formatted in HEX
    message.header.rtr = 0;
    message.header.length = 3; //formatted in DEC
    message.data[0] = exterior_lighting;
    message.data[1] = 0x00;
    message.data[2] = 0xF7;



    mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
    mcp2515_send_message(&message);
}