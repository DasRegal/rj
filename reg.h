#ifndef _REG_H
#define _REG_H

#include "Arduino.h"

#define REG_R_MAX       126
enum
{
  E_SHREDDER_ON_OFF_1 = 0,      // 0
  E_SHREDDER_ON_OFF_2,          // 1
  E_WEIGHT_1,                   // 2
  E_WEIGHT_2,                   // 3
  E_BLEND_SYSTEM_ON_OFF,        // 4
  E_ACTUATOR_H_IN_OUT,          // 5
  E_ACTUATOR_H_EN,              // 6
  E_ACTUATOR_V_UP,              // 7
  E_ACTUATOR_V_DOWN,            // 8
  E_ACTUATOR_V_FLUSH,           // 9
  E_ACTUATOR_V_EN,              // 10
  E_ACTUATOR_V_SPEED_1,         // 11
  E_ACTUATOR_V_SPEED_2,         // 12
  E_ACTUATOR_V_TIME_2,          // 13
  E_ACTUATOR_V_SPEED_3,         // 14
  E_ACTUATOR_V_SPEED_4,         // 15
  E_ACTUATOR_V_TIME_4,          // 16
  E_ACTUATOR_V_SPEED_5,         // 17
  E_ACTUATOR_V_SPEED_6,         // 18
  E_ACTUATOR_V_TIME_6,          // 19
  E_ACTUATOR_V_SPEED_7,         // 20
  E_ACTUATOR_V_SPEED_8,         // 21
  E_ACTUATOR_V_TIME_8,          // 22
  E_ACTUATOR_V_DELAY_8,         // 23
  E_ACTUATOR_V_SPEED_9,         // 24
  E_MIXER_ON_OFF,               // 25
  E_PUMP_ON_OFF,                // 26
  E_FLUSH_TIME,                 // 27
  E_DISPENSER_DRY_ON_OFF,       // 28
  E_DISPENSER_DRY_COUNT,        // 29
  E_NU_1,                       // 30
  E_DISPENSER_LIQ_ON_OFF,       // 31
  E_DISPENSER_LIQ_TIME,         // 32
  E_NU_2,                       // 33
  E_SERVO_PWM,                  // 34
  E_ACTUATOR_V_DELAY_1,         // 35
  E_ACTUATOR_V_DELAY_2,         // 36
  E_ACTUATOR_V_DELAY_3,         // 37
  E_INIT_SYSTEM_ON_OFF,         // 38
  E_MIXER_DELAY_START,          // 39
  E_EMERGENCY_STOP,             // 40
  E_HEARTBIT,                   // 41
  E_HEARTBIT_START_STOP,        // 42
  E_HEARTBIT_FREQ,              // 43

  E_ACTUATOR_V_SPEED,           // 44
  E_ACTUATOR_V_TIME,            // 45
  E_ACTUATOR_V_UP_TOP,          // 46
  E_ACTUATOR_V_DOWN_MID,        // 47
  E_ACTUATOR_V_DOWN_BOT,        // 48

  E_ACTUATOR_H_SPEED,           // 49
  E_ACTUATOR_H_TIME,            // 50
  E_ACTUATOR_H_IN,              // 51
  E_ACTUATOR_H_OUT,             // 52

  E_VERSION = (REG_R_MAX - 2),  // 124
  E_SUBVERSION = (REG_R_MAX - 1)// 125
};

int RegInit(void);
int RegUpdate(void);
int RegGet(uint8_t register);
int RegSet(uint8_t register, int value);
int IsRegNewValueu(uint8_t register);

#endif // _REG_H
