//Interfacing Relay with AVR
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRC=0xFF;
  while(1)
  {
   PORTC=0x01;
   _delay_ms(1000);
   PORTC=0x00;
   _delay_ms(1000);

  }
}
