//Taking Input from multiple Keys to MCU to control SSD
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRC=0XFF;
  int arr[10]={0b11111001,0b10100100,0b10110000,0b10011001,0b10010010,0b00000010,0b11111000,0b10000000,0b10010000,0b11000000};
  keypad_init();
  
  while(1)
  {
    int a=keypad();
    
	if(a==1)
	{
	  PORTC=arr[0];
	  _delay_ms(100);
    }
	else if(a==2)
	{
	  PORTC=arr[1];
	  _delay_ms(100);
    }
	else if(a==3)
	{
	  PORTC=arr[2];
	  _delay_ms(100);
    }
	else if(a==4)
	{
	  PORTC=arr[3];
	  _delay_ms(100);
    }
	else if(a==5)
	{
	  PORTC=arr[4];
	  _delay_ms(100);
    }
	else if(a==6)
	{
	  PORTC=arr[5];
	  _delay_ms(100);
    }
	else if(a==7)
	{
	  PORTC=arr[6];
	  _delay_ms(100);
    }
	else if(a==8)
	{
	  PORTC=arr[7];
	  _delay_ms(100);
    }
		else if(a==9)
	{
	  PORTC=arr[8];
	  _delay_ms(100);
    }
	else if(a==10)
	{
	  PORTC=arr[9];
	  _delay_ms(100);
    }
	else if(a==11)
	{
	  PORTC=arr[0];
	  _delay_ms(100);
    }
	else if(a==12)
	{
	  PORTC=arr[1];
	  _delay_ms(100);
    }
  }
}

void keypad_init()
{
  DDRA |=(1<<PA0);//O/P
  DDRA |=(1<<PA1);
  DDRA |=(1<<PA2);

  DDRA &=~(1<<PA3);//INPUT
  DDRA &=~(1<<PA4);
  DDRA &=~(1<<PA5);
  DDRA &=~(1<<PA6);
  

  PORTA |=(1<<PA3);
  PORTA |=(1<<PA4);
  PORTA |=(1<<PA5);
  PORTA |=(1<<PA6);
  
}

//////////////////////

///////////////////////
int  keypad()
{
  
 

  PORTA &=~(1<<PA0);
  PORTA |=(1<<PA1);
  PORTA |=(1<<PA2);
  _delay_ms(50);
  
 if((PINA & 0b01111000)==0b01110000) 
  {
     while((PINA & 0b01111000)==0b01110000);
	 return 1;
	 
  }
 if((PINA & 0b01111000)==0b01101000) 
  {
     while((PINA & 0b01111000)==0b01101000);
	 return 2;
	 
  }
   
  if((PINA & 0b01111000)==0b01011000) 
  {
     while((PINA & 0b01111000)==0b01011000);
	 return 3;
	 
  }
   if((PINA & 0b01111000)==0b00111000) 
  {
     while((PINA & 0b01111000)==0b00111000);
	 return 4;
	 
  }

  PORTA |=(1<<PA0);
  PORTA &=~(1<<PA2);
  PORTA |=(1<<PA3);
  _delay_ms(50);

   if((PINA & 0b01111000)==0b01110000) 
  {
     while((PINA & 0b01111000)==0b01110000);
	 return 5;
	 
  }
 if((PINA & 0b01111000)==0b01101000) 
  {
     while((PINA & 0b01111000)==0b01101000);
	 return 6;
	 
  }
   
  if((PINA & 0b01111000)==0b01011000) 
  {
     while((PINA & 0b01111000)==0b01011000);
	 return 7;
	 
  }
   if((PINA & 0b01111000)==0b00111000) 
  {
     while((PINA & 0b01111000)==0b00111000);
	 return 8;
	 
  }

  PORTA |=(1<<PA0);
  PORTA |=(1<<PA1);
   PORTA &=~(1<<PA2);
  _delay_ms(50);
   if((PINA & 0b01111000)==0b01110000) 
  {
     while((PINA & 0b01111000)==0b01110000);
	 return 9;
	 
  }
 if((PINA & 0b01111000)==0b01101000) 
  {
     while((PINA & 0b01111000)==0b01101000);
	 return 10;
	 
  }
   
  if((PINA & 0b01111000)==0b01011000) 
  {
     while((PINA & 0b01111000)==0b01011000);
	 return 11;
	 
  }
   if((PINA & 0b01111000)==0b00111000) 
  {
     while((PINA & 0b01111000)==0b00111000);
	 return 12;
	 
  }

} 
