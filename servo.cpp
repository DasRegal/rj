#include <Adafruit_PWMServoDriver.h>
#include "servo.h"
#include "reg.h"

static Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40); // Установка адреса I2C 0x40
static int oldVal = 441;
static uint8_t isEmergencyStop = 0;

int ServoInit(void)
{
    pwm.begin();
    pwm.setOscillatorFrequency(26000000);
    pwm.setPWMFreq(50);
    delay(10);
    pwm.setPWM(0, 0, 441);
    return 0;
}

int ServoSet(int val)
{
    if (oldVal != RegGet(E_SERVO_PWM))
    {
        oldVal = RegGet(E_SERVO_PWM);
        pwm.setPWM(0, 0, oldVal);
        Serial.println("[Servo] New value");
    }

    return 0;
}

void ServoEmergencyStop(uint8_t state)
{
    if (state)
    {
        if (!isEmergencyStop)
        {
            isEmergencyStop = 1;
            RegSet(E_SERVO_PWM, 441);
            pwm.setPWM(0, 0, 441);
            Serial.println("[Servo] Emergency Stop");
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