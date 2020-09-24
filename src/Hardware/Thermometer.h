#pragma once
#include <Arduino.h>
#include "microDS18B20.h"
#include "../Protothreads/protothreads.h"

class Thermometer {
public:
	Thermometer(uint8_t pin);
	
	void request();
	float getTemperature();
	bool valid();

private:
	MicroDS18B20* _ds;
	float _temperature;
	bool _valid;
	bool _requested;
};