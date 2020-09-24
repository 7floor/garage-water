#pragma once
#include <Arduino.h>

#define ENC_FAST_ROTATE_TIMEOUT 0
#define ENC_FAST_ROTATE_STEPS 10
#define ENC_DEBOUNCE_BUTTON 20
#define ENC_HOLD_TIMEOUT 1000

#define _readA() bool(*_pin_reg_A & _bit_mask_A)
#define _readB() bool(*_pin_reg_B & _bit_mask_B)
#define _readSW() bool(*_pin_reg_SW & _bit_mask_SW)

class Encoder {
public:
	Encoder(uint8_t a, uint8_t b, int8_t sw);
	
	void check();
	int encoder();
        int clicks();
        bool push();
        bool press();
        bool longpress();
	bool anything();
	void reset();
	void reset_lp();
	
private:
	bool _last_a, _last_b, _last_sw;
	unsigned long _last_enc_t, _last_sw_t, _lp_start_t;
	int _encoder = 0, _clicks = 0;
	bool _push;

	volatile uint8_t *_pin_reg_A;
	volatile uint8_t _bit_mask_A;
	volatile uint8_t *_pin_reg_B;
	volatile uint8_t _bit_mask_B;
	volatile uint8_t *_pin_reg_SW;
	volatile uint8_t _bit_mask_SW;
};