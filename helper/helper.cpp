#include "helper.h"

int main(void){
	watchdog_init();
	util_init();
	time_init();
    spi_init();
    sei();
    
    LED_ON();
    
    PWM_RED=0;
    PWM_GREEN=0;
    PWM_BLUE=0;
    

	while(1){
        spi_loop();
		watchdog_reset();
	}
	return 0;
}
