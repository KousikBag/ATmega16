//Interfacing Bluetooth with microcontroller & Controlling Microcontroller Operations

#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
void usart_init()
{
 UBRRL=51;
 UBRRH=0;
 UCSRB=0x18;
 UCSRC=0x8e;
}

void usart_send(char send)
{
  while((UCSRA&0x20)==0);
  UDR=send;
}
void usart_string(unsigned char *a)
{
    int i=0;
	while(a[i]!='\0')
	{
		usart_send(a[i]);
		i++;
	}
	
}

char usart_rec()
{
 while((UCSRA&0x80)==0);
 return UDR;
}

int main()
{
  DDRC=0xFF;
  usart_init();
  _delay_ms(10);
  char a;
       while(1)
	 {
	      a = usart_rec();
		  _delay_ms(10);
		 if(a=='F')
		 {
			  PORTC=0b00001010;
			  _delay_ms(200);
		 }
		  else if(a=='B')
		 {
			  PORTC=0b00000101;
			  _delay_ms(200);
		 }
		 else if(a=='L')
		 {
			  PORTC=0b00001000;
			  _delay_ms(200);
		 }
		 else if(a=='R')
		 {
			  PORTC=0b00000010;
			  _delay_ms(200);
		 }
		 else if(a=='S')
		 {
			  PORTC=0b00000000;
			  _delay_ms(200);
		 }
	 
     }
return 0;

}
