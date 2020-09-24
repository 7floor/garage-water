#include "Thermometer.h"
#include <Arduino.h>

Thermometer::Thermometer(uint8_t pin)
{
	_ds = new MicroDS18B20(pin);
	_ds->setResolution(10);
	_valid = false;
	_requested = false;
	_temperature = 0;
}

float Thermometer::getTemperature()
{
	if (_requested)
	{
		_requested = false;
		_temperature = _ds->getTemp();
		_valid = _temperature > 0;
	}
	return _temperature;
}

bool Thermometer::valid()
{
	return _valid;
}

void Thermometer::request()
{
	_requested = true;
	_ds->requestTemp();
}
