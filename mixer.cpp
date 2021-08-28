#include "mixer.h"
#include "periph.h"

int MixerInit(void)
{
    pinMode(PIN_MIXER, OUTPUT);  // Mixer
}

void MixerOnOff(int state)
{
    digitalWrite(PIN_MIXER, state);
}