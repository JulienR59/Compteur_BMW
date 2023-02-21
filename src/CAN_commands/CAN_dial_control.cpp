//Includes
#include <Arduino.h>
#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>
#include <CAN_commands/CAN_commands.h>


//Local variables
//Speed
static uint16_t last_speed_value = 0;
static tCAN message_speed;
static unsigned long speed_last_message_millis_time;

//Exported functions
void CAN_send_speed(uint16_t speed)
{
    const uint8_t delta_time = millis() - speed_last_message_millis_time; // const

    uint16_t speed_value = speed + last_speed_value;

    uint16_t counter = (message_speed.data[6] | (message_speed.data[7] << 8)) & 0x0FFF;
    counter += (float)delta_time * M_PI;

    message_speed.id = 0x1A6; //formatted in HEX
    message_speed.header.rtr = 0;
    message_speed.header.length = 8; //formatted in DEC
    message_speed.data[0] = speed_value;
    message_speed.data[1] = (speed_value >> 8);
    message_speed.data[2] = message_speed.data[0];
    message_speed.data[3] = message_speed.data[1]; //formatted in HEX
    message_speed.data[4] = message_speed.data[0];
    message_speed.data[5] = message_speed.data[1];
    message_speed.data[6] = counter;
    message_speed.data[7] = (counter >> 8) | 0xF0;


    mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
    mcp2515_send_message(&message_speed);
    last_speed_value = speed_value;
    speed_last_message_millis_time = millis();
}