#include "dispenser.h"

static int isStartDry   = 0;
static int isStartLiq   = 0;
static int dispDry_old  = 0;
static int dispDryCnt   = 0;
static uint8_t isEmergencyStop = 0;
static unsigned long liqTimer;

int DispenserInit(void)
{
    pinMode(PIN_DISP_MOTOR_DRY, OUTPUT);
    pinMode(PIN_DISP_MOTOR_LIQ, OUTPUT);
    pinMode(PIN_ENDSTOP_DISP_DRY, INPUT);
}

int DispDryOnOff(int state)
{
    if(state)
    {
        if (!isStartDry)
        {
            isStartDry = 1;
            dispDry_old = digitalRead(PIN_ENDSTOP_DISP_DRY);
            digitalWrite(PIN_DISP_MOTOR_DRY, 1);
            Serial.println("[Dispenser] Disp Dry Start");
        }
        else
        {
            if (dispDry_old != digitalRead(PIN_ENDSTOP_DISP_DRY))
            {
                dispDry_old = digitalRead(PIN_ENDSTOP_DISP_DRY);
                if (digitalRead(PIN_ENDSTOP_DISP_DRY))
                {
                    dispDryCnt++;
                }
            }

            if (dispDryCnt >= RegGet(E_DISPENSER_DRY_COUNT))
            {
                dispDryCnt = 0;
                isStartDry = 0;
                RegSet(E_DISPENSER_DRY_ON_OFF, 0);
                digitalWrite(PIN_DISP_MOTOR_DRY, 0);
                Serial.println("[Dispenser] Disp Dry Stop By Count");
            }
        }
    }
    else
    {
        if (isStartDry)
        {
            Serial.println("[Dispenser] Disp Dry Stop By State");
        }

        isStartDry = 0;
        dispDryCnt = 0;
        digitalWrite(PIN_DISP_MOTOR_DRY, 0);
    }

    return 0;
}

int DispLiqOnOff(int state)
{
    if (state)
    {
        if (!isStartLiq)
        {
            isStartLiq = 1;
            digitalWrite(PIN_DISP_MOTOR_LIQ, 1);
            Serial.println("[Dispenser] Disp Liq Start");
            liqTimer = millis();
        }
        else
        {
            if (millis() - liqTimer >= (RegGet(E_DISPENSER_LIQ_TIME) * 1000))
            {
                digitalWrite(PIN_DISP_MOTOR_LIQ, 0);
                isStartLiq = 0;
                RegSet(E_DISPENSER_LIQ_ON_OFF, 0);
                Serial.println("[Dispenser] Disp Liq Stop By Timer");
            }
        }
    }
    else
    {
        if (isStartLiq)
        {
            Serial.println("[Dispenser] Disp Liq Stop By State");
        }
        isStartLiq = 0;
        digitalWrite(PIN_DISP_MOTOR_LIQ, 0);
    }

    return 0;
}

void DispenserEmergencyStop(uint8_t state)
{
    if (state)
    {
        if (!isEmergencyStop)
        {
            isEmergencyStop = 1;
            isStartDry = 0;
            isStartLiq = 0;
            digitalWrite(PIN_DISP_MOTOR_DRY, 0);
            digitalWrite(PIN_DISP_MOTOR_LIQ, 0);
            RegSet(E_DISPENSER_DRY_ON_OFF, 0);
            RegSet(E_DISPENSER_LIQ_ON_OFF, 0);
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