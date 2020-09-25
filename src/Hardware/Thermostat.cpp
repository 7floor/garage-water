#include "Thermostat.h"
#include <Arduino.h>
#include "Hub.h"

Thermostat::Thermostat()
{
	setTarget(0);

	PT_INIT(&pt);
}

void Thermostat::setTarget(float value)
{
	_target = constrain(value, 0, 60);
	_integral = 0;
	_lasterror = 0;
}

float Thermostat::getTarget()
{
	return _target;
}

PT_THREAD() Thermostat::run()
{
	static uint16_t ontime;
	PT_BEGIN(&pt);
  
	for(;;)
	{
		float actual = hub.thermometer.getTemperature();

		if (!hub.thermometer.valid())
		{
			hub.heater.setState(false);
			hub.thermometer.request();
			hub.buzzer.beep(20);
			PT_SLEEP(&pt, Dt);
			continue;
		}

		hub.thermometer.request();

		float error = _target - actual;

		// Proportional
		float action = Kp * error;

		// Differential
		action = action + Kd * (error - _lasterror);

		float intdelta = (error + _lasterror) / 2;
		
		// stop integration for saturated action
		if (action > 1 && intdelta > 0) intdelta = 0;
		if (action < 0 && intdelta < 0) intdelta = 0;

		_integral = _integral + intdelta;
		_integral = constrain(_integral, -1, +1); // constrain integral
		action = action + Ki * _integral;

		// constrain action
		action = constrain(action, 0, 1);

		_lasterror = error;

		ontime = action * Dt;
		if (ontime > 0)
		{
			hub.heater.setState(true);
			PT_SLEEP(&pt, ontime);
		}
		if (ontime < Dt)
		{
			hub.heater.setState(false);
			PT_SLEEP(&pt, Dt - ontime);
		}
	}
  
	PT_END(&pt);
}

