#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
int main(void)
{

  DDRC=0xFF;
  int i,j;
  int a[7]= { 0b10000000,0b01000000, 0b00100000, 0b00010000,0b00001000,0b00000100, 0b00000010, 0b00000001};

  while(1)
  {
  for( i=0;i<=7;i++)
    {
	  PORTC=i;
	  _delay_ms(500);
	}
    for(j=7;j<=7;j--)
	    {
		  PORTC=j;
		  _delay_ms(20);
         }
	  
	  
  
  
  
  

}
 return(0);
 }



/*for(int c=0;c<=8;c++)
        {
             int b=pow(2,c);
            PORTC |=b;
            _delay_ms(500);
             int a=255-b;
            PORTC &=a;
            _delay_ms(500);
       }
	   */
