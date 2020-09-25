#pragma once
#include <Arduino.h>
#include "../Protothreads/protothreads.h"
#include "../Hardware/Hub.h"

class ActiveScene {
public:
	ActiveScene();
	
	struct pt ptt;
	struct pt pt;
	PT_THREAD() run();
	
private:
	PT_THREAD() run_t();
};

extern ActiveScene active_scene;
