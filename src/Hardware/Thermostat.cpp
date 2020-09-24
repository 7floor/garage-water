#include "Thermostat.h"
#include <Arduino.h>
#include "Hub.h"

Thermostat::Thermostat()
{
	setTarget(0);

	PT_INIT(&pt);
}

void Thermostat::setTarget(uint8_t value)
{
	_target = constrain(value, 0, 60);
}

uint8_t Thermostat::getTarget()
{
	return _target;
}

PT_THREAD() Thermostat::run()
{
	PT_BEGIN(&pt);
  
	for(;;)
	{
		while (!hub.thermometer.isValid())
		{
			hub.heater.setHeat(0);
			PT_YIELD(&pt);
		}

		float actual = hub.thermometer.getValue();
		float error = _target - actual;
		float action = 0.3 * error;
		action = constrain(action, 0, 1);
		hub.heater.setHeat(action * 100);
		PT_SLEEP(&pt, 500); // for i/d
	}
  
	PT_END(&pt);
}

