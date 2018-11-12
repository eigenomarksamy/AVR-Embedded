#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "lcd.h"

#define ACK 0x7E

void spi_init_slave (void)
{
    DDRB=(1<<6);
    SPCR=(1<<SPE);
}

unsigned char spi_tranceiver (unsigned char data)
{
    SPDR = data;
    while(!(SPSR)&(1<<SPIF));
    return(SPDR);
}

int main(void)
{
    lcd_init(LCD_DISP_ON_CURSOR_BLINK);
    spi_init_slave();
    
    unsigned char data, buffer[10];
    
    DDRA  = 0x00;
    PORTA = 0xFF;
    
    while(1)
    {
        lcd_clrscr();                             //LCD Clear screen
        lcd_home();                               //LCD move cursor to home 
        lcd_puts("Testing");
        lcd_gotoxy(0,1);
        data = spi_tranceiver(ACK);               //Receive data, send ACK
        itoa(data, buffer, 10);                   //Convert integer into string
        lcd_puts(buffer);                         //Display received data
        _delay_ms(20);                            //Wait
    }
}