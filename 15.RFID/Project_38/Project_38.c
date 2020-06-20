//Smart Card Based Security System

#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
void usart_string(unsigned char *a);
void usart_send(char send);
char usart_rec();
void usart_init();
void int_tx(int data);
void msg_send(char num,char msg);


int main()
{
   


   
         usart_init();
	_delay_ms(100);

   

   static char a[12];
   char b[12]="3B002AF89D74";
   char c[12]="1800895BF43E";
   char d[12]="1800893F8D23";
   char e[12]="18008919EA62";
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
	     msg_send("7877876606","Your Ward Reached at School");
   	     _delay_ms(1000);
		count1=0;count2=0;
		count3=0;count4=0;

		}
		else if(count2==12)
	    {
	       msg_send("9529698354","Your Ward Reached at School");
   	       _delay_ms(1000);

		 count1=0;count2=0;
		 count3=0;count4=0;

		}
		else if(count3==12)
	    {
	      msg_send("9509880092","Your Ward Reached at School");
   	     _delay_ms(1000);

		 count1=0;count2=0;
		 count3=0;count4=0;

		}
		else if(count4==12)
	    {
	       msg_send("8946952707","Your Ward Reached at School");
   	       _delay_ms(1000);

		 count1=0;count2=0;
		 count3=0;count4=0;

		}
		else
		{
		  usart_string("Not authorised");
		  _delay_ms(50);
		 count1=0;count2=0;
		 count3=0;count4=0;
		 }
		
	 }
	 return 0;
}


void int_tx(int data)
{
  int wc=0;
  unsigned char ulta[5];
  unsigned char sidha[5];
  int r=0,j1=0,i1=0;
  if(data==0)
  {
    usart_send(48);
  }

 while(data!=0)
 {
    r=data%10;
    data=data/10;
    ulta[i1]=r+48;
    i1++;
    _delay_ms(100);
    wc=1;
 }
  if(wc==1)
  {
  for(j1=0;j1<=(i1-1);j1++)
  {
    sidha[j1]=ulta[(i1-1)-j1];
  }
   sidha[j1]='\0';
   usart_string(sidha);wc=0;
   }
}
//////////////////////////////


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
    int i2=0;
	while(a[i2]!='\0')
	{
		usart_send(a[i2]);
		i2++;
	}
	

}


void msg_send(char num,char msg)
{
   usart_string("AT+CMGF=1");
   usart_send(0x0d);
  _delay_ms(1000);
  usart_string("AT+CMGS=");
  usart_send(0x22);
  usart_string(num);
  usart_send(0x22);
  //usart_send('"');
  usart_send(0x0d);
  _delay_ms(1000);
  usart_string(msg);
  usart_send(0x1A);
  _delay_ms(1000);
}










