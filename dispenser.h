#ifndef _DISPENSER_H
#define _DISPENSER_H

int DispenserInit(void);
int DispDryOnOff(int state);
int DispLiqOnOff(int state);
void DispenserEmergencyStop(uint8_t state);

#endif // _DISPENSER_H