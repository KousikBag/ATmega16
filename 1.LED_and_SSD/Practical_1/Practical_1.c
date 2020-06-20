#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRC=0xFF;
  while(1)
  {
    PORTC=0XFF;
	_delay_ms(500);
	PORTC=0X00;
	_delay_ms(500);
  }
}
