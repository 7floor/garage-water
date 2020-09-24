#include "Heater.h"
#include <Arduino.h>

Heater::Heater(uint8_t pin)
{
	_pin = pin;
	pinMode(_pin, OUTPUT);
	setState(false);
}

void Heater::setState(bool state)
{
	digitalWrite(_pin, state);
}
