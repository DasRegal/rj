#include "Arduino.h"
#include "pump.h"
#include "periph.h"
#include "reg.h"

static int isStartPump          = 0;
static uint8_t isEmergencyStop  = 0;
static unsigned long pumpTimer;

int PumpInit(void)
{
    pinMode(PIN_PUMP, OUTPUT);
    return 0;
}

int PumpOnOff(int state)
{
    if (state)
    {
        if (isEmergencyStop)
        {
            RegSet(E_PUMP_ON_OFF, 0);
            return 0;
        }

        if (!isStartPump)
        {
            isStartPump = 1;
            digitalWrite(PIN_PUMP, 1);
            Serial.println("[Pump] Pump Start");
            pumpTimer = millis();
        }
        else
        {
            if (millis() - pumpTimer >= (RegGet(E_FLUSH_TIME) * 1000))
            {
                digitalWrite(PIN_PUMP, 0);
                isStartPump = 0;
                RegSet(E_PUMP_ON_OFF, 0);
                Serial.println("[Pump] Pump Stop By Timer");
            }
        }
    }
    else
    {
        if (isStartPump)
        {
            Serial.println("[Pump] Pump Stop By State");
        }
        isStartPump = 0;
        digitalWrite(PIN_PUMP, 0);
    }
    return 0;
}

void PumpEmergencyStop(uint8_t state)
{
    if (state)
    {
        if (!isEmergencyStop)
        {
            isEmergencyStop = 1;
            isStartPump = 0;
            digitalWrite(PIN_PUMP, 0);
            RegSet(E_PUMP_ON_OFF, 0);
            Serial.println("[Pump] Emergency Stop");
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