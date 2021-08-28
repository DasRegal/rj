#ifndef _SERVO_H
#define _SERVO_H

int ServoInit(void);
int ServoSet(int val);
void ServoEmergencyStop(uint8_t state);

#endif // _SERVO_H