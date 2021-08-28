#include "Arduino.h"
#include "emergency_stop.h"
#include "act.h"
#include "dispenser.h"
#include "mixer.h"
#include "pump.h"
#include "servo.h"
#include "shredder.h"

void EmergencyStop(uint8_t state)
{
	ActEmergencyStop(state);
	DispenserEmergencyStop(state);
	MixerEmergencyStop(state);
	PumpEmergencyStop(state);
	ServoEmergencyStop(state);
	ShredderEmergencyStop(state);
}