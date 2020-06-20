#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRC=0xFF;
  int arr[10]={0b11111001,0b10100100,0b10110000,0b10011001,0b10010010,0b00000010,0b11111000,0b10000000,0b10010000,0b11000000};
  while(1)
   {
    for(int i=0;i<=9;i++)
	{
      PORTC=arr[i];
	  _delay_ms(5000);
    }
   }
   return 0;
}
