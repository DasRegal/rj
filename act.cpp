#include "BTS7960.h"
#include "Arduino.h"
#include "act.h"
#include "periph.h"
#include "reg.h"
#include "endstop.h"

static BTS7960 motorActV(PIN_ACTUATOR_VERTICAL_L_EN, PIN_ACTUATOR_VERTICAL_R_EN,
                  PIN_ACTUATOR_VERTICAL_L_PWM, PIN_ACTUATOR_VERTICAL_R_PWM);
static BTS7960 motorActH(PIN_ACTUATOR_HORIZONTAL_L_EN, PIN_ACTUATOR_HORIZONTAL_R_EN,
                  PIN_ACTUATOR_HORIZONTAL_L_PWM, PIN_ACTUATOR_HORIZONTAL_R_PWM);
                  
static uint8_t is_actVBusy      = 0;
static uint8_t is_actHBusy      = 0;
static uint8_t isEmergencyStop  = 0;
static uint8_t is_UpStart       = 0;
static uint8_t is_DownMidStart  = 0;
static uint8_t is_DownBotStart  = 0;
static uint8_t is_ActInStart    = 0;
static uint8_t is_ActOutStart   = 0;

int ActInit(void)
{
  is_actVBusy     = 0;
  is_actHBusy     = 0;
  isEmergencyStop = 0;

  pinMode(PIN_ENDSTOP_HOR_IN,  INPUT);
  pinMode(PIN_ENDSTOP_HOR_OUT, INPUT);

  pinMode(PIN_ENDSTOP_VER_TOP, INPUT);
  pinMode(PIN_ENDSTOP_VER_MID, INPUT);
  pinMode(PIN_ENDSTOP_VER_BOT, INPUT);
  
  return 0;
}

int ActVBlock(void)
{
  is_actVBusy = 1;
  return 0;
}

int ActHBlock(void)
{
  is_actHBusy = 1;
  return 0;
}

int ActVUnblock(void)
{
  is_actVBusy = 0;
  return 0;
}

int ActHUnblock(void)
{
  is_actHBusy = 0;
  return 0;
}

int ActIn(uint8_t speed)
{
  if (isEmergencyStop)
    return 1;
    
  if (is_actHBusy)
  {
    Serial.println("[Actuator] Horizontal IN is busy");
    return 1;
  }

  Serial.println("[Actuator] Horizontal IN start");
  motorActH.TurnLeft(speed);
  
  return 0;
}

int ActOut(uint8_t speed)
{
    if (isEmergencyStop)
    {
        Serial.println("[Actuator] Horizontal Actuator Out Emergency Stop");
        return 1;
    }
    
    if (is_actHBusy)
    {
        Serial.println("[Actuator] Horizontal OUT is busy");
        return 1;
    }

    Serial.println("[Actuator] Horizontal OUT start");
    motorActH.TurnRight(speed);

    return 0;
}

int ActUp(uint8_t speed)
{
    if (isEmergencyStop)
    {
        Serial.println("[Actuator] Vertical Actuator Up Emergency Stop");
        return 1;
    }

    if (is_actVBusy)
    {
        return 1;
    }

    Serial.println("[Actuator] Vertical UP start");
    motorActV.TurnRight(speed);

    return 0;
}

int ActDown(uint8_t speed)
{
    if (isEmergencyStop)
    {
        Serial.println("[Actuator] Vertical Actuator Down Emergency Stop");
        return 1;
    }

    if (is_actVBusy)
    {
        return 1;
    }

    Serial.println("[Actuator] Vertical DOWN start");
    motorActV.TurnLeft(speed);

    return 0;
}

int ActStopV(void)
{
    if (isEmergencyStop)
    {
        Serial.println("[Actuator] Vertical Actuator Stop Emergency Stop");
        return 1;
    }

    if (is_actVBusy)
    {
        Serial.println("[Actuator] Vertical Stop is busy");
        return 1;
    }

    Serial.println("[Actuator] Vertical Stop");
    motorActV.Stop();

    return 0;
}

int ActStopH(void)
{
    if (isEmergencyStop)
    {
        Serial.println("[Actuator] Horizontal Actuator Stop Emergency Stop");
        return 0;
    }

    if (is_actHBusy)
    {
        Serial.println("[Actuator] Horizontal Stop is busy");
        return 1;
    }

    Serial.println("[Actuator] Horizontal Stop");
    motorActH.Stop();

    return 0;
}

