//direction movement of a two motor based robotic vehicle system.

#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRB=0xFF;
  while(1)
  {
    PORTB=0b00000101;
	_delay_ms(1000);
	 PORTB=0b00001010;
	_delay_ms(1000);
	PORTB=0b00000001;
	_delay_ms(1000);
	 PORTB=0b00000100;
	_delay_ms(1000);
  }
}
