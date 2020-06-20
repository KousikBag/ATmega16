//Touch Screen Based Pattern Locking Enabled Locker
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
  DDRC=0XFF;
 
  lcd_init();
  _delay_ms(10);
  while(1)
  {
  lcd_command(0x01);
  _delay_ms(100);
	DDRA=0b00000101;
	PORTA=0b00000001;
	int x=ADC_read(1);
	_delay_ms(10);
	DDRA=0b00001010;
	PORTA=0b00000010;
	int y=ADC_read(0);
	_delay_ms(10);
	lcd_command(0x83);
	lcd_num(x);
	lcd_command(0xc3);
	lcd_num(y);
	_delay_ms(500);

	if((x>=150)&&(y>=150))
	{
	  if((x>=400)&&(y>=150))
	   {
	     if((x>=600)&&(y>=150))
		 {
		   if((x>=700)&&(y>=150))
		   {
		    if((x>=800)&&(y>=150))
			 {
			  if((x>=800)&&(y>=400))
			  {
			   if((x>=800)&&(y>=700))
			   {
			    if((x>=800)&&(y>=800))
				{
               lcd_command(0x86);
			   lcd_string("DoorUnlock");
			   _delay_ms(2000);
              }
            }
        }
      }
    }
  }}}}
}

