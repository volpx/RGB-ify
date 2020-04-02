# RGB-ify 
One day I will get the time to explain it better.
If you have a SBC and a atmega328p and some MOSFET you can try this.
Helper is the firmware for the microcontroller, it communicates as slave using SPI with the SBC which is the master and sets some registers to get the PWM codes of the color output. Ideally `run the baracca.sh` is runned at boot with zeros to initiate the GPIO pins but can be run manually to change the colors.
