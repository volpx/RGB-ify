#include "low_level_communication.h"


const int help_cs_gpio_list[]={
	MAIN_HELPER_NUM,
	SEC_HELPER_NUM,
};

int send_RGB(const uint8_t help_id,
	const uint8_t R, const uint8_t G, const uint8_t B){

	char gpiopinvaluefile[40];
	sprintf(gpiopinvaluefile,
		GPIO_ACCESS_FILE_TEMPLATE, help_cs_gpio_list[help_id]);

	// open the gpiopin
	int cs_helper=open(gpiopinvaluefile,O_WRONLY);
	// set cs high justincase
	write(cs_helper, "1", 1);

	// pointer to file device, must be int for whatever reason
	int spifile;
	char *spidev=SPI_DEVICE;

	// declare a spi packet container
	struct spi_ioc_transfer xfer[1];
	// buffer
	uint8_t buf[4];
	uint32_t len=4;

	// get device to use
	spifile = open(spidev, O_RDWR);
	if (spifile < 0) {
		perror("opening spidev file");
		return 1;
	}

	// zeroout the structs
	memset(xfer, 0, sizeof(xfer));
	memset(buf, 0, sizeof(buf));

	//load the data
	buf[0]=0b11000001;
	buf[1]=R;
	buf[2]=G;
	buf[3]=B;
	len=4;

	// assign the buffers to use and the length of the transfer packet
	xfer[0].tx_buf = (uint64_t) buf;
	xfer[0].rx_buf = 0;
	xfer[0].len = len;
	xfer[0].speed_hz=50000;

	low_level_send(spifile,cs_helper,xfer[0]);

	// close the files
	close(cs_helper);
	close(spifile);
	return 0;
}

int low_level_send(int spidev_file, int cs_file,
	const struct spi_ioc_transfer xfer){

	// do the transmission
	// lower the cs
	write(cs_file, "0", 1);
	int status = ioctl(spidev_file, SPI_IOC_MESSAGE(1), xfer);
	// TODO: check that effectively at this point
	// the transmission has ended
	// the helper firmware obviusly bases the end of the packet
	// on the rising edge of the CS and if transmission has not
	// ended it goes pallino
	write(cs_file, "1", 1);
	if (status < 0) {
		perror("SPI_IOC_MESSAGE");
		return -1;
	}

	return 0;
}

//
// Set up a memory regions to access GPIO
//
volatile unsigned int* get_gpio_pointer(){
	int mem_fd;
	void *gpio_map;

	/* open /dev/mem */
	if ( ( mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
		printf("can't open /dev/mem \n");
		exit(-1);
	}

	/* mmap GPIO */
	gpio_map = mmap(
		NULL,             //Any adddress in our space will do
		1024,       //Map length
		PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
		MAP_SHARED,       //Shared with other processes
		mem_fd,           //File to map
		H6_GPIO_BASE         //Offset to GPIO peripheral
	);

	close(mem_fd); //No need to keep mem_fd open after mmap

	if (gpio_map == MAP_FAILED) {
		printf("mmap error, errno: %d\n", errno);//errno also set!
		exit(-1);
	}

	// Always use volatile pointer!
	return (volatile unsigned int*)gpio_map;

} // setup_io
