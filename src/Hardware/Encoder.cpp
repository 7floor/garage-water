#include "Encoder.h"
#include <Arduino.h>

Encoder::Encoder(uint8_t a, uint8_t b, int8_t sw)
{
	_pin_reg_A = portInputRegister(digitalPinToPort(a));
	_bit_mask_A = digitalPinToBitMask(a);
	_pin_reg_B = portInputRegister(digitalPinToPort(b));
	_bit_mask_B = digitalPinToBitMask(b);
	_pin_reg_SW = portInputRegister(digitalPinToPort(sw));
	_bit_mask_SW = digitalPinToBitMask(sw);

	pinMode(a, INPUT_PULLUP);
	pinMode(b, INPUT_PULLUP);	
	pinMode(sw, INPUT_PULLUP);	

	_last_a = _readA();
	_last_b = _readB();
	_last_sw = !_readSW();
	_last_enc_t = _last_sw_t = _lp_start_t = millis();
}

void Encoder::check()
{
	unsigned long now = millis();

	bool a = _readA();
	bool b = _readB();
	bool sw = !_readSW();

	// switch
	if (sw != _last_sw)
	{
		if (!sw && now - _last_sw_t > ENC_DEBOUNCE_BUTTON && now - _last_sw_t < ENC_HOLD_TIMEOUT)
		{
			_clicks++;
		}
		_last_sw = _push = sw;
		_last_sw_t = _lp_start_t = now;
	}

	// rotation
	if (a != _last_a || b != _last_b)
	{
		if (a != b)
		{
			int increment = now - _last_enc_t > ENC_FAST_ROTATE_TIMEOUT ? 1 : ENC_FAST_ROTATE_STEPS;
  
			if ((a > b) == _last_a)
			{
				_encoder += increment;
			}
			else
			{
				_encoder -= increment;
			}

			_last_enc_t = now;
		}

		_last_a = a;
		_last_b = b;
	}
}

bool Encoder::anything()
{
	return encoder() != 0 || clicks() != 0 || push() || press();
}

int Encoder::encoder()
{
	return _encoder;
}

int Encoder::clicks()
{
	return _clicks;
}

bool Encoder::push()
{
	return _push && press();
}

bool Encoder::press()
{
	return _last_sw && millis() - _last_sw_t > ENC_DEBOUNCE_BUTTON;
}

bool Encoder::longpress()
{
	return _last_sw && millis() - _lp_start_t > ENC_HOLD_TIMEOUT;
}

void Encoder::reset()
{
	if (!anything()) return;
	_encoder = _clicks = 0;
	_push = false;
}

void Encoder::reset_lp()
{
	_lp_start_t = millis();
}

