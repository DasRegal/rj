#ifndef _ACT_H
#define _ACT_H

//#include <stdint.h>

int ActInit(void);
int ActVBlock(void);
int ActHBlock(void);
int ActVUnblock(void);
int ActHUnblock(void);
int ActIn(uint8_t speed);
int ActOut(uint8_t speed);
int ActUp(uint8_t speed);
int ActDown(uint8_t speed);
int ActStopV(void);
int ActStopH(void);
int ActDisableV(void);
int ActDisableH(void);
int ActEnableV(void);
int ActEnableH(void);
void ActEmergencyStop(uint8_t state);

#endif // _ACT_H
