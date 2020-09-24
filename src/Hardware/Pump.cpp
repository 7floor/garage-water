#include "Pump.h"
#include <Arduino.h>

Pump::Pump(uint8_t pin, uint8_t flowSteps, uint8_t minDuty, uint8_t maxDuty)
{
	_pin = pin;
	pinMode(_pin, OUTPUT);

	_flowSteps = flowSteps;
	_minDuty = minDuty;
	_maxDuty = maxDuty;

	setFlow(0);
}

uint8_t Pump::getFlow()
{
	return _flow;
}

void Pump::setFlow(uint8_t flow)
{
	_flow = flow;

	if (_flow > _flowSteps) _flow = _flowSteps;

	uint8_t duty = flow == 0
		? 0
		: _minDuty + (uint16_t)(_maxDuty - _minDuty) * (flow - 1) / _flowSteps;

	analogWrite(_pin, duty);
}

void Pump::changeFlow(int8_t delta)
{
	int8_t newFlow = _flow + delta;
	if (newFlow < 0) newFlow = 0;
	setFlow(newFlow);
}

