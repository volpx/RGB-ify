#include "helper.h"

int main(void){
	watchdog_init();
	util_init();
	time_init();
    spi_init();
    
    LED_ON();
    
    PWM_RED=255;
    PWM_GREEN=255;
    PWM_BLUE=255;
    

	while(1){
        spi_loop();
		watchdog_reset();
	}
	return 0;
}
