#pragma once
#include <Arduino.h>
#include "microDS18B20.h"
#include "../Protothreads/protothreads.h"

class Thermometer {
public:
	Thermometer(uint8_t pin);
	
	float getValue();
	bool isValid();

	PT_THREAD() run();
	
private:
	pt pt;
	MicroDS18B20* _ds;
	float _value;
	bool _isValid;
};