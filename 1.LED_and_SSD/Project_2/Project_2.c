//Traffic Light Controlling Prototype

#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
void usart_string(unsigned char *a);
void usart_send(char send);
char usart_rec();
void usart_init();
void int_tx(int data);
void msg_send(char num,char msg);

int main()
{
	DDRC=0xff;
	DDRB=0xff;
    DDRD &=~(1<<PD2);
    MCUCR|=(1<<ISC01);   //Falling edge on INT0 triggers interrupt.
    GICR|=(1<<INT0);     //Enable INT0 interrupt
    sei(); 
	 
     usart_init();
	_delay_ms(100);
	while(1)
	{
		led_traffic();


	}
}
ISR(INT0_vect)//interrup service routine
 {
   cli();
  msg_send("8017896720","Ambulence on the way");
  PORTB=0X00;
  PORTC=0X00;
 
  PORTB |=(1<<PB6);
  PORTB |=(1<<PB0);
  PORTB |=(1<<PB3);
  PORTC |=(1<<PC2);
  _delay_ms(8000);

  sei();


 }

void led_traffic()
{
        PORTB=0b01001100;
		PORTC=0b00000010;
		_delay_ms(2000);
		PORTB=0b01001010;
		_delay_ms(200);

		PORTB=0b01100001;
		PORTC=0b00000010;
		_delay_ms(2000);
		PORTB=0b01010001;
		_delay_ms(200);

		PORTB=0b00001001;
		PORTC=0b00000011;
		_delay_ms(2000);
		PORTB=0b10001001;
		PORTC=0b00000010;
		_delay_ms(200);

		PORTB=0b01001001;
		PORTC=0b00001000;
		_delay_ms(2000);
		PORTC=0b00000100;
		_delay_ms(200);
}

void int_tx(int data)
{
  int wc=0;
  unsigned char ulta[5];
  unsigned char sidha[5];
  int r=0,j1=0,i1=0;
  if(data==0)
  {
    usart_send(48);
  }

 while(data!=0)
 {
    r=data%10;
    data=data/10;
    ulta[i1]=r+48;
    i1++;
    _delay_ms(100);
    wc=1;
 }
  if(wc==1)
  {
  for(j1=0;j1<=(i1-1);j1++)
  {
    sidha[j1]=ulta[(i1-1)-j1];
  }
   sidha[j1]='\0';
   usart_string(sidha);wc=0;
   }
}
//////////////////////////////


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
void usart_string(unsigned char *a)
{
    int i2=0;
	while(a[i2]!='\0')
	{
		usart_send(a[i2]);
		i2++;
	}
	

}


void msg_send(char num,char msg)
{
   usart_string("AT+CMGF=1");
   usart_send(0x0d);
  _delay_ms(1000);
  usart_string("AT+CMGS=");
  usart_send(0x22);
  usart_string(num);
  usart_send(0x22);
  //usart_send('"');
  usart_send(0x0d);
  _delay_ms(1000);
  usart_string(msg);
  usart_send(0x1A);
  _delay_ms(1000);
}

