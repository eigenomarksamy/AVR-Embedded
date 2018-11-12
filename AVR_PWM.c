#include <avr/io.h>
#include <util/delay.h>
void pwm_init()
{
    TCCR0 |= (1<<WGM00)|(1<<COM01)|(1<<WGM01)|(1<<CS00);
    DDRB |= (1<<PB3);
}

void main()
{
    uint8_t duty;
    duty = 115;       // duty cycle = 0.45 * 255 = 114.8 = 115
    pwm_init();
    while(1)
    {
        OCR0 = duty;
    }
}
