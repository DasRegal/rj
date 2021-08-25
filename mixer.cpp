#include <stdint.h>
#include "act.h"
#include "mixer.h"
#include "periph.h"

static uint8_t is_mixerStart = 0;
static uint8_t is_posTop     = 0;
static uint8_t is_postBot    = 0;
static uint8_t is_posMid     = 0;

void MixerInit(void)
{
  is_mixerStart = 0;
  is_posTop     = 0;
  is_postBot    = 0;
  is_posMid     = 0;
}

uint8_t MixerUp(uint8_t speed)
{
  uint8_t res = -1;

  if (digitalRead(PIN_ENDSTOP_VER_TOP) == 0)
  {
    if (!is_posTop)
    {
      is_posTop = 1;
      res = 1;
      ActVUnblock();
      ActStopV();
      ActDisableV();
    }
  }
  
  if (!is_mixerStart)
  {
    is_mixerStart = 1;
    ActEnableV();
    ActUp(speed);
    ActVBlock();
  }
  else
  {
    if (digitalRead(PIN_ENDSTOP_VER_TOP) == 0)
    {
      ActVUnblock();
      
    }
  }
}

void Mixer(uint8_t state)
{
  if (state)
  {
    }
}
