//Interfacing IR Sensor as a touch less switch with AVR
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRC=0xFF;
  DDRA=0x00;
  PORTC=0x00;
  while(1)
  {
   if(PINA==0x01)
   {PORTC=0xFF;}
   else
   {PORTC=0x00;}
  }
}
