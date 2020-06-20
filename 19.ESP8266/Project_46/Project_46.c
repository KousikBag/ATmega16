//Wi-Fi switch
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>


void usart_init()
{
 UBRRL=51;
 UBRRH=0;
 UCSRB=0x18;
 UCSRC=0x8e;
}

void usart_tx(char send)
{
  while((UCSRA&0x20)==0);
  UDR=send;
}
void usart_str_tx(unsigned char *a)
{
    int i=0;
	while(a[i]!='\0')
	{
		usart_tx(a[i]);
		i++;
	}
	
}

char usart_rx()
{
 while((UCSRA&0x80)==0);
 return UDR;
}

int main()
{
 DDRC=0XFF;
 _delay_ms(10);

 usart_init();
 _delay_ms(10);

 usart_str_tx("AT\r\n");
_delay_ms(1000);


usart_str_tx("AT+CWMODE=3\r\n");
_delay_ms(1000);



usart_str_tx("AT+CIPMUX=0\r\n");
_delay_ms(1000);


usart_str_tx("AT+CWJAP=\"harish\",\"harish123\"\r\n");
_delay_ms(10000);


char x=0;
while(1)
{
      unsigned char val,data;
      int i=0;
      usart_str_tx("AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n");
      _delay_ms(1000);
      usart_str_tx("AT+CIPSEND=97\r\n");
      _delay_ms(1000);
      usart_str_tx("GET https://api.thingspeak.com/channels/321484/fields/1.json?api_key=TFFK6K6RURDXDUVC&results=1\r\n");
      while(i!=21)
      {
      val=usart_rx();
      if(val==':')
      {
        i++;
      }
      }
    val=usart_rx();
    data=usart_rx();
    usart_tx(data);
    usart_str_tx("\r\n");

    if(data=='A')
    {
      PORTC=0b00000001;
    }
    else if(data=='a')
    {
        PORTC=0b00000000;
    }
    
    

}

}




                
