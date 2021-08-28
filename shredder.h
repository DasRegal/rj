#ifndef _SHREDDER_H
#define _SHREDDER_H

#include "Arduino.h"

void ShredderInit(void);
uint8_t ShredderOnOff_1(uint8_t state);
uint8_t ShredderOnOff_2(uint8_t state);
void ShredderEmergencyStop(uint8_t state);

#endif // _SHREDDER_H
