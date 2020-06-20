#define F_CPU 8000000UL
#define get_bit(reg,bitnum) ((reg & (1<<bitnum))>>bitnum) // get bit macro used to get the value of a certain bit.
#include <avr/io.h>
#include <util/delay.h>
void TWI_Init (void);
void TWI_Start (void);
void TWI_Stop (void);
void TWI_Write (char data);
void TWI_Read_Nack (char* ptr);
void EEPROM_Write (char data, char address);
void EEPROM_Read (char address, char* ptr);

void TWI_Init (void)
{
     //set_bit(TWCR,6);
       TWSR=0;
       TWBR=0x07;
       TWCR|=(1<<TWEN);
}




void TWI_Start (void)

{

       TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

       while (get_bit(TWCR,TWINT)==0)

       {

       }

}




void TWI_Stop (void)

{

       TWCR=(1<<TWSTO)|(1<<TWEN)|(1<<TWINT);

}




void TWI_Write (char data)

{

       TWDR=data;

       TWCR= (1<<TWINT)|(1<<TWEN);

       while (get_bit(TWCR,TWINT)==0)

       {

       }

}




void TWI_Read_Nack (char* ptr) // The function argument is a pointer to a memory place in the MCU to store the received data in

{

       TWCR=(1<<TWINT)|(1<<TWEN);

       while (get_bit(TWCR,TWINT)==0)

       {

       }

       *ptr=TWDR;

}




void EEPROM_Write (char data, char address)

{

       TWI_Start();

       TWI_Write(0xA8); //slave address is 1010.100 and a 0 in the 8th bit to indicate Writting.

       TWI_Write(address);

       TWI_Write(data);

       TWI_Stop();

}

void EEPROM_Read (char address, char* ptr) // the function arguments are an address in the EEPROM to read from and a pointer to a memory place in the MCU to store the read data in

{

       TWI_Start();

       TWI_Write(0xA8);

       TWI_Write(address);

       TWI_Start();

       TWI_Write(0xA9);

       TWI_Read_Nack(ptr);

       TWI_Stop();




}




int main(void)

{

       char R;

       DDRD=0b11111111;

       TWI_Init();

       while(1)

       {

              EEPROM_Write(0xE0,0x00);

              _delay_ms(1000); // You must allow suffcent delay for the EEPROM to complete the its internal write cycle

              EEPROM_Read(0x00,&R);

              if (R==0xE0)

              {

                     PORTD=0b01000000;

              }

       }

}
