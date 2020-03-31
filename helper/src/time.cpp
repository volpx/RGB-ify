#include "time.h"

volatile uint32_t ms=0; // over 1000 hours before overflow
volatile uint16_t dms=0;

void delay_ms(const uint16_t delay){
	dms=delay+1;
	while(dms)
		idle();
}

void delay_us(uint8_t delay){
	// Always has at least 9cycles(0.56us) delay if delay=0
	// Then it is 9cycles+1us*delay
	asm("cli\n");
	while(delay){
		asm("\
			nop\n\
			nop\n\
			nop\n\
			nop\n\
			nop\n\
			nop\n\
			nop\n\
			nop\n\
			nop\n\
			nop\n\
			nop\n\
			nop\n\
			nop\n");
		--delay;
	}
	asm("sei\n");
}

void time_base(){

}
void time_init(){
	// Timer TIMER0
	// This timer is setted por PWM
	DDRD|=(1<<5)|(1<<6);	
	// Disable power saving
	PRR&=~(1<<PRTIM0);
	// Mode selection: pwm on OC0A OC0B
    // add COM0B0 to avoid load peaks and put in inverting
	TCCR0A=(1<<COM0A1)|(1<<COM0B1)|(1<<WGM01)|(1<<WGM00);
	// Scale clock: tune this to change frequency
	TCCR0B=(1<<CS00);
	// zero out the PWM
	// OCR0A
	PWM_RED=0x00;
	// OCR0B
	PWM_GREEN=0x00;


	
	// Timer TIMER1
	// Set port pin to output to abilitate pin driving for PWM
	DDRB|=(1<<1);
	// Set PWM mode and the wanted pin
	TCCR1A=(1<<COM1A1)|(1<<WGM10);
	// Set prescaler
	TCCR1B=(1<<WGM12)|(1<<CS10);
	// Set half dutycycle
	OCR1AH=0x00;
	// OCR1A
	PWM_BLUE=0x00;

// 	Sync timers after prescaler selection
// 	Sync mode on
// 	GTCCR|=(1<<TSM);
// 	Reset prescalers
// 	GTCCR|=(1<<PSRSYNC);
// 	Sync mode off
// 	GTCCR&=~(1<<TSM);
}
ISR(TIMER1_COMPA_vect){
	// for pwm for example:
	//PORTB^=0x20;
}
ISR(TIMER0_OVF_vect){
// 	++ms;
// 	dms=(dms)?dms-1:0;
}
