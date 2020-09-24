#pragma once
#include <Arduino.h>
#include "../Protothreads/protothreads.h"

class Thermostat {
public:
	Thermostat();

	uint8_t getTarget();
	void setTarget(uint8_t value);	

	PT_THREAD() run();
	
private:
	pt pt;
	uint8_t _target;
};
