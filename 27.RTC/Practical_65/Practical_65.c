//Displaying RTC format data on LCD

#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<stdio.h>


char mystr[8];
int temp;
unsigned char address =0x20,read=1,write=0,write_data=0x01,recv_data;

void i2c_init(void) // Function to initialize master
{
    TWBR=32;    // Bit rate
    TWSR=(0<<TWPS1)|(0<<TWPS0);    // Setting prescalar bits
    // SCL freq= F_CPU/(16+2(TWBR).4^TWPS)
}

void i2c_start(void)
{
    // Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
    TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);    
    while(!(TWCR & (1<<TWINT))){} // Wait till start condition is transmitted
    while((TWSR & 0xF8)!= 0x08);
 // Check for the acknowledgement
}

void I2C_START_RX(unsigned char data)
{
    TWDR=data;    // Address and read instruction
    TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
    while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte received
    //while((TWSR & 0xF8)!= 0x40);  // Check for the acknoledgement
} 

void  I2C_START_TX(unsigned char data)
{
TWDR=data;
TWCR=(1<<TWINT)|(1<<TWEN);
while(!(TWCR&(1<<TWINT)));
//while((TWSR&0x10)!=0x10);//while((TWSR&0xf8)!=0x18);

}
void i2c_transmit(unsigned char data)
{
    TWDR=data;    // put data in TWDR
    TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
    while (!(TWCR & (1<<TWINT)));// Wait till complete TWDR byte transmitted
    //while((TWSR & 0xF8) != 0x28); // Check for the acknoledgement
}

void i2c_stop(void)
{
    // Clear TWI interrupt flag, Put stop condition on SDA, Enable TWI
    TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWSTO)|(0<<TWSTA);    
   //while(!(TWCR & (1<<TWSTO)));  // Wait till stop condition is transmitted
}

int i2c_receive(void)
{
    TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
    while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
    //while((TWSR & 0xF8) != 0x58); // Check for the acknoledgement
    return TWDR;
}

void TWI_repeated_start()
{
TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
while(!(TWCR&(1<<TWINT)));
while((TWSR&0XF8)!=0X10);
}


#define LCD PORTA
#define RS  PA0
#define RW  PA1
#define EN  PA2

void lcd_data(char dat)
{
	LCD = dat & 0xf0;
	LCD |= (1<<RS);
	LCD	&= ~(1<<RW);
	LCD |= (1<<EN);
	_delay_ms(1);
	LCD &= ~(1<<EN);

	LCD = (dat<<4) & 0xf0;
	LCD |= (1<<RS);
	LCD	&= ~(1<<RW);
	LCD |= (1<<EN);
	_delay_ms(1);
	LCD &= ~(1<<EN);
}
void lcd_cmd(char cmd)
{
	LCD = cmd & 0xf0;
	LCD &= ~(1<<RS);
	LCD	&= ~(1<<RW);
	LCD |= (1<<EN);
	_delay_ms(1);
	LCD &= ~(1<<EN);

	LCD = (cmd<<4) & 0xf0;
	LCD &= ~(1<<RS);
	LCD	&= ~(1<<RW);
	LCD |= (1<<EN);
	_delay_ms(1);
	LCD &= ~(1<<EN);
}
void lcd_init()
{
	lcd_cmd(0x02);
	lcd_cmd(0x28);
	lcd_cmd(0x0c);
	lcd_cmd(0x06);
}
void lcd_gotoxy(int clm,int row)
{
	if(row==0)
		lcd_cmd(0x80+clm);
	if(row==1)
		lcd_cmd(0xc0+clm);
}
void lcd_string(char *str)
{
	while(*str!='\0')
	{
		lcd_data(*str);
		_delay_ms(10);
		str++;
	}
}

int Read_RTC(char add)
{
 int temp1;
i2c_start();
 I2C_START_TX(0b11010000);
  i2c_transmit(add);
i2c_stop();
  i2c_start();
 

 I2C_START_RX(0b11010001);

 temp1 = i2c_receive();
 i2c_stop();
 return(temp1);
}

int Write_RTC(char add,char data1)
{
  i2c_start();
 i2c_transmit(0xd0);
 //I2C_START_TX(0b11010000); //device add
 //2C_START_TX(0xd0);
 
    i2c_transmit(add); //Reg. add.
	
 i2c_transmit(data1);

 i2c_stop();

return 0;
}

