//Voice Control Robot

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
   char a[12],b[4]="*go#",c[6]="*back#",d[6]="*left#",e[7]="*right#",f[6]="*stop#";
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
   count=str_cmp(a,b);//for forword movement
   if(count==1)
   {
      PORTC=0b00001010;
   }   
   count=str_cmp(a,c); //fot back
   if(count==1)
   {
        PORTC=0b00000101;
   } 
   count=str_cmp(a,d); //fot left
   if(count==1)
   {
        PORTC=0b00000010;
   } 
   count=str_cmp(a,e); //fot right
   if(count==1)
   {
        PORTC=0b00001000;;
   } 
   count=str_cmp(a,f); //stop
   if(count==1)
   {
        PORTC=0b00000000;;
   } 


}
return 0;
}
