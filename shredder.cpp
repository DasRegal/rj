#include "shredder.h"
#include "periph.h"

static uint8_t isEmergencyStop = 0;
static uint8_t isShredderStart_1 = 0;
static uint8_t isShredderStart_2 = 0;

void ShredderInit(void)
{
  pinMode(PIN_SHREDDER_1, OUTPUT);  // Shredder 1
  pinMode(PIN_SHREDDER_2, OUTPUT);  // Shredder 2
  isEmergencyStop = 0;
  isShredderStart_1 = 0;
  isShredderStart_2 = 0;
}

//void ShredderOn_1(void)
//{
//  if (isEmergencyStop)
//    return;
//    
//  digitalWrite(PIN_SHREDDER_1, 1);
//}
//
//void ShredderOff_1(void)
//{
//  digitalWrite(PIN_SHREDDER_1, 0);
//}
//
//void ShredderOn_2(void)
//{
//  if (isEmergencyStop)
//    return;
//    
//  digitalWrite(PIN_SHREDDER_2, 1);
//}
//
//void ShredderOff_2(void)
//{
//  digitalWrite(PIN_SHREDDER_2, 0);
//}

uint8_t ShredderOnOff_1(uint8_t state)
{
  if (state)
  {
    if (!isShredderStart_1)
    {
      isShredderStart_1 = 1;
    }
    else
    {
      
    }
  }
  else
  {
    if (isShredderStart_1)
    {
      isShredderStart_1 = 0;
      digitalWrite(PIN_SHREDDER_1, 0);
    }
  }
}

void ShredderEmergencyStop(uint8_t state)
{
  if (state)
  {
    if (!isEmergencyStop)
    {
      isEmergencyStop = 1;
      digitalWrite(PIN_SHREDDER_1, 0);
      digitalWrite(PIN_SHREDDER_2, 0);
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

