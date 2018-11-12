#define F_CPU 1000000UL
 
#include <avr/io.h>
 
int ch_prime(int);

int main(void)
{
          uint8_t num=0;
          uint8_t res;
          DDRA &= ~(1<<0);
          DDRD |= (1<<0); 
          while(1)
          {
                   if (bit_is_set(PINA, 0))
                   {
                            while (bit_is_set(PINA, 0));
                            res = ch_prime(++num);
                            if (res==1)
                            PORTD |= (1<<PIND0);
                            else
                            PORTD &= ~(1<<PIND0);
                   }
                   else
                   continue;
          }
}
 
int ch_prime(int num)
{
          int i;
          for (i=2;i<num;i++)
          {
                   if (num%i==0)
                   return(0);
          }
          if (i==num)
          return(1);
}