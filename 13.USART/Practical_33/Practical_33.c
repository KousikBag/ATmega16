//Sending/ Receiving Data from/to PC to/from Microcontroller Displaying it on LCD

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
  while(1)
  {
    char a=usart_rec();
    if(a=='1')
	{
	  PORTC=0x01;
	 
    }
	else if(a=='2')
	{
	  PORTC=0x02;
	}
	else if(a=='3')
	{
	  PORTC=0x03;
	}
	else if(a=='4')
	{
	  PORTC=0x04;
	}
	else if(a=='5')
	{
	  PORTC=0x05;
	}
	else if(a=='6')
	{
	  PORTC=0x06;
	}
	else if(a=='7')
	{
	  PORTC=0x07;
	}
	else if(a=='8')
	{
	  PORTC=0x08;
	}
	else if(a=='a')
	{
	  PORTC=0xFF;
	}
	
  }
}
	  


    
