#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd.h"							// include LCD library

#define BAUD 9600
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

// function to initialize UART
void uart_init (void)
{
	UBRRH=(BAUDRATE>>8);
	UBRRL=BAUDRATE;
	UCSRB|=(1<<TXEN)|(1<<RXEN);
	UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
}


void uart_transmit (unsigned char data)
{
	while (!( UCSRA & (1<<UDRE)));
	UDR = data;
}

unsigned char uart_recieve (void)
{ 
	while(!(UCSRA) & (1<<RXC));
	return UDR;
}


int main (void)
{
	unsigned char a;
	char buffer[10];

	uart_init();
	lcd_init(LCD_DISP_ON_CURSOR);
	lcd_home();

  	while(1)
  	{
		a=uart_recieve(); 					// save the received data in a variable
		itoa(a,buffer,10); 					// convert numerals into string
		lcd_clrscr(); 						// LCD clear screen
		lcd_home();							// goto LCD home
		lcd_puts(buffer); 					// display the received value on LCD
		_delay_ms(100);						// wait before next attempt
  	}
  	
  	return 0;
}