int ActDisableV(void)
{
    if (isEmergencyStop)
    {
        Serial.println("[Actuator] Vertical Actuator Disable Emergency Stop");
        return 1;
    }

    if (is_actVBusy)
    {
        Serial.println("[Actuator] Vertical Disable is busy");
        return 1;
    }

    motorActV.Disable();

    return 0;
}

int ActDisableH(void)
{
    if (isEmergencyStop)
    {
        Serial.println("[Actuator] Horizontal Actuator Disable Emergency Stop");
        return 0;
    }

    if (is_actHBusy)
    {
        Serial.println("[Actuator] Horizontal Disable is busy");
        return 1;
    }

    motorActH.Disable();

    return 0;
}

int ActEnableV(void)
{
    if (isEmergencyStop)
    {
        Serial.println("[Actuator] Vertical Actuator Enable Emergency Stop");
        return 1;
    }

    if (is_actVBusy)
    {
        Serial.println("[Actuator] Vertical Enable is busy");
        return 1;
    }

    motorActV.Enable();

    return 0;
}

int ActEnableH(void)
{
    if (isEmergencyStop)
    {
        Serial.println("[Actuator] Horizontal Actuator Enable Emergency Stop");
        return 1;
    }

    if (is_actHBusy)
    {
        Serial.println("[Actuator] Horizontal Enable is busy");
        return 1;
    }

    motorActH.Enable();

    return 0;
}

int ActuatorUp(uint8_t state)
{
    volatile unsigned long actVTimer;
    if (state)
    {
        if (!is_UpStart)
        {
            is_UpStart = 1;
            if (ActUp(RegGet(E_ACTUATOR_V_SPEED)) == 0)
            {
                ActVBlock();
                actVTimer = millis();
            }
            else
            {
                Serial.println("[Actuator Up] Start Error");
                RegSet(E_ACTUATOR_V_UP_TOP, 0);
                is_UpStart = 0;
                return 1;
            }
        }

        if (millis() - actVTimer >= (RegGet(E_ACTUATOR_V_TIME) * 1000) ||
            IsEndstop(PIN_ENDSTOP_VER_TOP))
        {
            ActVUnblock();
            ActStopV();
            RegSet(E_ACTUATOR_V_UP_TOP, 0);
            is_UpStart = 0;
            Serial.println("[Actuator Up] Stop by Event");
        }

        return 0;
    }
    else
    {
        if (is_UpStart)
        {
            ActVUnblock();
            ActStopV();
            is_UpStart = 0;
            Serial.println("[Actuator Up] Stop by State");
        }

        return 0;
    }
}

int ActuatorDownMid(uint8_t state)
{
    volatile unsigned long actVTimer;
    if (state)
    {
        if (!is_DownMidStart)
        {
            is_DownMidStart = 1;
            if (ActDown(RegGet(E_ACTUATOR_V_SPEED)) == 0)
            {
                ActVBlock();
                actVTimer = millis();
            }
            else
            {
                Serial.println("[Actuator Down Mid] Start Error");
                RegSet(E_ACTUATOR_V_DOWN_MID, 0);
                is_DownMidStart = 0;
                return 1;
            }
        }

        if (millis() - actVTimer >= (RegGet(E_ACTUATOR_V_TIME) * 1000) ||
            IsEndstop(PIN_ENDSTOP_VER_MID))
        {
            ActVUnblock();
            ActStopV();
            RegSet(E_ACTUATOR_V_DOWN_MID, 0);
            is_DownMidStart = 0;
            Serial.println("[Actuator Down Mid] Stop by Event");
        }

        return 0;
    }
    else
    {
        if (is_DownMidStart)
        {
            ActVUnblock();
            ActStopV();
            is_DownMidStart = 0;
            Serial.println("[Actuator Down Mid] Stop by State");
        }

        return 0;
    }
}

