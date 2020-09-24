#pragma once

#define BUZZER 2

#define ENC_BTN 3
#define ENC_A 4
#define ENC_B 5

#define DISP_CLK 6
#define DISP_DIO 7

#define SONAR_TRIG 12
#define SONAR_ECHO 11

#define HEATER_PIN 8

#define PUMP_PWM 9

#define THERM_PIN 10

#define SONAR_MA_SAMPLES 20

#include <Arduino.h>
#include "../Protothreads/protothreads.h"
#include "Encoder.h"
#include "Display.h"
#include "Buzzer.h"
#include "Pump.h"
#include "Heater.h"
#include "Level.h"
#include "Thermometer.h"
#include "Thermostat.h"

class Hub {
public:
	Encoder encoder = Encoder(ENC_A, ENC_B, ENC_BTN);
	Display display = Display(DISP_CLK, DISP_DIO);
	Buzzer buzzer = Buzzer(BUZZER);
	Pump pump = Pump(PUMP_PWM, 8, 64, 255);
	Heater heater = Heater(HEATER_PIN);
	Level level = Level(SONAR_TRIG, SONAR_ECHO, SONAR_MA_SAMPLES);
	Thermometer thermometer = Thermometer(THERM_PIN);
	Thermostat thermostat = Thermostat();

	void Init();	
	PT_THREAD() run();
	
private:

};

uint8_t attachPCINT(uint8_t pin);

extern Hub hub;
