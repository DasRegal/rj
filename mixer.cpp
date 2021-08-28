#include "Arduino.h"
#include "mixer.h"
#include "periph.h"
#include "reg.h"

static uint8_t isEmergencyStop = 0;
static int oldState = 0;

int MixerInit(void)
{
    pinMode(PIN_MIXER, OUTPUT);  // Mixer
}

void MixerOnOff(int state)
{
    if (isEmergencyStop)
    {
        RegSet(E_MIXER_ON_OFF, 0);
        return;
    }
    
    if (oldState != state)
    {

        digitalWrite(PIN_MIXER, state);
        if (state)
        {
            Serial.println("[Mixer] Start");
        }
        else
        {
            Serial.println("[Mixer] Stop");
        }
        oldState = state;
    }
}

void MixerEmergencyStop(uint8_t state)
{
    if (state)
    {
        if (!isEmergencyStop)
        {
            isEmergencyStop = 1;
            digitalWrite(PIN_MIXER, 0);
            RegSet(E_MIXER_ON_OFF, 0);
            Serial.println("[Mixer] Emergency Stop");
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