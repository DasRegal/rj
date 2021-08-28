#include <stdint.h>
#include <SPI.h>
#include <Ethernet.h>
#include "periph.h"
#include "act.h"
#include "endstop.h"
#include "shredder.h"
#include "reg.h"
#include "mixer.h"
#include "dispenser.h"
#include "servo.h"
#include "pump.h"
#include "emergency_stop.h"

void setup()
{
    uint8_t mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
    Ethernet.begin(mac);
    delay(1000);
    Serial.begin(9600);

    Serial.println("Started");

    Serial.print("- Arduino's IP address   : ");
    Serial.println(Ethernet.localIP());

    Serial.print("- Gateway's IP address   : ");
    Serial.println(Ethernet.gatewayIP());

    Serial.print("- Network's subnet mask  : ");
    Serial.println(Ethernet.subnetMask());

    Serial.print("- DNS server's IP address: ");
    Serial.println(Ethernet.dnsServerIP());

    RegInit();
    ActInit();
    ShredderInit();
    MixerInit();
    DispenserInit();
    ServoInit();
    PumpInit();
}

void loop() {
    RegUpdate();
    ShredderOnOff_1(RegGet(E_SHREDDER_ON_OFF_1));
    ShredderOnOff_2(RegGet(E_SHREDDER_ON_OFF_2));
    ActuatorUp(RegGet(E_ACTUATOR_V_UP_TOP));
    ActuatorDownMid(RegGet(E_ACTUATOR_V_DOWN_MID));
    ActuatorDownBot(RegGet(E_ACTUATOR_V_DOWN_BOT));
    ActuatorIn(RegGet(E_ACTUATOR_H_IN));
    ActuatorOut(RegGet(E_ACTUATOR_H_OUT));
    MixerOnOff(RegGet(E_MIXER_ON_OFF));
    DispDryOnOff(RegGet(E_DISPENSER_DRY_ON_OFF));
    DispLiqOnOff(RegGet(E_DISPENSER_LIQ_ON_OFF));
    ServoSet(RegGet(E_SERVO_PWM));
    PumpOnOff(RegGet(E_PUMP_ON_OFF));
    EmergencyStop(RegGet(E_EMERGENCY_STOP));
}
