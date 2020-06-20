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

int ADC_read(int read)
 {
    ADMUX=read|0x40;
	ADCSRA=0xD7;
	while((ADCSRA & 0x10)==0);
	return ADC;
 }


int main()
{
   DDRC=0xFF;
   DDRB=0x11111110;
   lcd_init();
   _delay_ms(100);
   lcd_command(0x80);
   lcd_string("KOUSIK BAG");
   int a,b;
   int count=0;
   DDRD=0xFF;
   while(1)
   {

       trigger();
	   for(unsigned int i=0;i<=37000;i++)
	     {
	        if(PINB==0x01)
	          {
	            while(PINB==0x01)
		         {
		           count++;
			       _delay_us(1);
                  }
              }
			  _delay_us(1);
         }
	 count=count/69;
	 lcd_command(0xC0);
	 lcd_string("DIST");
	 _delay_ms(100);
	 lcd_command(0xC6);
	 lcd_num(count);
	 _delay_ms(100);
   }
}

void trigger()
{
  PORTD=0x01;
  _delay_us(10);
  PORTD=0x00;
  _delay_us(400);
  
 }
