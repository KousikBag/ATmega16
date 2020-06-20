//Interfacing 4x3 Keypad Matrix and displaying results(numbers) on LCD
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#define lcd PORTC
#define rs 0
#define rw 1
#define en 2
void lcd_init()						//lcd initialization function
{
	lcd_command(0x02);
 	lcd_command(0x28);
	lcd_command(0x06);
	lcd_command(0x0c);
	lcd_command(0x01);
}

void lcd_command(unsigned char com)	   //command function
{

	lcd = com & 0xF0;	//send higher bit	

	lcd &= ~(1<<rs); 	//rs =0
	lcd &= ~(1<<rw);	//rw =0	
	lcd |=(1<<en);		//en =1		
	_delay_ms(1);
	lcd &= ~(1<<en);	//en =0	
	_delay_ms(1);

	lcd = (com<<4) & 0xF0;  //send lower bit	

	lcd &= ~(1<<rs); 	//rs =0		
	lcd &= ~(1<<rw);	//rw =0
	lcd |=(1<<en);		//en =1		
	_delay_ms(1);
	lcd &= ~(1<<en);	//en =0
	_delay_ms(1);
}

void lcd_data(unsigned char value)   //data function
{

	lcd =value & 0xF0;	 //send higher bit	

	lcd |= (1<<rs); 	//rs =1	
	lcd &= ~(1<<rw);	//rw =0	
	lcd |=(1<<en);		//en =1		
	_delay_ms(1);
	lcd &= ~(1<<en);	//en =0	
	_delay_ms(1);


	lcd =(value<<4) & 0xF0;	 //send lower bit

	lcd |= (1<<rs); 	//rs =1	
	lcd &= ~(1<<rw);	//rw =0
	lcd |=(1<<en);		//en =1		
	_delay_ms(1);		
	lcd &= ~(1<<en);	//en =0	
	_delay_ms(1);
	
}


void lcd_string(unsigned char *a)    //lcd string function
{
    while(*a!='\0')
	{
	 lcd_data(*a);
	 a++;
    }
}

void lcd_num(unsigned int num)
{
	lcd_command(0x04);
	unsigned int i;
	while(num!=0)
	{
		i=num%10;
		lcd_data(i+48);
		num=num/10;
	}
	lcd_command(0x06);
}


int main()
{
  DDRC=0xFF;
  lcd_init();
  _delay_ms(100);
  keypad_init();
  
  while(1)
  {
    int a=keypad();
	lcd_command(0x85);
	lcd_string("WELCOME");
	_delay_ms(100);
	if(a==1)
	{
	  lcd_command(0xc5);
	  lcd_num(1);
	  _delay_ms(100);
	  lcd_command(0x01);
	   _delay_ms(100);

    }
	else if(a==2)
	{
	  
	  lcd_command(0xc5);
	  lcd_num(2);
	  _delay_ms(100);
	   lcd_command(0x01);
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
