
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#include <stdio.h>
//#include"TechieNest.h"


char val,val1,val2;

void getnotify();
void get1();
void get();
void send2();
void send1();
void send();
void fp_search();

void serial_init()
{
	UCSRB = 0X18;
	UCSRC = 0X8E;
	UBRRL = 51;
	UBRRH = 0;
}


unsigned int getdata()
{
	while ((UCSRA & (1 << RXC)) == 0);
	{
	}    // Do nothing until data has been received and is ready to be read from UDR
	
	return UDR; // return the byte
}



void putdata(unsigned char send)
{    while(!(UCSRA & (1<<UDRE)))
	{
	}
	UDR=send;
}
void lcd_data(unsigned int data)
{
	unsigned int ln ,un;

	un=data&0xf0;
	PORTB=un|0x05;
	_delay_ms(10);
	PORTB=0x01;
	_delay_ms(2);

	ln=(data<<4)&0xf0;
	PORTB=ln|0x05;
	_delay_ms(10);
	PORTB=0x01;
	_delay_ms(2);

}

void lcd_num(unsigned int num)
{
	lcd_cmd(0x04);
	unsigned int i;
	while(num!=0)
	{
		i=num%10;
		lcd_data(i+48);
		num=num/10;
	}
	lcd_cmd(0x06);
}

void lcd_str(char *str)
{
	unsigned int i=0;
	while(str[i]!='\0')
	{
		lcd_data(str[i]);
		i++;
	}
}

void lcd_cmd(unsigned int cmd)
{
	unsigned int ln ,un;

	un=cmd&0xf0;
	PORTB=un|0x04;
	_delay_ms(10);
	PORTB=0x00;
	_delay_ms(2);

	ln=(cmd<<4)&0xf0;
	PORTB=ln|0X04;
	_delay_ms(10);
	PORTB=0x00;
	_delay_ms(2);


}

void lcd_init()
{
	lcd_cmd(0x02);
	lcd_cmd(0x28);
	lcd_cmd(0x0c);
	lcd_cmd(0x06);


}
int main()
{
	DDRA=0xfe;
	PORTA=0x01;
	DDRB=0xff;
	DDRC=0xff;
	lcd_init();
	serial_init();
	lcd_cmd(0X01);
	_delay_ms(800);
	lcd_cmd(0x85);
	lcd_data('m');
	char buff[20];
	_delay_ms(2000);
	
	while(1)
	{
		lcd_cmd(0xc0);
		lcd_str("Command Exexuted");
		if(PINA==0x00)
		{PORTC=0xff;

			fp_search();
			lcd_cmd(0x88);
			lcd_data(val1);
			_delay_ms(100);
			sprintf(buff,"%x--%x",val1,val2);
			lcd_cmd(0xc0);
			lcd_str(buff);
			_delay_ms(1000);
			if(val1==0x00)
			{
				lcd_cmd(0xc0);
				lcd_str("Command Exexuted");_delay_ms(1000);
				lcd_cmd(0x01);_delay_ms(80);
				if(val2==0x00)
				{
					lcd_cmd(0xc0);
					lcd_str("aditya");_delay_ms(1000);
					lcd_cmd(0x01);_delay_ms(80);
				}
				else if(val2==0x01)
				{
					lcd_cmd(0xc0);
					lcd_str("gaurav");_delay_ms(1000);
					lcd_cmd(0x01);_delay_ms(80);
				}
				else if(val2==0x02)
				{
					lcd_cmd(0xc0);
					lcd_str("Right thumb");_delay_ms(1000);
					lcd_cmd(0x01);_delay_ms(80);
				}
			}
			else
			{
				lcd_cmd(0xc0);
				lcd_str("Command NOt Exexuted");_delay_ms(1000);
				lcd_cmd(0x01);_delay_ms(80);
			}
			PORTC=0xff;
		}
		else
		{
			lcd_cmd(0xc0);
			lcd_str("press *");_delay_ms(80);
		}
	}
}

void fp_search()
{
	send();
	PORTC=0X01;
	get();
	
	send1();
	
	get1();
	PORTC=0X04;
	send2();
	getnotify();
	PORTC=0X05;
}

void send()              //  GenImg
{
	putdata(0xEF);
	putdata(0x01);
	putdata(0xFF);
	putdata(0xFF);
	putdata(0xFF);
	putdata(0xFF);
	putdata(0x01);
	putdata(0x00);
	putdata(0x03);
	putdata(0x01);
	putdata(0x00);
	putdata(0x05);
}

void send1()			//To generate character file from image
{
	putdata(0xEF);putdata(0x01);putdata(0xFF);putdata(0xFF);putdata(0xFF);
	putdata(0xFF);putdata(0x01);putdata(0x00);putdata(0x04);putdata(0x02);
	putdata(0x01);putdata(0x00);putdata(0x08);
}

void send2()
{
	putdata(0xEF);putdata(0x01);putdata(0xFF);putdata(0xFF);putdata(0xFF);
	putdata(0xFF);putdata(0x01);putdata(0x00);putdata(0x08);putdata(0x1B);
	putdata(0x01);putdata(0x00);putdata(0x00);   putdata(0x03);putdata(0xE9);
	putdata(0x01);putdata(0x11);
}

void get()
{
	val=getdata();PORTC=0X02;val=getdata();val=getdata();
	val=getdata();val=getdata();val=getdata();
	val=getdata();PORTC=0X03;val=getdata();val=getdata();
	val=getdata();PORTC=0X13;val=getdata();PORTC=0X23;val=getdata();
}

void get1()
{
	val=getdata();val=getdata();val=getdata();
	val=getdata();val=getdata();val=getdata();
	val=getdata();val=getdata();val=getdata();
	val=getdata();val=getdata();val=getdata();
}
void getnotify()
{
	val=getdata();val=getdata();val=getdata();
	val=getdata();val=getdata();val=getdata();
	val=getdata();val=getdata();val=getdata();
	val1=getdata();val=getdata();val2=getdata();
	val=getdata();val=getdata();val=getdata();
	val=getdata();
}
