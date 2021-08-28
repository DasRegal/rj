#include "BTS7960.h"
#include "Arduino.h"
#include "act.h"
#include "periph.h"

static BTS7960 motorActV(PIN_ACTUATOR_VERTICAL_L_EN, PIN_ACTUATOR_VERTICAL_R_EN,
                  PIN_ACTUATOR_VERTICAL_L_PWM, PIN_ACTUATOR_VERTICAL_R_PWM);
static BTS7960 motorActH(PIN_ACTUATOR_HORIZONTAL_L_EN, PIN_ACTUATOR_HORIZONTAL_R_EN,
                  PIN_ACTUATOR_HORIZONTAL_L_PWM, PIN_ACTUATOR_HORIZONTAL_R_PWM);
                  
static uint8_t is_actVBusy = 0;
static uint8_t is_actHBusy = 0;
static uint8_t isEmergencyStop = 0;

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
    return 0;
    
  if (is_actHBusy)
  {
    Serial.println("[Actuator] Horizontal In is busy");
    return 1;
  }

  
  motorActH.TurnLeft(speed);
  
  return 0;
}

int ActOut(uint8_t speed)
{
  if (isEmergencyStop)
    return 0;
    
  if (is_actHBusy)
  {
    Serial.println("[Actuator] Horizontal Out is busy");
    return 1;
  }

  motorActH.TurnRight(speed);
  
  return 0;
}

int ActUp(uint8_t speed)
{
  if (isEmergencyStop)
    return 0;

  if (is_actVBusy)
  {
    Serial.println("[Actuator] Vertical Up is busy");
    return 1;
  }

  motorActV.TurnRight(speed);
  
  return 0;
}

int ActDown(uint8_t speed)
{
  if (isEmergencyStop)
    return 0;

  if (is_actVBusy)
  {
    Serial.println("[Actuator] Vertical Down is busy");
    return 1;
  }

  motorActV.TurnLeft(speed);
  
  return 0;
}

int ActStopV(void)
{
  if (isEmergencyStop)
    return 0;

  if (is_actVBusy)
  {
    Serial.println("[Actuator] Vertical Stop is busy");
    return 1;
  }

  motorActV.Stop();
  
  return 0;
}

int ActStopH(void)
{
  if (isEmergencyStop)
    return 0;

  if (is_actHBusy)
  {
    Serial.println("[Actuator] Horizontal Stop is busy");
    return 1;
  }

  motorActH.Stop();
  
  return 0;
}

int ActDisableV(void)
{
  if (isEmergencyStop)
    return 0;

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
    return 0;

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
    return 0;

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
    return 0;

  if (is_actHBusy)
  {
    Serial.println("[Actuator] Horizontal Enable is busy");
    return 1;
  }

  motorActH.Enable();
  
  return 0;
}

void ActEmergencyStop(uint8_t state)
{
  if (state)
  {
    if (!isEmergencyStop)
    {
      isEmergencyStop = 1;
      motorActH.Disable();
      motorActV.Disable();
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
