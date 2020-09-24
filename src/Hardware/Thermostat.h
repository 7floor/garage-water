#pragma once
#include <Arduino.h>
#include "../Protothreads/protothreads.h"
#define Kp 0.5
#define Ki 0.03
#define Kd 0.3
#define Dt 500

class Thermostat {
public:
	Thermostat();

	float getTarget();
	void setTarget(float value);	

	PT_THREAD() run();
	
private:
	pt pt;
	float _target;
	float _integral;
	float _lasterror;
};
