//Includes
#include <Arduino.h>
#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>
#include <CAN_commands/CAN_commands.h>


//Local variables
static uint8_t ignition_count =0xe2;
static unsigned long ignition_last_message_millis_time;

//Exported functions
void CAN_ignition_status(void)
{
    if ((millis() - ignition_last_message_millis_time) > 1400)
    {
    ignition_count++;
    ignition_last_message_millis_time = millis();
    }

    tCAN message;

    message.id = 0x130; //formatted in HEX
    message.header.rtr = 0;
    message.header.length = 5; //formatted in DEC
    message.data[0] = 0x45;
    message.data[1] = 0x40;
    message.data[2] = 0x21;
    message.data[3] = 0x8F; //formatted in HEX
    message.data[4] = ignition_count;


    mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
    mcp2515_send_message(&message);
}