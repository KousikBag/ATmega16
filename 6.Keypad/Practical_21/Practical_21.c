//Taking Input from single Key to MCU to ON/OFF led
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRC=0xFF;
  DDRA=0x00;
  PORTA=0xff;
  while(1)
  {
   if((PINA & 0x01)==0x00)
   {
     PORTC=0xFF;
   }
    
    else
	{
	  PORTC=0x00;
    }
  }
}
