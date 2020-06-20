//Black/White line follower Robot

#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRD=0x00;
  DDRB=0xFF;
  int i;
  while(1)
  {
    if((PIND & 0b00000101)==0b00000101)
	{
	  PORTB=0b00000101;
	   _delay_us(60);
	  PORTB=0;
	  _delay_us(60);

	 }
	 else if((PIND & 0b00000001)==0b00000001) 
	 {
	   
	   for(i=0;i<=6000;i++)
	   {
	     PORTB=0b00000100;
	     _delay_us(60);
	     PORTB=0;
	    _delay_us(60);
	   }
     }
	 else if((PIND & 0b00000100)==0b00000100)
	 {
	  
	   for(i=0;i<=6000;i++)
	   {
	      PORTB=0b00000001;
	     _delay_us(60);
	     PORTB=0;
	    _delay_us(60);
	   }
	   
     }
	  else if((PIND & 0b00000111)==0b00000111)
	  {
	  
	   
	     PORTB=0x00;
	   }
	   
     }
	 
  
  return 0;
}
