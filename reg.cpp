#include "reg.h"
#include "Mudbus.h"

static Mudbus Mb;
static int curValue[REG_R_MAX];

static void RegInitValues(void)
{
    // RegSet(E_ACTUATOR_V_SPEED_1, 400);
}

int RegInit(void)
{
    Mb.Run();
    RegInitValues();
    for (uint8_t i = 0; i < REG_R_MAX; i++)
    {
        curValue[i] = Mb.R[i];
    }
    return 0;
}

int RegUpdate(void)
{
    Mb.Run();
    return 0;
}

int RegGet(uint8_t reg)
{
    return Mb.R[reg];
}

int RegSet(uint8_t reg, int value)
{
    Mb.R[reg] = value;
    return 0;
}

int IsRegNewValueu(uint8_t reg)
{
    if (curValue[reg] != Mb.R[reg])
    {
        curValue[reg] = Mb.R[reg];
        return 1;
    }

    return 0;
}