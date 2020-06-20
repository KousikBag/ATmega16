//Glowing LED by IR sensor as an external Interrupt

#define F_CPU 800000UL
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
void INTO_init();

void INTO_init()
{
        DDRD &=~(1<<PD2);
        MCUCR|=(1<<ISC01);   //Falling edge on INT0 triggers interrupt.
        GICR|=(1<<INT0);     //Enable INT0 interrupt
	    sei();               // Enable global interrupts
}
  

int main()
{
  DDRC=0xFF;
   INTO_init();
  _delay_ms(20);
  while(1)
  {
    
	 
	
  }
 return 0;
}

ISR(INT0_vect)//interrup service routine
 {
   PORTC=0xFF;
   _delay_ms(5000);
   PORTC=0X00;
   _delay_ms(5000);
  				
 }
                     
