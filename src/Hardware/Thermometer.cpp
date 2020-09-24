#include "Thermometer.h"
#include <Arduino.h>

Thermometer::Thermometer(uint8_t pin)
{
	_ds = new MicroDS18B20(pin);
	_ds->setResolution(10);
	PT_INIT(&pt);
}

float Thermometer::getValue()
{
	return _value;
}

bool Thermometer::isValid()
{
	return _isValid;
}

PT_THREAD() Thermometer::run()
{
	static uint8_t fails;
  
	PT_BEGIN(&pt);
  
	for(;;)
	{
		_ds->requestTemp();
		PT_SLEEP(&pt, 100); // < 100 us for 9 bit resolution, 200 for 10 bit
		float t = _ds->getTemp();
		if (t == 0) // invalid value, todo: change in library to some impossible value
		{
			fails++;
			if (fails > 10)
			{
				fails = 10; // to not overflow
				_isValid = false;
			}
		}
		else
		{
			fails = 0;
			_value = t;
			_isValid = true;
		}
	}
  
	PT_END(&pt);
}

