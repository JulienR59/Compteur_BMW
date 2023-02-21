//Exported functions declarations
/**
 * Sends the speed to the cluster
 * 
 * @param speed Speed in km/h
*/
void CAN_send_speed(uint16_t speed);

/**
 * Sends the lighting status to the cluster
 * 
 * @param dip_beam true if dip_beams are on, false instead
*/
void CAN_lighting_status(bool dip_beam);

/**
 * Send ignition status to the cluster
*/
void CAN_ignition_status(void);