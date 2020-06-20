#define F_CPU 12000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
void int_tx(int data);
int power(int a1, int b1);
void clr();
void usart_init();
char usart_rec();
void usart_send(char send);
void usart_string(unsigned char *a);
unsigned int ar[33];
unsigned int i=0;
unsigned int arr[7];
unsigned int count=0;
unsigned int d=0,inc=0;
int main()
{
   

     usart_init();
	  _delay_ms(10);
     
      DDRD &=~(1<<PD2); //I/P FOR INTERRUPT
      TCNT1=0;
	  TCCR1B=0x02;
	  MCUCR|=(1<<ISC01);   //Falling edge on INT0 triggers interrupt.
      GICR|=(1<<INT0);     //Enable INT0 interrupt
	  sei();               // Enable global interrupts
      while(1)
        {
		          
		          for(int k=0;k<7;k++)
		          {
		             count=ar[23-k]*power(2,k)+count;
			        }
			        clr();

               
			    int_tx(count);
				_delay_ms(500);
 count=0;
 }

  return 0;
}

/////////////////////////////////
void clr()
{
  for(int i4=0;i4<33;i4++)
  {
    ar[i4]=0;
  }
}
//////////////////////////////////

////////////////////////////////////

 ISR(INT0_vect)//interrup service routine
 {
   if(TCNT1>19000)
   {
     i=0;
   }
 ar[i]=((TCNT1)/2000);
 TCNT1=0;
 i++;
 d++;
}

////////////////////////////


////////////////////////////////
int power(int a1, int b1)
{
	int c1=1;
	if(b1==0)
	{
		return 1;
	}
	else
	{
		for(int i3=1;i3<=b1;i3++)
		{
			c1=c1*a1;
		}
		return c1;
	}

}
//////////////////////////////////

///////////////////////////////////
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




////////////////////////////////////////
void usart_init()
{
 UBRRL=77;
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






