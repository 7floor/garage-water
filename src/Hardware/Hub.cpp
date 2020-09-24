#include "Hub.h"
#include <Arduino.h>

void Hub::Init()
{
	display.brightness(2);
	display.clear();

	level.setLevel(Bottom, 1000);
	level.setLevel(Top, 100);

	attachPCINT(ENC_A);
	attachPCINT(ENC_B);
	attachPCINT(ENC_BTN);
}

PT_THREAD() Hub::run()
{
	PT_SCHEDULE(level.run());
	PT_SCHEDULE(thermometer.run());
	PT_SCHEDULE(buzzer.run());
	PT_SCHEDULE(heater.run());
	PT_SCHEDULE(thermostat.run());
}

uint8_t attachPCINT(uint8_t pin) {
  if (pin < 8) // D0-D7 // PCINT2
  { 
    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << pin); 
    return 2; 
  }
  else
  if (pin > 13) // A0-A5 // PCINT1
  { 
    PCICR |= (1 << PCIE1);
    PCMSK1 |= (1 << pin - 14);
    return 1;
  }
  else // D8-D13  // PCINT0
  { 
    PCICR |= (1 << PCIE0);
    PCMSK0 |= (1 << pin - 8);
    return 0;
  }
}

Hub hub;