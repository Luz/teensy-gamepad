#include <avr/io.h>
#include <util/delay.h>
#include "usb_keyboard.h"

#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))

int main(void) {
	uint8_t bnew;
	uint8_t keys[6];

	CPU_PRESCALE(0); // 16 MHz clock
	DDRB = 0x00; //pins B are inputs with pullup resistors
	PORTB = 0xFF; //pins B are inputs with pullup resistors
	usb_init(); // Wait for a USB-Host
	while(!usb_configured());
	_delay_ms(1000); //Wait one more second for the OS to set drivers

	while(1) {
		bnew = PINB; //read port B pins

		for(int i=0; i<6; i++) keys[i] = 0;

		if (0 == (bnew & 0x01)) keys[0] = KEY_F1; //PB0 -> F1
		if (0 == (bnew & 0x02)) keys[1] = KEY_F2; //PB1 -> F2
		if (0 == (bnew & 0x04)) keys[2] = KEY_F3; //PB2 -> F3
		if (0 == (bnew & 0x08)) keys[3] = KEY_F4; //PB3 -> F4
		if (0 == (bnew & 0x80)) keys[4] = KEY_F5; //PB7 -> F5
		if (0 == (bnew & 0x10)) keys[5] = KEY_SPACE; //PB4 -> SPACE

		//TODO: only send if keys have changed!

		usb_keyboard_down(keys, 0);

		_delay_ms(2); //debounce delay (bouncing of contacts)
	}
}
