#pragma once
#include <Arduino.h>
#include "NewPing.h"
#include "../Protothreads/protothreads.h"

enum LevelMode {Current, Bottom, Top};

class Level {
public:
	Level(uint8_t ping, uint8_t echo, uint8_t avgSteps);
	
	uint16_t getLevel(enum LevelMode mode = Current);
	void setLevel(enum LevelMode mode, uint16_t level);
	void learnLevel(enum LevelMode mode);
	bool isEmpty();
	bool isFull();
	uint8_t getPercentage();

	PT_THREAD() run();
	
private:
	struct pt pt;
	NewPing* _ping;
	uint8_t _avgSteps;
	uint16_t _levels[3];
};