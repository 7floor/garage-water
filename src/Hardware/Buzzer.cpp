#include "Buzzer.h"
#include <Arduino.h>

Buzzer::Buzzer(uint8_t pin)
{
	_pin = pin;
	pinMode(_pin, OUTPUT);
	off();
	_ms = 0;

	PT_INIT(&pt);
}

void Buzzer::beep(uint8_t ms = 100)
{
	_ms = ms;
	PT_RESTART(&pt);
}

void Buzzer::on()
{
	digitalWrite(_pin, 1);
}

void Buzzer::off()
{
	digitalWrite(_pin, 0);
}


PT_THREAD() Buzzer::run()
{
	PT_BEGIN(&pt);
  
	for(;;)
	{
		PT_WAIT_WHILE(&pt, _ms == 0);
		on();
		PT_SLEEP(&pt, _ms);
		off();
		_ms = 0;
	}
  
	PT_END(&pt);
}

