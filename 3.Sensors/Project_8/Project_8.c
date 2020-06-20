//Edge Follower (Never Falling Robot)

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
    if((PIND & 0b00000011)==0b00000011)
	{
	  PORTB=0b00000101;
	  _delay_us(60);
	  PORTB=0;
	  _delay_us(30);
	 }
	 else if((PIND & 0b00000001)==0b00000001) 
	 {
	 for(i=0;i<=6000;i++)
	 {
	   PORTB=0b00001010;
	   _delay_us(60);
	   PORTB=0;
	   _delay_us(60);
	  }

	 for(i=0;i<=8000;i++)
	 {
	   PORTB=0b00001000;
	     _delay_us(60);
	  PORTB=0;
	  _delay_us(60);
	  }

     }
	 else if((PIND & 0b00000010)==0b00000010)
	 {
	 for(i=0;i<=6000;i++)
	 {
	   PORTB=0b00001010;
	     _delay_us(60);
	  PORTB=0;
	  _delay_us(60);
	  }
	  
	  
	   for(i=0;i<=8000;i++)
	 {
	   PORTB=0b00000001;
	     _delay_us(60);
	  PORTB=0;
	  _delay_us(60);
	  }
	   
	   
     }
	 else if((PIND & 0b00000000)==0b00000000)
	 {
	  
	    for(i=0;i<=6000;i++)
	 {
	   PORTB=0b00001010;
	     _delay_us(60);
	  PORTB=0;
	  _delay_us(60);
	  }
	   

	     for(i=0;i<=8000;i++)
	 {
	   
	   PORTB=0b00001001;
	     _delay_us(60);
	  PORTB=0;
	  _delay_us(60);
	  }
     }


  }

  return 0;
}
