//Mobile Controlled Robotic Vehicle

#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRC=0xFF;
  DDRD=0x00;
  while(1)
  { 
     
     if(PIND==0x02)
	 {
	  PORTC=0b00000101;//FORWARD
	 }
     else if(PIND==0x04)
      {
	   PORTC=0b00001010;//BACKWARD
	  
	  }
	 else if(PIND==0x06)
	  {
	    PORTC=0b00000001;//LEFT
	    
	  }
     else if(PIND==0x08)
	 {
	    PORTC=0b00000100;//RIGHT
	    
	 }
	else if(PIND==0x05)
	 {
	   PORTC=0b00000000;//STOP
	 
	 }
     
  }
  return 0;

}
