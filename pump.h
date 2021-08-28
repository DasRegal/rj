#ifndef _PUMP_H
#define _PUMP_H

int PumpInit(void);
int PumpOnOff(int state);
void PumpEmergencyStop(uint8_t state);

#endif // _PUMP_H