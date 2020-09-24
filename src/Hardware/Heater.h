#pragma once
#include <Arduino.h>

class Heater {
public:
	Heater(uint8_t pin);

	void setState(bool state);	

private:
	uint8_t _pin;
};