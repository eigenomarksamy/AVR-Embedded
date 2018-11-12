#include <avr/io.h>

void timer0_init()
{
    // set up timer with prescaler = 1024
    TCCR0 |= (1 << CS02)|(1 << CS00);
    TCNT0 = 0;
}

int main(void)
{
    DDRC |= (1 << 0);
    timer0_init(); 
    while(1) 
    {
        if (TCNT0 >= 124)
        {
            PORTC ^= (1 << 0);
            TCNT0 = 0;
        }
    }
}