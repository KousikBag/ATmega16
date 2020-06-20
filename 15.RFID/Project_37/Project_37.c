//RFID based Attendance System

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
    int i=0;
	while(a[i]!='\0')
	{
		usart_send(a[i]);
		i++;
	}
	
}




int main()
{
   
   DDRC=0xFF;
   lcd_init();
   usart_init();
   _delay_ms(10);
   lcd_command(0x80);
   lcd_string("RFID attendence");
   lcd_command(0xC0);
   lcd_string("Place your Card:");

   

   static char a[12];
   char b[12]="180089202E9F";
   char c[12]="180089108405";
   char d[12]="180089192EA6";
   char e[12]="1800891DED61";
   
   while(1)
   {
   int count1=0;
   int count2=0;
   int count3=0;
   int count4=0;
      for(int i=0;i<=11;i++)
	  {
	    a[i]=usart_rec();
		
      }
	  
	  

	  for(int j=0;j<=11;j++)
	  {
	  if(a[j]==b[j])
	  {count1++;}
	  if(a[j]==c[j])
	  {count2++;}
	  if(a[j]==d[j])
	  {count3++;}
	  if(a[j]==e[j])
	  {count4++;}
	  }
	  

	  if(count1==12)
	  {
	    lcd_command(0x01);
		_delay_ms(10);
		lcd_command(0xC0);
		lcd_string("KOUSIK PRESENT");
		_delay_ms(1000);
		lcd_command(0x01);
		_delay_ms(10);
		count1=0;count2=0;
		count3=0;count4=0;

		}
		else if(count2==12)
	    {
	      lcd_command(0x01);
		  _delay_ms(10);
		 lcd_command(0xC0);
		 lcd_string("KAPIL PRESENT");
		 _delay_ms(1000);
		 lcd_command(0x01);
		 _delay_ms(10);

		 count1=0;count2=0;
		 count3=0;count4=0;

		}
		else if(count3==12)
	    {
	      lcd_command(0x01);
		  _delay_ms(10);
		 lcd_command(0xC0);
		 lcd_string("RAM PRESENT");
		 _delay_ms(1000);
		 lcd_command(0x01);
		 _delay_ms(10);

		 count1=0;count2=0;
		 count3=0;count4=0;

		}
		else if(count4==12)
	    {
	      lcd_command(0x01);
		  _delay_ms(10);
		 lcd_command(0xC0);
		 lcd_string("JOHN PRESENT");
		 _delay_ms(1000);
		 lcd_command(0x01);
		 _delay_ms(10);

		 count1=0;count2=0;
		 count3=0;count4=0;

		}
		else
		{
		lcd_command(0x01);
		  _delay_ms(10);
		 lcd_command(0xC0);
		 lcd_string("NOT authorised");
		 _delay_ms(1000);
		 lcd_command(0x01);
		 _delay_ms(10);
		 count1=0;count2=0;
		 count3=0;count4=0;
		 }
		
	 }
	 return 0;
}


