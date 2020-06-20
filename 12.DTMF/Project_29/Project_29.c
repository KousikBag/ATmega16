
//Cellphone operated Water Irrigation Pump Controlling Relays

#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRC=0xFF;
  DDRD=0x00;
  while(1)
  { 
     
     if(PIND==0x01)
	 {
	  PORTC=0b00000001;//Start
	 }
     else if(PIND==0x02)
      {
	   PORTC=0b00000000;//stop
	  
	  }
	 
     
  }
  return 0;

}
