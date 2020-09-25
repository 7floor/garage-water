#pragma once
#include <Arduino.h>
#include "../Protothreads/protothreads.h"
#define Kp 0.5
#define Ki 0.05
#define Kd 0.3
#define Dt 400

class Thermostat {
public:
	Thermostat();

	float getTarget();
	void setTarget(float value);	

	PT_THREAD() run();
	
private:
	struct pt pt;
	float _target;
	float _integral;
	float _lasterror;
};
