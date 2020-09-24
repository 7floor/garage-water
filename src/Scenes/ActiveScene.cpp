#include "ActiveScene.h"
#include <Arduino.h>

ActiveScene::ActiveScene()
{
	PT_INIT(&pt);
}

PT_THREAD() ActiveScene::run()
{
	PT_BEGIN(&pt);
  
	hub.display.clear();

	for(;;)
	{
		hub.pump.changeFlow(hub.encoder.encoder());

		if (hub.encoder.push())
		{
			PT_SPAWN(&pt, &ptt, run_t());
		}

		hub.encoder.reset();

		uint8_t flow = hub.pump.getFlow();
	        hub.display.displayBar(flow);

		if (flow == 0)
		{
			PT_EXIT(&pt);
		}	

		PT_WAIT_UNTIL(&pt, hub.encoder.anything());
	}
  
	PT_END(&pt);
}

PT_THREAD() ActiveScene::run_t()
{
	static bool isTarget;
	static unsigned long tglast;

	PT_BEGIN(&ptt);
  
	hub.display.clear();
	hub.display.point(2, true);
	hub.encoder.reset();
	hub.thermostat.setTarget((int)hub.thermometer.getTemperature());
	isTarget = true;
	tglast = millis();

	for(;;)
	{
		if (!hub.thermometer.valid())
		{
			hub.display.displayByte(_E, _r, _r, _t);
			PT_SLEEP(&ptt, 1000);
			PT_EXIT(&ptt);
		}

		if (isTarget)
		{
			hub.display.brightness(7);
		        hub.display.displayInt(hub.thermostat.getTarget() * 10);
		}
		else
		{
			hub.display.brightness(2);
		        hub.display.displayInt(hub.thermometer.getTemperature() * 10);
		}

		PT_YIELD(&ptt);

		if (hub.encoder.encoder())
		{
			hub.thermostat.setTarget(hub.thermostat.getTarget() + hub.encoder.encoder());
			isTarget = true;
			tglast = millis();
		}

		if (hub.encoder.push())
		{
			hub.display.point(2, false);
			hub.display.brightness(2);
			PT_EXIT(&ptt);
		}	

		hub.encoder.reset();

		if (millis() - tglast > 2000)
		{
			isTarget = false;
		}
	}
  
	PT_END(&ptt);
}

ActiveScene active_scene;