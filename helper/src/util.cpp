#include "util.h"

uint8_t util_reg=0;

void util_init(){
		// My led
		DDRD |= (1<<LED);
		// turn off the debug led
		// can be turned on 
		LED_OFF();
}
void idle(){
	// watchdog_reset();
	time_base();
}

// Initialize watchdog with 8s timeout, if possible. Otherwise, make it 4s.
void watchdog_init(){
		// #define WDTO_NS WDTO_2S
		// #undef WATCHDOG_RESET_MANUAL
		// #if ENABLED(WATCHDOG_RESET_MANUAL)
		//   // Enable the watchdog timer, but only for the interrupt.
		//   // Take care, as this requires the correct order of operation, with interrupts disabled.
		//   // See the datasheet of any AVR chip for details.
		//   wdt_reset();
		//   cli();
		//   _WD_CONTROL_REG = _BV(_WD_CHANGE_BIT) | _BV(WDE);
		//   // WDTO_NS directly does not work. bit 0-2 are consecutive in the register but the highest value bit is at bit 5
		//   // So worked for up to WDTO_2S
		//   _WD_CONTROL_REG = _BV(WDIE) | (WDTO_NS & 0x07) | ((WDTO_NS & 0x08) << 2);
		//   sei();
		//   wdt_reset();
		// #else
		//   wdt_enable(WDTO_NS); // The function handles the upper bit correct.
		// #endif
		// //delay(10000); // test it!
		wdt_enable(WDTO_4S);
}
