#pragma once
#include <Arduino.h>
#include "../Protothreads/protothreads.h"
#define Kp 1.0 // 1C difference - full power; 0.5C difference - half power
#define Ki 0.0
#define Kd 0.0
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
