#ifndef __LOW_LEVEL_COMMUNICATION__
#define __LOW_LEVEL_COMMUNICATION__

// C headers
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Linux headers
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <sys/mman.h>
#include <errno.h>

// List of the GPIOs for the different CSs
#define GPIO_ACCESS_FILE_TEMPLATE	"/sys/class/gpio/gpio%d/value"
#define MAIN_HELPER_ID		0
#define MAIN_HELPER_NUM		122
#define SEC_HELPER_ID		1
#define SEC_HELPER_NUM		123
extern const int help_cs_gpio_list[2];

// SPI device to use
#define SPI_DEVICE "/dev/spidev0.0"
#define SPI_BUF_MAX_SIZE 8

// Memory map addresses
#define H6_GPIO_BASE  0x0300B000
#define PORT_OFFSET   0x24

#define CFG0_OFFSET  0x00
#define CFG1_OFFSET  0x04
#define CFG2_OFFSET  0x08
#define CFG3_OFFSET  0x0C
#define DAT_OFFSET   0x10
#define DRV0_OFFSET  0x14
#define DRV1_OFFSET  0x18
#define PUL0_OFFSET  0x1C
#define PUL1_OFFSET  0x20


#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

/*
 * Send a single RGB color
 * helper_id: device number
 * R,G,B values wanted
 */
int send_RGB(const uint8_t help_id,
	const uint8_t R, const uint8_t G, const uint8_t B);

/*
 * Send a single packet to spi
 * spidev_file: linux spifile
 * sc_file: file of the corespponding cs
 * xfer: packet
 */
int low_level_send(int spidev_file, int cs_file,
	const struct spi_ioc_transfer xfer);

/*
 * Getter of the CPU memory map for direct hardware access
 */
volatile unsigned int* get_gpio_pointer();

#endif // __LOW_LEVEL_COMMUNICATION__
