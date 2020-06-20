//Chaser
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRC=0xFF;
  while(1)
  {
    for(int i=1;i<256;i=i*2)
	{
	  PORTC=i;
	  _delay_ms(500);
	 }
  }
}
