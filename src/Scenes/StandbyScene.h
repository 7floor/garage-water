#pragma once
#include <Arduino.h>
#include "../Protothreads/protothreads.h"
#include "../Hardware/Hub.h"
#include "ActiveScene.h"

class StandbyScene {
public:
	StandbyScene();
	
	PT_THREAD() run();
	
private:
	pt pt;
};

extern StandbyScene standby_scene;
