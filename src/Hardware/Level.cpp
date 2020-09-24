#include "Level.h"
#include <Arduino.h>

Level::Level(uint8_t ping, uint8_t echo, uint8_t avgSteps)
{
	_ping = new NewPing(ping, echo);
	_avgSteps = avgSteps;
	PT_INIT(&pt);
}

uint16_t Level::getLevel(enum LevelMode mode = Current)
{
	return _levels[mode];
}

void Level::setLevel(enum LevelMode mode, uint16_t level)
{
	_levels[mode] = level;
}

void Level::learnLevel(enum LevelMode mode)
{
	_levels[mode] = _levels[Current];
}

bool Level::isEmpty()
{
	return _levels[Current] >= _levels[Bottom];
}

bool Level::isFull()
{
	return _levels[Current] <= _levels[Top];
}

uint8_t Level::getPercentage()
{
	int8_t pct = (int32_t(_levels[Bottom]) - _levels[Current]) * 100 / (_levels[Bottom] - _levels[Top]);
	if (pct < 0) pct = 0;
	if (pct > 100) pct = 100;
	return pct;
}

PT_THREAD() Level::run()
{
	static uint8_t i;
	static long sum;
  
	PT_BEGIN(&pt);
  
	sum = 0;

	for(;;)
	{
		sum = ((sum * i) + _ping->ping()) / ++i;
		if (i > _avgSteps) i = _avgSteps;
		_levels[Current] = sum * 10 / 57;
    
		PT_SLEEP(&pt, 50);
	}
  
	PT_END(&pt);
}

