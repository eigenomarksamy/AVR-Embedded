#ifndef F_CPU 
#define F_CPU 16000000UL 
#endif 

#include <avr/io.h> 
#include <stdlib.h>
#include "lcd.h"
#include <util/delay.h> 

void adc_init(void) 
{ 
    ADCSRA|=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
    ADMUX|=(1<<REFS0);
} 

uint16_t adc_read(uint8_t ch) 
{ 
    ch&=0b00000111;
    ADMUX = (ADMUX & 0xf8)|ch;
    ADCSRA|=(1<<ADSC);
    while((ADCSRA)&(1<<ADSC));
    return(ADC);
} 

int main(void) 
{ 
    uint16_t x,y,z; 
    char bufferx[10], buffery[10], bufferz[10];
    adc_init();
    lcd_init(LCD_DISP_ON);
    lcd_clrscr();
    while(1) 
    { 
        lcd_home();
        x=adc_read(0);
        y=adc_read(1);
        z=adc_read(2);
        itoa(x,bufferx,10);
        itoa(y,buffery,10); 
        itoa(z,bufferz,10); 
        lcd_puts("x=");
        lcd_gotoxy(2,0); 
        lcd_puts(bufferx); 
        lcd_gotoxy(0,1); 
        lcd_puts("y="); 
        lcd_gotoxy(2,1); 
        lcd_puts(buffery); 
        lcd_gotoxy(6,0); 
        lcd_puts("z="); 
        lcd_gotoxy(6,1); 
        lcd_puts(bufferz); 
    } 
}