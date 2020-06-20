//Virtual Touch Piano

#define F_CPU 800000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRB=0b00001000;
  TCCR2=0b00011111;
  unsigned char arr[10]={1,5,10,15,20,25,30,35,40,45};
  while(1)
  {
    for(int i=0;i<=9;i++)
	{
	  OCR2=arr[i];
	  _delay_ms(2000);
	}
	
	
 }
 return 0;
}
