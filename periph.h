#ifndef _PERIPH_H
#define _PERIPH_H

#include "Arduino.h"

#define PIN_ACTUATOR_VERTICAL_L_EN    9   // D7/PH6 HEADER X2
#define PIN_ACTUATOR_VERTICAL_R_EN    11  // D9/PB5 HEADER X2
#define PIN_ACTUATOR_VERTICAL_L_PWM   3   // D1/PE5 HEADER X1
#define PIN_ACTUATOR_VERTICAL_R_PWM   5   // D3/PE3 HEADER X1

#define PIN_ACTUATOR_HORIZONTAL_L_EN  10  // D8/PB4 HEADER X2
#define PIN_ACTUATOR_HORIZONTAL_R_EN  12  // D10/PB6 HEADER X2
#define PIN_ACTUATOR_HORIZONTAL_L_PWM 4   // D2/PG5 HEADER X1
#define PIN_ACTUATOR_HORIZONTAL_R_PWM 6   // D4/PH3 HEADER X1

#define PIN_SHREDDER_1                28  // R6/PA6 RELAY R6
#define PIN_SHREDDER_2                29  // R7/PA7 RELAY R7

#define PIN_ENDSTOP_HOR_IN            A0  // A0/PF0 INPUT A0
#define PIN_ENDSTOP_HOR_OUT           A1  // A1/PF1 INPUT A1

#define PIN_ENDSTOP_VER_TOP           A2  // A2/PF2 INPUT A2
#define PIN_ENDSTOP_VER_MID           A3  // A3/PF3 INPUT A3
#define PIN_ENDSTOP_VER_BOT           A4  // A4/PF4 INPUT A4

#define PIN_ENDSTOP_DISP_DRY          A5  // A5/PF5 INPUT A5
#define PIN_ENDSTOP_SHREDDER_1        A6  // 
#define PIN_ENDSTOP_SHREDDER_2        A7  // 
#define PIN_DISP_MOTOR_DRY            26  // R4/PA4 RELAY R4

#define PIN_DISP_MOTOR_LIQ            7   // D5/PH4 HEADER X1

#define PIN_MIXER                     30  // R8/PC7 RELAY R8
#define PIN_PUMP                      22  // R0/PA0 RELAY R0

#endif // _PERIPH_H
