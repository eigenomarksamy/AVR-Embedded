#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

#define LTHRES 500
#define RTHRES 500

void adc_init()
{
    ADMUX = (1<<REFS0);
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t adc_read(uint8_t ch)
{
    ch &= 0b00000111;
    ADMUX = (ADMUX & 0xF8)|ch;
    ADCSRA |= (1<<ADSC);
    while(ADCSRA & (1<<ADSC));
    return (ADC);
}

int main()
{
    uint16_t adc_result0, adc_result1;
    char int_buffer[10];
    DDRC = 0x01;
    adc_init();
    lcd_init(LCD_DISP_ON_CURSOR);
    lcd_puts("left  ADC = ");
    lcd_gotoxy(0,1);
    lcd_puts("right ADC = ");
    _delay_ms(50);
    while(1)
    {
        adc_result0 = adc_read(0);
        adc_result1 = adc_read(1);
        if (adc_result0 < LTHRES && adc_result1 < RTHRES)
            PORTC = 0x01;
        else
            PORTC = 0x00;
        itoa(adc_result0, int_buffer, 10);
        lcd_gotoxy(12,0);
        lcd_puts(int_buffer);
        itoa(adc_result0, int_buffer, 10);
        lcd_gotoxy(12,1);
        lcd_puts(int_buffer);
        _delay_ms(50);
    }
}