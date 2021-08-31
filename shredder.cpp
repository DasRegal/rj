#include <Controllino.h> 
#include "Arduino.h"
#include "shredder.h"
#include "periph.h"
#include "endstop.h"
#include "reg.h"

static uint8_t isEmergencyStop = 0;
static uint8_t isShredderStart_1 = 0;
static uint8_t isShredderStart_2 = 0;

void ShredderInit(void)
{
  pinMode(PIN_SHREDDER_1, OUTPUT);  // Shredder 1
  pinMode(PIN_SHREDDER_2, OUTPUT);  // Shredder 2
  isEmergencyStop = 0;
  isShredderStart_1 = 0;
  isShredderStart_2 = 0;
}

uint8_t ShredderOnOff_1(uint8_t state)
{
    if (isEmergencyStop)
    {
        RegSet(E_SHREDDER_ON_OFF_1, 0);
        return 1;
    }

    if (state)
    {
        if (!digitalRead(CONTROLLINO_A6))
        {
            if (!isShredderStart_1)
            {
                isShredderStart_1 = 1;
                Serial.println("[Shredder 1] Start");
                digitalWrite(PIN_SHREDDER_1, 1);
            }
        }
        else
        {
            isShredderStart_1 = 0;
            Serial.println("[Shredder 1] Stop by EndStop");
            digitalWrite(PIN_SHREDDER_1, 0);
            RegSet(E_SHREDDER_ON_OFF_1, 0);
            state = 0;
        }
    }
    else
    {
        if (isShredderStart_1)
        {
            isShredderStart_1 = 0;
            Serial.println("[Shredder 1] Stop by State");
            digitalWrite(PIN_SHREDDER_1, 0);
        }
    }

    return 0;
}

uint8_t ShredderOnOff_2(uint8_t state)
{
    if (isEmergencyStop)
    {
        RegSet(E_SHREDDER_ON_OFF_2, 0);
        return 1;
    }

    if (state)
    {
        if (!digitalRead(CONTROLLINO_A7))
        {
            if (!isShredderStart_2)
            {
                isShredderStart_2 = 1;
                Serial.println("[Shredder 2] Start");
                digitalWrite(PIN_SHREDDER_2, 1);
            }
        }
        else
        {
            isShredderStart_2 = 0;
            Serial.println("[Shredder 2] Stop by EndStop");
            digitalWrite(PIN_SHREDDER_2, 0);
            RegSet(E_SHREDDER_ON_OFF_2, 0);
            state = 0;
        }
    }
    else
    {
        if (isShredderStart_2)
        {
            isShredderStart_2 = 0;
            Serial.println("[Shredder 2] Stop by State");
            digitalWrite(PIN_SHREDDER_2, 0);
        }
    }

    return 0;
}

void ShredderEmergencyStop(uint8_t state)
{
    if (state)
    {
        if (!isEmergencyStop)
        {
            isEmergencyStop = 1;
            isShredderStart_1 = 0;
            isShredderStart_2 = 0;
            digitalWrite(PIN_SHREDDER_1, 0);
            digitalWrite(PIN_SHREDDER_2, 0);
            RegSet(E_SHREDDER_ON_OFF_1, 0);
            RegSet(E_SHREDDER_ON_OFF_2, 0);
            Serial.println("[Shredder 1] Emergency Stop");
            Serial.println("[Shredder 2] Emergency Stop");
        }  
    }
    else
    {
        if (isEmergencyStop)
        {
            isEmergencyStop = 0;
        }
    }
}

