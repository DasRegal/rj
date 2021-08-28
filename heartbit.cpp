#include "Arduino.h"
#include "heartbit.h"
#include "reg.h"

static int isStartHeartbit = 0;
static unsigned long heartbitTimer;
static int isHbSet;

void HeartbitInit(void)
{
	isHbSet = 0;
}

void HeartBit(int state)
{
	if (state)
    {
        if (!isStartHeartbit)
        {
            isStartHeartbit = 1;
            Serial.println("[Heartbit] Start");
            heartbitTimer = millis();
        }
        else
        {
            if (millis() - heartbitTimer >= (RegGet(E_HEARTBIT_FREQ)))
            {
                if (!isHbSet)
                {
                	isHbSet = 1;
                	Serial.println("[Heartbit]");
                }
                else
                {
                	isHbSet = 0;
                }
            	RegSet(E_HEARTBIT, isHbSet);

            	heartbitTimer = millis();
            }
        }
    }
    else
    {
        if (isStartHeartbit)
        {
            Serial.println("[Heartbit] Stop");
        }
        isStartHeartbit = 0;
    }
}