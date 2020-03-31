/* DOCS:
 * https://www.kernel.org/doc/html/latest/driver-api/pwm.html
 * https://www.kernel.org/doc/html/latest/driver-api/gpio/index.html
 * https://www.kernel.org/doc/html/latest/spi/index.html
 */

/*
* Sample application that makes use of the SPIDEV interface
* to access an SPI slave device. Specifically, this sample
* reads a Device ID of a JEDEC-compliant SPI Flash device.
*/

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include <sys/ioctl.h>

#include <linux/spi/spidev.h>
#include <unistd.h>
// #include <linux/>

// #include <sys/types.h>
// #include <sys/stat.h>
// #include <linux/types.h>

// length of the used buffer
#define MAX_BUF 32
int main(int argc, char **argv){
	// TODO: read in the configuration
	// $GPIO_CS_HELPER
	// TODO: sprintf(buf, "%d", gpio);
	char *gpiopinvaluefile="/sys/class/gpio/gpio122/value";
	// open the gpiopin
	int cs_helper=open(gpiopinvaluefile,O_WRONLY);
	// set cs high
	write(cs_helper, "1", 1);

	// pointer to file device, must be int for whatever reason
	int spifile;
	char *spidev="/dev/spidev0.0";
	int status;

	// declare a spi packet container
	struct spi_ioc_transfer xfer[1];
	// buffer
	uint8_t buf[MAX_BUF];
	uint32_t len=MAX_BUF;

	// get device to use
	spifile = open(spidev, O_RDWR);
	if (spifile < 0) {
		perror("open");
		return 1;
	}

	// zeroout the structs
	memset(xfer, 0, sizeof(xfer));
	memset(buf, 0, sizeof(buf));

	//load the data
	buf[0]=0b11000001;
	sscanf(argv[1],"%d",&(buf[1]));
	sscanf(argv[2],"%d",&(buf[2]));
	sscanf(argv[3],"%d",&(buf[3]));
	// buf[1]=0xAA;
	// buf[2]=buf[1];
	// buf[3]=0x55;
	len=4;

	// assign the buffers to use  and the lenght to the transfer packet
	xfer[0].tx_buf = (uint64_t) buf;
	xfer[0].rx_buf = 0;
	xfer[0].len = len;
	xfer[0].speed_hz=5000;

	// do the transmission
	// lower the cs
	write(cs_helper, "0", 1);
	status = ioctl(spifile, SPI_IOC_MESSAGE(1), xfer);
	write(cs_helper, "1", 1);
	if (status < 0) {
		perror("SPI_IOC_MESSAGE");
		return -1;
	}

	printf("response(%d): ", status);
	for (uint32_t i=0;i<len;++i){
		printf("%02x ", *(buf+i));
	}
	printf("\n");

	close(cs_helper);
	close(spifile);
	return 0;
}
