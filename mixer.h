#ifndef _MIXER_H
#define _MIXER_H

int MixerInit(void);
void MixerOnOff(int state);
void MixerEmergencyStop(uint8_t state);

#endif // _MIXER_H
