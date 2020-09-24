#include "Heater.h"
#include <Arduino.h>

Heater::Heater(uint8_t pin)
{
	_pin = pin;
	pinMode(_pin, OUTPUT);
	setHeat(0);

	PT_INIT(&pt);
}

void Heater::setHeat(uint8_t heat)
{
	_heat = constrain(heat, 0, 100); // 100% max
}

uint8_t Heater::getHeat()
{
	return _heat;
}

PT_THREAD() Heater::run()
{
	static uint16_t onTime;

	PT_BEGIN(&pt);
  
	for(;;)
	{
		onTime = ONE_PERCENT_TIME * _heat;
		if (_heat > 0)
		{
			digitalWrite(_pin, true);
			PT_SLEEP(&pt, onTime);
		}
		if (_heat < 100)
		{
			digitalWrite(_pin, false);
			PT_SLEEP(&pt, ONE_PERCENT_TIME * 100 - onTime);
		}
	}
  
	PT_END(&pt);
}

