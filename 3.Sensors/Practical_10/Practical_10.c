//Interfacing LDR with MCU as light controlled switch
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