int ActuatorDownBot(uint8_t state)
{
    volatile unsigned long actVTimer;
    if (state)
    {
        if (!is_DownBotStart)
        {
            is_DownBotStart = 1;
            if (ActDown(RegGet(E_ACTUATOR_V_SPEED)) == 0)
            {
                ActVBlock();
                actVTimer = millis();
            }
            else
            {
                Serial.println("[Actuator Down Bot] Start Error");
                RegSet(E_ACTUATOR_V_DOWN_BOT, 0);
                is_DownBotStart = 0;
                return 1;
            }
        }

        if (millis() - actVTimer >= (RegGet(E_ACTUATOR_V_TIME) * 1000) ||
            IsEndstop(PIN_ENDSTOP_VER_BOT))
        {
            ActVUnblock();
            ActStopV();
            RegSet(E_ACTUATOR_V_DOWN_BOT, 0);
            is_DownBotStart = 0;
            Serial.println("[Actuator Down Bot] Stop by Event");
        }

        return 0;
    }
    else
    {
        if (is_DownBotStart)
        {
            ActVUnblock();
            ActStopV();
            is_DownBotStart = 0;
            Serial.println("[Actuator Down Bot] Stop by State");
        }

        return 0;
    }
}

int ActuatorIn(uint8_t state)
{
    volatile unsigned long actHTimer;
    if (state)
    {
        if (!is_ActInStart)
        {
            is_ActInStart = 1;
            if (ActIn(RegGet(E_ACTUATOR_H_SPEED)) == 0)
            {
                ActHBlock();
                actHTimer = millis();
            }
            else
            {
                Serial.println("[Actuator H In] Start Error");
                RegSet(E_ACTUATOR_H_IN, 0);
                is_ActInStart = 0;
                return 1;
            }
        }

        if (millis() - actHTimer >= (RegGet(E_ACTUATOR_H_TIME) * 1000) ||
            IsEndstop(PIN_ENDSTOP_HOR_IN))
        {
            ActHUnblock();
            ActStopH();
            RegSet(E_ACTUATOR_H_IN, 0);
            is_ActInStart = 0;
            Serial.println("[Actuator H In] Stop by Event");
        }

        return 0;
    }
    else
    {
        if (is_ActInStart)
        {
            ActHUnblock();
            ActStopH();
            is_ActInStart = 0;
            Serial.println("[Actuator H In] Stop by State");
        }

        return 0;
    }
}

int ActuatorOut(uint8_t state)
{
    volatile unsigned long actHTimer;
    if (state)
    {
        if (!is_ActOutStart)
        {
            is_ActOutStart = 1;
            if (ActOut(RegGet(E_ACTUATOR_H_SPEED)) == 0)
            {
                ActHBlock();
                actHTimer = millis();
            }
            else
            {
                Serial.println("[Actuator H Out] Start Error");
                RegSet(E_ACTUATOR_H_OUT, 0);
                is_ActOutStart = 0;
                return 1;
            }
        }

        if (millis() - actHTimer >= (RegGet(E_ACTUATOR_H_TIME) * 1000) ||
            IsEndstop(PIN_ENDSTOP_HOR_OUT))
        {
            ActHUnblock();
            ActStopH();
            RegSet(E_ACTUATOR_H_OUT, 0);
            is_ActOutStart = 0;
            Serial.println("[Actuator H Out] Stop by Event");
        }

        return 0;
    }
    else
    {
        if (is_ActOutStart)
        {
            ActHUnblock();
            ActStopH();
            is_ActOutStart = 0;
            Serial.println("[Actuator H Out] Stop by State");
        }

        return 0;
    }
}

void ActEmergencyStop(uint8_t state)
{
    if (state)
    {
        if (!isEmergencyStop)
        {
            motorActH.Disable();
            motorActV.Disable();
            RegSet(E_ACTUATOR_V_UP_TOP, 0);
            RegSet(E_ACTUATOR_V_DOWN_MID, 0);
            RegSet(E_ACTUATOR_V_DOWN_BOT, 0);
            RegSet(E_ACTUATOR_H_IN, 0);
            RegSet(E_ACTUATOR_H_OUT, 0);
            ActVUnblock();
            ActStopV();
            ActHUnblock();
            ActStopH();
            is_UpStart = 0;
            is_DownMidStart  = 0;
            is_DownBotStart  = 0;
            isEmergencyStop = 1;
        }  
    }
    else
    {
        if (isEmergencyStop)
        {
            motorActH.Enable();
            motorActV.Enable();
            isEmergencyStop = 0;
        }
    }
}
