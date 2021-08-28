#include <stdint.h>
#include "periph.h"
#include "act.h"
#include "endstop.h"
#include "shredder.h"
#include "reg.h"
#include "mixer.h"

void setup()
{
    RegInit();
    ActInit();
    ShredderInit();
    MixerInit();
}

void loop() {
    RegUpdate();
    ShredderOnOff_1(RegGet(E_SHREDDER_ON_OFF_1));
    ShredderOnOff_2(RegGet(E_SHREDDER_ON_OFF_2));
    ActuatorUp(RegGet(E_ACTUATOR_V_UP_TOP));
    ActuatorDownMid(RegGet(E_ACTUATOR_V_DOWN_MID));
    ActuatorDownBot(RegGet(E_ACTUATOR_V_DOWN_BOT));
    // MixerOnOff(RegGet());
}
