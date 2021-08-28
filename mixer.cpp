#include "mixer.h"
#include "periph.h"

static uint8_t isEmergencyStop = 0;

int MixerInit(void)
{
    pinMode(PIN_MIXER, OUTPUT);  // Mixer
}

void MixerOnOff(int state)
{
    digitalWrite(PIN_MIXER, state);
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