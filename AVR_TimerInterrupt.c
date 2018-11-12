#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t tot_overflow;

void timer0_init()
{
    TCCR0 |= (1 << CS02);
    TCNT0 = 0;
    TIMSK |= (1 << TOIE0);
    sei();
    tot_overflow = 0;
}
ISR(TIMER0_OVF_vect)
{
    tot_overflow++;
}

int main(void)
{
    DDRC |= (1 << 0); 
    timer0_init(); 
    while(1) 
    {  
        if (tot_overflow >= 12)
        {
            if (TCNT0 >= 53)
            {
                PORTC ^= (1 << 0);
                TCNT0 = 0;
                tot_overflow = 0;
            }
        }
    }
}