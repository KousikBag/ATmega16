//Storing/Retrieving Security passwords to EEPROM

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
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



void EEPROM_write(char address,char data);
char EEPROM_read(char address);


int main(void)
{
	
	DDRC=0xFF;
	lcd_init();
	lcd_command(0x01);
	_delay_ms(100);
	while(1)
    {
	 lcd_command(0x81);
	 lcd_string("Enter Your Password");
	 _delay_ms(1000);
	 lcd_command(0x01);
     EEPROM_write(0x10,0x41);//To write character A on the given address 0x10 "65-Ascii Value for A in hexa 0x41"
	 char c= EEPROM_read(0x10);//To read it from EEPROM
	 lcd_command(0x85);
	 lcd_data(c);//To display the read character 'A' stored in EEPROM on LCD 
	 _delay_ms(1000);

	 EEPROM_write(0x11,0x42);//To write character B on the given address 0x10 "65-Ascii Value for B in hexa 0x42"
	 char b= EEPROM_read(0x10);//To read it from EEPROM
	 lcd_command(0x85);
	 lcd_data(b);//To display the read character 'B' stored in EEPROM on LCD 
	 _delay_ms(1000);
	 lcd_command(0x01);
	 lcd_command(0xC0);
	 lcd_string("EEPROM SUCCESSFUL");
	
	 _delay_ms(1000);
	  lcd_command(0x01);
	    //TODO:: Please write your application code 
    }
}

void EEPROM_write(char address,char data)
{
  while( EECR & (1<< EEWE));//Wait For Completion Of Previous Write
     EEAR=address;
     EEDR= data;
     EECR|= (1<< EEMWE);
     EECR|=(1<< EEWE);//Set EEPROM by setting EEWE to 1
    
}
 char EEPROM_read(char address)
{
  while(!(EECR & (1<< EEWE)));//Wait For Completion Of Previous Write
     EEAR=address;
     EECR|=(1<< EERE);//Set EEPROM for read by setting EERE to 1
     return EEDR;
}
