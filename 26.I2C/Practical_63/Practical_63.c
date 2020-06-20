//i2c master

#define F_CPU 8000000UL 
#include <avr/io.h>                    
#include <util/delay.h>         


void TWI_Init()
{
  TWBR = 0x00; 
  TWBR = 0x0C; 
}

void TWI_Start()
{
     TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
	 while((TWCR&(1<<TWINT))==0);
	while((TWSR & (0xF8)) != 0x08);
}

void TWI_Write_Addr(unsigned char Addr)
{
    TWDR = Addr;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while((TWCR & (1<<TWINT)) == 0);
	while((TWSR & (0xF8)) != 0x18);
}

void TWI_Write_Data(unsigned char Data)
{
    TWDR = Data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while((TWCR & (1<<TWINT)) == 0);
	while((TWSR & (0xF8)) != 0x28);
}
void TWI_Stop()
{
     TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}
int main()
{
	DDRB=0xff;
    lcd_init();
    TWI_Init();
	lcd_cmd(0x80);
	lcd_str("I2C Master Init");
    while(1)
	{
	     
	     TWI_Start();
		 _delay_ms(1000);
		 TWI_Write_Addr(0x20);
		 _delay_ms(1000);
		 TWI_Write_Data('1');
		 lcd_cmd(0xc0);
		 lcd_str("write -> 1");
		 _delay_ms(1000);
		 TWI_Stop();
	}
}

void lcd_init()
{
lcd_cmd(0x02);
lcd_cmd(0x28);
lcd_cmd(0x06);
lcd_cmd(0x0c);
}

void lcd_cmd(int cmd)
{
PORTB=(cmd&0xf0)|0x08;
_delay_ms(20);
PORTB=PORTB-0x08;

PORTB=(((cmd<<4)&0xf0)|0x08);
_delay_ms(20);
PORTB=PORTB-0x08;
}

void lcd_data(int data)
{

PORTB=(data&0xf0)|0x0C;
_delay_ms(20);
PORTB=PORTB-0x08;

PORTB=(((data<<4)&0xf0)|0x0C);
_delay_ms(20);
PORTB=PORTB-0x08;
}

void lcd_str(char*str)
{
unsigned int i=0;
while(str[i]!='\0')
{
lcd_data(str[i]);
i++;
}
}

void lcd_num(unsigned int num)
{
unsigned int a;
if(num==0)
{
lcd_data(48);
}
while(num!=0)
{
lcd_cmd(0x04);
a=num%10;
num=num/10;
lcd_data(48+a);
}
lcd_cmd(0x06);
}
