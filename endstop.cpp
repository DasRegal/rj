#include <Controllino.h> 
#include "Arduino.h"
#include "endstop.h"
#include "periph.h"

int EndstopInit(void)
{
    pinMode(PIN_ENDSTOP_HOR_IN, INPUT);         // Endstop H Actuator IN Зелен
    pinMode(PIN_ENDSTOP_HOR_OUT, INPUT);        // Endstop H Actuator OUT Оранж

    pinMode(PIN_ENDSTOP_VER_TOP, INPUT);        // Endstop V Actuator TOP Синий
    pinMode(PIN_ENDSTOP_VER_MID, INPUT);        // Endstop V Actuator MID Белый
    pinMode(PIN_ENDSTOP_VER_BOT, INPUT);        // Endstop V Actuator BOT Желтый

    pinMode(PIN_ENDSTOP_DISP_DRY, INPUT);       // Endstop Dry Disp
    pinMode(CONTROLLINO_A6, INPUT);     // Endstop Shredder 1
    pinMode(CONTROLLINO_A7, INPUT);     // Endstop Shredder 2

    return 0;
}

int IsEndstop(uint8_t pin)
{
    if (digitalRead(pin) == 0)
    {
        return 1;
    }

    return 0;
}
