#ifndef SPI_SLAVE_H
#define SPI_SLAVE_H

#include "../helper.h"

#include <avr/interrupt.h>
#include <stdint.h>

// packet size
#define SPI_MEM 4

// registers define masks to
#define SPI_ADDR_MASK 0x3F
#define SPI_REG_RED   0x01
#define SPI_REG_GREEN 0x02
#define SPI_REG_BLUE  0x03

// register access modifier
#define SPI_AUTOINC   0x80
#define SPI_W         0x40

// take the interrupt
extern "C" void SPI_STC_vect(void) __attribute__((signal));

extern uint8_t spi_mem[SPI_MEM];

// reg description
extern volatile uint8_t spi_reg;
//#define SPI_UPDATE      0
#define SPI_X_READY     1
#define SPI_REG_AUTOINC 2
#define SPI_REG_W       3

extern volatile uint8_t spi_ind;

void spi_init();
void spi_loop();

#endif //SPI_SLAVE_H
