//Automatic Irrigation System in which controlling the gate of water tank using Bluetooth & turning off water motor automatically


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


void usart_init()
{
 UBRRL=51;
 UBRRH=0;
 UCSRB=0x18;
 UCSRC=0x8e;
}
char usart_rec()
{
 while((UCSRA&0x80)==0);
 return UDR;
}
void usart_send(char send)
{
  while((UCSRA&0x20)==0);
  UDR=send;
}

  

int main()
{
   DDRC=0xFF;
   INTO_init();
  _delay_ms(20);
  char a;
  while(1)
  {

          a = usart_rec();
		  _delay_ms(10);
		 if(a=='F')
		 {
			  PORTC=0b00000001;
			  _delay_ms(200);
		 }
		  else if(a=='B')
		 {
			  PORTC=0b00000010;
			  _delay_ms(200);
		 }
	
    
	 
	
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
                     
