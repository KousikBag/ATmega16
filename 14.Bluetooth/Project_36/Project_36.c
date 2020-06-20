//Voice control Smart Automation

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
 // function for compare 
int str_cmp(char *arr1,char *arr2) 
{
 int count=0;
  for(int i=0;i<12;i++)
   {
         if(arr1[i]==0x23||arr2[i]==0x23)
		 {
		   return count;
		 }
         if(arr1[i]==arr2[i])
		 {
		      count=1;
		 }
		 else
		 {
		      count=0;
			  return count;
		 }
   }
}
int main()
{ 
   char a[12],b[4]="*on#",c[5]="*off#",d[5]="*Fon#",e[6]="*Foff#";
   DDRC=0xff;
   usart_init();
while(1)
{
int i,k=0,count=0;
   for(i=0;i<12;i++)
   {
        a[i]=usart_rec();
		k++;
	    if(a[i]==0x23)
	    {
	        break;
	    }	 
   }  
   for(i=0;i<12;i++)
   {
         usart_send(a[i]);
	    if(a[i]==0x23)
	   {
	        break;
	   }	 
   }
   count=str_cmp(a,b);//for ligt on
   if(count==1)
   {
      PORTC=0b00000001;
   }   
   count=str_cmp(a,c); //for light off
   if(count==1)
   {
        PORTC=0b00000000;
   } 
   count=str_cmp(a,d); //for fan on
   if(count==1)
   {
        PORTC=0b00001000;
   } 
   count=str_cmp(a,e); //for fan off
   if(count==1)
   {
        PORTC=0b00000000;
   } 
   


}
return 0;
}
