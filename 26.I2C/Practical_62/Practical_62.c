//i2c slave

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void TWI_Init(unsigned char Slave_Addr)
{
   TWAR = Slave_Addr;
}

unsigned char TWI_Read_Data()
{
    unsigned char x; 
    TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while((TWCR & (1<<TWINT)) == 0);
	while((TWSR & (0xF8)) != 0x80);
	x = TWDR;
	return x;
}
void TWI_Match_ACK()
{
  while((TWSR & (0xF8))!= 0x60)
  {
      TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	  while((TWCR & (1<<TWINT)) == 0);
  }
}

int main()
{
char x;
   DDRB = 0xFF;
   DDRD = 0xFF;
   DDRC = 0xFF;
   lcd_init();
   TWI_Init(0x22);
   lcd_str("I2C Slave Init");

   while(1)
   {
     lcd_cmd(0xc0);
     TWI_Match_ACK();
     x = TWI_Read_Data();
	 lcd_str("Received -> ");
	 lcd_data(x);
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
