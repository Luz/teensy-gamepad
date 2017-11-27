#include <avr/io.h>
#include <util/delay.h>
#include "usb_keyboard.h"

#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))

static const uint8_t B_MASK      = 0x01;
static const uint8_t SELECT_MASK = 0x02;
static const uint8_t START_MASK  = 0x04;
static const uint8_t A_MASK      = 0x08;

static const uint8_t UP_MASK     = 0x01;
static const uint8_t DOWN_MASK   = 0x02;
static const uint8_t LEFT_MASK   = 0x04;
static const uint8_t RIGHT_MASK  = 0x08;

int main(void) {
	uint8_t bnew;
	uint8_t dnew;
	uint8_t keys[6];

	CPU_PRESCALE(0); // 16 MHz clock
	DDRB = 0x00; //pins B are inputs with pullup resistors
	PORTB = 0xFF; //pins B are inputs with pullup resistors

	// pins D are inputs with pullup resistors
	DDRD = 0x00;
	PORTD = 0xFF;

	usb_init(); // Wait for a USB-Host
	while(!usb_configured());
	_delay_ms(1000); //Wait one more second for the OS to set drivers

	while(1) {
		bnew = PINB; // read port B pins
		dnew = PIND; // read port D pins

		for(int i=0; i<6; i++) keys[i] = 0;

		if (0 == (bnew & A_MASK))      keys[0] = KEY_SPACE;
		if (0 == (bnew & SELECT_MASK)) keys[1] = KEY_ESC;
		if (0 == (bnew & B_MASK))      keys[2] = KEY_B;
		if (0 == (bnew & START_MASK))  keys[3] = KEY_Q;

		if (0 == (dnew & UP_MASK))   keys[4] = KEY_K;
		if (0 == (dnew & DOWN_MASK)) keys[4] = KEY_J;
		if (0 == (dnew & LEFT_MASK))  keys[5] = KEY_H;
		if (0 == (dnew & RIGHT_MASK)) keys[5] = KEY_L;

		//TODO: only send if keys have changed!

		usb_keyboard_down(keys, 0);

		_delay_ms(2); //debounce delay (bouncing of contacts)
	}
}
