#ifndef UTIL_H
#define UTIL_H

#include "../helper.h"

#include <avr/wdt.h>

//pin B5 is also the SPI clock, don't use it!
#define LED_BUILTIN 5
//port D
#define LED 7

extern uint8_t util_reg;

void util_init();
void idle();
#define LED_ON() PORTD|=(1<<LED)
#define LED_OFF() PORTD&= ~(1<<LED)
#define LED_TOG() PORTD^= (1<<LED)

void watchdog_init();

// Reset watchdog. MUST be called at least every 4 seconds after the
// first watchdog_init or AVR will go into emergency procedures.
inline void watchdog_reset() { wdt_reset(); }

// Utility functions


#endif //UTIL_H
