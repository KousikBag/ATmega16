//Controlling a simple DC motor rotation (CW, CCW) using MCU
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRB=0xFF;
  while(1)
  {
    PORTB=0b00000001;
	_delay_ms(1000);
	 PORTB=0b00000010;
	_delay_ms(1000);
  }
}
