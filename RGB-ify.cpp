/* DOCS:
 * https://www.kernel.org/doc/html/latest/driver-api/pwm.html
 * https://www.kernel.org/doc/html/latest/driver-api/gpio/index.html
 * https://www.kernel.org/doc/html/latest/spi/index.html
 */

extern "C"{
	#include "low_level_communication.h"
}
#include "high_level_trickery.h"

#include <cstdint>
#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>

int oldmain(){
	volatile unsigned int* gpio=get_gpio_pointer();
	int port=3,pin=26;
	int offset=0;

	// std::cin>>std::hex>>offset;

	std::ofstream outf{"tmpdump.bin",std::ios::binary|std::ios::out};
	if (!outf)
	{
		// Print an error and exit
		std::cerr << "Uh oh, Sample.dat could not be opened for writing!" << std::endl;
		return 1;
	}
	for (int i=0;i<1024/sizeof(int);i++){
		outf.write((char*)(gpio+i),sizeof(int));
	}
	return 0;
	// TODO: nothing works
	// set pinmode output
	std::cout<<"Before: "<<*(gpio+CFG3_OFFSET + port*PORT_OFFSET)<<std::endl;
	*(gpio+CFG3_OFFSET + port*PORT_OFFSET) += 1;//(0b0001<<(pin*4));
	std::cout<<"After: "<<*(gpio+CFG3_OFFSET + port*PORT_OFFSET)<<std::endl;

	// set high
	*(gpio+DAT_OFFSET + port*PORT_OFFSET) |= (0b1<<pin);
	// ser low
	*(gpio+DAT_OFFSET + port*PORT_OFFSET) &= ~(0b1<<pin);
	return 0;
}

int main(int argc, char **argv){

	// TODO: read in the configuration
	send_RGB(0,0,0,0);
	float H_speed{0.1}; // rad/s of the HUE
	uint8_t RGB[3]={0,0,0};

	return 0;
}

void HUE_rotation_routine(const float S,const float L,
	const float H_speed,const float H_start){
	// uint8_t RGB[3]={0,0,0};
	//TODO
}
