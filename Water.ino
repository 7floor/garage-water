#include <protothreads.h>
#include "src/Hardware/Hub.h"
#include "src/Scenes/StandbyScene.h"

/*
+hardware context for scenes = Hub
+encoder: anything() & push()
+ds18b20
+heater hw

active scene for temperature
when starting flow set target = current (no heater will be used mostly)
press - (x) go to temp set mode (bright) - rotate - adjust target - timeout - go to current temp - rotate - go to (x)

PID for heater (+P only at the moment, let's see)
leak detector device?
failure watcher & error reporting

eeprom, load/save settings
setup scene
  params:
  - water level min, max / adjust in mm & learn from current
  - motor pwm range min max / adjust 0-255
  - temperatures min, max, critical / adjust in celsius 0 to 60 (critical set 70 and not adjust?)
  


 
 */
 
void setup() 
{
  Serial.begin(9600);

  hub.Init();
}

void loop() 
{
  PT_SCHEDULE(hub.run());
  PT_SCHEDULE(standby_scene.run());
}

ISR(PCINT2_vect) // PCINT0_vect: D8-D13, PCINT1_vect: A0-A5, PCINT2_vect: D0-D7
{
  hub.encoder.check();
}
