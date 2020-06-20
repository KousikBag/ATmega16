//@@@@Multiplexing multiple SSDs using Hardware Optimization@@@@//

#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRA=0xFF;
  DDRC=0xFF;
  int arr[10]={0b11111001,0b10100100,0b10110000,0b10011001,0b10010010,0b00000010,0b11111000,0b10000000,0b10010000,0b11000000};
  while(1)
   {
     for(int i=0;i<=9;i++)
	 {
           PORTC=0b00100000;
		   PORTA=arr[i];
		   _delay_ms(1000);
		   PORTC=0b00010000;
		   PORTA=arr[i];
		   _delay_ms(1000);
		   PORTC=0b00001000;
		   PORTA=arr[i];
		   _delay_ms(1000);
		   PORTC=0b00000100;
		   PORTA=arr[i];
		   _delay_ms(1000);
		   PORTC=0b00000010;
		   PORTA=arr[i];
		   _delay_ms(1000);
		   PORTC=0b00000001;
		   PORTA=arr[i];
		   _delay_ms(1000);
		 }
    }
	return 0;
}
	       
	    