//=======================================================================
//                           SET TIME
//=======================================================================
void SetTime(char HH,char MM, char SS, char ampm)
{

 sprintf(mystr,"%03d",SS);
 Write_RTC(0x00,((mystr[1] - 0x30) << 4) | (mystr[2] - 0x30));
 sprintf(mystr,"%03d",MM);
 Write_RTC(0x01,((mystr[1] - 0x30) << 4) | (mystr[2] - 0x30));


 sprintf(mystr,"%03d",HH);
 if(ampm == 1)
 {
  Write_RTC(0x02,((((mystr[1] - 0x30) << 4) | (mystr[2] - 0x30)) | 0x40) | 0x20);
    }
 else
 {
  Write_RTC(0x02,((((mystr[1] - 0x30) << 4) | (mystr[2] - 0x30)) | 0x40));
 }
}
//=======================================================================
char GetHH()
{
 return Read_RTC(0x02);
}
//=======================================================================
char GetMM()
{
 return (Read_RTC(0x01) & 0x7F);
}
//=======================================================================
char GetSS()
{
 return Read_RTC(0x00);
}
//=======================================================================
//                   SET DATE
//=======================================================================
void SetDate(char DD,char MM, char YY)
{

 sprintf(mystr,"%03d",DD);
 Write_RTC(0x04,((mystr[1] - 0x30) << 4)  | (mystr[2] - 0x30));

 sprintf(mystr,"%03d",MM);
 Write_RTC(0x05,((mystr[1] - 0x30) << 4) | (mystr[2] - 0x30));

 sprintf(mystr,"%03d",YY);
 Write_RTC(0x06,((mystr[1] - 0x30) << 4)  | (mystr[2] - 0x30));
}
//=======================================================================
char GetDD()
{
 return Read_RTC(0x04);
}

//=======================================================================

char GetMonth()
{
 char j;
 j=Read_RTC(0x05);
 j=(j & 0x0F) + ((j >> 4) * 10);
 return j; //12/11
}

//=======================================================================
char GetYY()
{
 char k;
 k=Read_RTC(0x06);
 k=(k & 0x0F) + ((k >> 4) * 10);
 return k;
}
//=======================================================================
//                    Display Date and Time
//=======================================================================
void DisplayDateTime()
{
  temp = Read_RTC(0x00);
  
  mystr[7]=48+(temp & 0b00001111);
  mystr[6]=48+((temp & 0b01110000)>>4);
  mystr[5]=':';
 
  temp = Read_RTC(0x01);
  
  mystr[4]=48+(temp & 0b00001111);
  mystr[3]=48+((temp & 0b01110000)>>4);
  mystr[2]=':';
 
  temp = Read_RTC(0x02);
  
  mystr[1]=48+(temp & 0b00001111);
  mystr[0]=48+((temp & 0b00010000)>>4);

  lcd_cmd(0xc1); 
  lcd_string("Time:");
  
  lcd_data(mystr[0]);
  lcd_data(mystr[1]);
  lcd_data(mystr[2]);
  lcd_data(mystr[3]);
  lcd_data(mystr[4]);
  lcd_data(mystr[5]);
  lcd_data(mystr[6]);
  lcd_data(mystr[7]);

  temp = Read_RTC(0x02);
  temp = temp & 0x20;
  if(temp == 0x20)
  {
   lcd_string(" PM");
  }
  else
  {
   lcd_string(" AM");
  }
  temp = Read_RTC(0x06);
  
  mystr[7]=48+(temp & 0b00001111);
  mystr[6]=48+((temp & 0b01110000)>>4);
  mystr[5]=':';
 
  temp = Read_RTC(0x05);
  
  mystr[4]=48+(temp & 0b00001111);
  mystr[3]=48+((temp & 0b01110000)>>4);
  mystr[2]=':';
 
  temp = Read_RTC(0x04);
  
  mystr[1]=48+(temp & 0b00001111);
  mystr[0]=48+((temp & 0b00110000)>>4);
  
  lcd_cmd(0x81);
  lcd_string("Date:");
  
  lcd_data(mystr[0]);
  lcd_data(mystr[1]);
  lcd_data(mystr[2]);
  lcd_data(mystr[3]);
  lcd_data(mystr[4]);
  lcd_data(mystr[5]);
  lcd_data(mystr[6]);
  lcd_data(mystr[7]);
}

int main()
{
_delay_ms(150);
DDRA=0XFF;     //LCD is connected to PORTA.
char buff[20];
char h,m,s;
lcd_init();    // initialize lcd.
i2c_init();   //   intialize  i2c.
_delay_ms(10);
lcd_cmd(0x85);
lcd_string("KOUSIK");


//SetTime(11,11,11, 1);

lcd_cmd(0x01);
_delay_ms(10);
while(1)
{
DisplayDateTime();
_delay_ms(10);
}

}
