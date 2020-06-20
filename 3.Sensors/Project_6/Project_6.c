//Obstacle Detector Robot

#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRC=0x00;
  DDRB=0xFF;
  int i;
  while(1)
  {
    if(PINC==0b00000000)
	{
	  PORTB=0b00000101;
	  _delay_us(60);
	  PORTB=0;
	  _delay_us(30);
	 }
	 else 
	 {
	 for(i=0;i<=10000;i++)
	  {
	   PORTB=0b00001010;
	   _delay_us(60);
	   PORTB=0;
	   _delay_us(30);
	  }
	  for(i=0;i<=9000;i++)
	  {
	   PORTB=0b00000001;
	   _delay_us(60);
	   PORTB=0;
	   _delay_us(30);
	  }

     }
}

return 0;
}
