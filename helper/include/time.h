#ifndef TIME_H
#define TIME_H

#include "../helper.h"

#include <stdint.h>


// F_OVF=F_MCU/PRESCALER/TIMERCS/TOP=976.5 Hz
#define NOP_TIME        1/16e6
// PWM setup
#define PWM_RED     OCR0A
#define PWM_GREEN   OCR0B
#define PWM_BLUE    OCR1AL

extern volatile uint32_t ms;
void time_init();
void time_base();
void delay_ms(const uint16_t delay);
void delay_us(uint8_t delay);

#endif //TIMER_H
