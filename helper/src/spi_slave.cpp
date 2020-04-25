#include "spi_slave.h"

uint8_t spi_mem[SPI_MEM];

volatile uint8_t spi_reg=0;
volatile uint8_t spi_ind=0;

void spi_init(){
    // Disable module power reduction
    PRR&=~(1<<PRSPI);
    // set MISO and clock as output
    DDRB|=(1<<4);
    // set pullup on my cs, clock and input
    PORTB|=(1<<PB2)|(1<<PB5)|(1<<PB3);

    // Enable SPI as a master and set clock
    SPCR = (1<<SPIE)|(1<<SPE)|(0<<DORD)
        |(0<<CPOL)|(0<<CPHA);

    for (uint8_t i=0;i<SPI_MEM;++i){
        spi_mem[i]=0;
    }
    // Wait the end of programming, my CS must be high
    while(!(PINB&(1<<PB2)));
    // set ready
    spi_reg|=(1<<SPI_REG_X_READY);
}

void spi_loop(){
    if ((spi_reg& (1<<SPI_UPDATE))) {
		// so there's an update in the spi mem
		PWM_RED=spi_mem[1];
		PWM_GREEN=spi_mem[2];
		PWM_BLUE=spi_mem[3];

		// dummy data
		SPDR=0xFF;
		// set no more update
		spi_reg&=~(1<<SPI_UPDATE);
    }
}

ISR(SPI_STC_vect){
    // slave operations
    uint8_t data=SPDR;
//     if(data == 0xaa && spi_reg==0b00001110){
//             LED_OFF();
//     }
    if (spi_reg & (1<<SPI_REG_X_READY)){
        // begin of transmission
        spi_reg&=~(1<<SPI_REG_X_READY);

        // get the mem address
        spi_ind=SPI_ADDR_MASK&data;
        if(spi_ind>=SPI_MEM){
            spi_ind=0;
        }

        // check W / AUTOINC
        if(data & SPI_AUTOINC){
            spi_reg|=(1<<SPI_REG_AUTOINC);
        }
        else{
            spi_reg&=~(1<<SPI_REG_AUTOINC);
        }

        if(data & SPI_W){
            // write
            spi_reg|=(1<<SPI_REG_W);
            // don't need for now
            data=0xFF;
        }
        else{
            // read
            spi_reg&=~(1<<SPI_REG_W);
            // here load the next byte to send out
            data=0xFF;
        }
    }
    else{
        // ongoing transmission
        if (spi_reg & (1<<SPI_REG_W)){
            // write stuff

            // save the data in the memory
            spi_mem[spi_ind]=data;
        }
        else{
            // read stuff
            data=0xFF;
        }

        if (spi_reg & (1<<SPI_REG_AUTOINC)){
            // advance the address
            ++spi_ind;
            if(spi_ind>=SPI_MEM){
				// end of transmission
                spi_reg|=(1<<SPI_REG_X_READY)|(1<<SPI_UPDATE);
            }
        }
    }
    // load next data
    SPDR=data;
}
