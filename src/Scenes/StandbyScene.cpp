#include "StandbyScene.h"
#include <Arduino.h>

StandbyScene::StandbyScene()
{
	PT_INIT(&pt);
}

PT_THREAD() StandbyScene::run()
{
	static bool lraw;

	PT_BEGIN(&pt);
  
	for(;;)
	{
	        hub.display.displayInt(lraw ? hub.level.getLevel() : hub.level.getPercentage());
        	hub.display.point(2, lraw);
		if (hub.encoder.clicks() > 0)
		{
			hub.buzzer.beep(250);
			lraw = !lraw;
		}
		if (hub.encoder.encoder() > 0)
		{
			hub.buzzer.beep();
			PT_SPAWN(&pt, &active_scene.pt, active_scene.run());
			hub.thermostat.setTarget(0);
		}
		hub.encoder.reset();

		PT_YIELD(&pt);
	}
  
	PT_END(&pt);
}

StandbyScene standby_scene;