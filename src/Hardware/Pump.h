#pragma once
#include <Arduino.h>

class Pump {
public:
	Pump(uint8_t pin, uint8_t flowSteps, uint8_t minDuty, uint8_t maxDuty);
	
	uint8_t getFlow();
        void setFlow(uint8_t flow);
	void changeFlow(int8_t delta);
	
private:
	uint8_t _pin;
	uint8_t _flowSteps;
	uint8_t _minDuty;
	uint8_t _maxDuty;
	uint8_t _flow;
};