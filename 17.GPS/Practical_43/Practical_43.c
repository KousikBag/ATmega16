//Displaying GPS location coordinates

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


char val,i,GPS_lat[9],GPS_long[10],x;
int n=0;
void usart_init()
{
 UBRRL=51;
 UBRRH=0;
 UCSRB=0x18;
 UCSRC=0x8e;
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

char usart_rec()
{
 while((UCSRA&0x80)==0);
 return UDR;
}


void main()
{
	DDRC=0xFF;  
    
	

	lcd_init();
	_delay_ms(100);

	
	usart_init();
	_delay_ms(100);
  lcd_command(0x85);
  lcd_string("START");
  _delay_ms(100);
  lcd_command(0x01);
  _delay_ms(100);
  _delay_ms(500);
	while(1)
	{
	usart_init();
	_delay_ms(100);
	
	 char val,i,GPS_lat[10],GPS_long[11],x;
	 
	   val=usart_rec();//all the string check
	    
	   if(val=='$')
	    {
		  val=usart_rec();
		   
		   if(val=='G')
		    {
			  val=usart_rec();
			  
			   if(val=='P')
			     {
				   val=usart_rec();
				   
				    if(val=='G')
					 {
					   val=usart_rec();
					   
					    if(val=='G')
						 {
						   val=usart_rec();
						   
						   if(val=='A')
						    {
							  val=usart_rec();
							  
							   if(val==0x2c);
							   {
							       val=usart_rec();//untill get the 2nd ","
								   
								   while(val!=0x2c)
								    {
								      val=usart_rec();
									 
								    }
								 
                                     for(i=0;i<9;i++)
								     {
									   GPS_lat[i]=usart_rec();
									   
									  }
									  val=usart_rec();
									  if(val==0x2c);
							   			{
							       		val=usart_rec();
									  while(val!=0x2c)
								    {
								      val=usart_rec();
									 
								    }
									   for(i=0;i<10;i++)
								      {
									 
									   GPS_long[i]=usart_rec();
									   
									   }
									   GPS_lat[9]='\0';
										GPS_long[10]='\0';
									 val=usart_rec();

									 lcd_command(0x80);
									 lcd_string("lat");

									
									 lcd_command(0x84);
									 lcd_string(GPS_lat);
									 
									  lcd_command(0xc0);
									  lcd_string("long");
									  								
									 lcd_command(0xc5);
									 lcd_string(GPS_long);
									
									 /*usart_string(GPS_lat);
									 _delay_ms(1000);
									 usart_send(0x0d);
									  usart_string(GPS_long);
									 _delay_ms(1000);*/
									  
									 }
								}
                          }
                       }
                   
				    }
                 }
             }
}
}

}
