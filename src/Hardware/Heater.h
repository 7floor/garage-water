#pragma once
#include <Arduino.h>
#include "../Protothreads/protothreads.h"
#define ONE_PERCENT_TIME 5

class Heater {
public:
	Heater(uint8_t pin);
	
	void setHeat(uint8_t heat);
	uint8_t getHeat();

	PT_THREAD() run();
	
private:
	pt pt;
	uint8_t _pin;
	uint8_t _heat;
};