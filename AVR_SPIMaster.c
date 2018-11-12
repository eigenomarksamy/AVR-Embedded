#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define ACK 0x7E
#define LONG_TIME 10000


void spi_init_master (void)            
{
    DDRB = (1<<5)|(1<<3);
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}


unsigned char spi_tranceiver (unsigned char data)
{
    SPDR = data;
    while(!(SPSR)&(1<<SPIF));
    return(SPDR);
}


void led_blink (uint8_t i)
{

    for (; i>0; --i)
    {
        PORTD|=(1<<0);
        _delay_ms(100);
        PORTD=(0<<0);
        _delay_ms(100);
    }
}

//Main
int main(void)
{
    spi_init_master();
    DDRD |= 0x01;
    
    unsigned char data;
    uint8_t c = 0;
    
    while(1)
    {
        data = 0x00;
        data = spi_tranceiver(++c);
        if(data == ACK) {
            led_blink(c);
        }
        else {
            led_blink(LONG_TIME);
        }
        _delay_ms(500);
    }
}