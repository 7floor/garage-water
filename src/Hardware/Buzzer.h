#pragma once
#include <Arduino.h>
#include "../Protothreads/protothreads.h"

class Buzzer {
public:
	Buzzer(uint8_t pin);
	
	void beep(uint8_t ms = 100);
	void on();
	void off();

	PT_THREAD() run();
	
private:
	struct pt pt;
	uint8_t _pin;
	uint8_t _ms;
};