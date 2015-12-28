/*
 * tk_project.c
 *
 * Created: 19-12-2015 15:53:55
 *  Author: Chaitanya Paikara
 */ 


#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "LCD.h"

int UBRR = 0;
char data = ' ';

void comm_init(void); 
char recieved_byte(void);
void transmitted_byte(char ch);

int main(void)
{
	init();
	comm_init();
	UCSRB |= (1<<TXB8);  // Set bit#8
	transmitted_byte(0xF8);		// address byte
	_delay_ms(50);
	UCSRB |= (0<<TXB8);
	    
	character("T");
    character("E");
    character("A");
    character("M");
    character(" ");
    character("K");
    character("A");
    character("R");
    character("T");
    _delay_ms(2000);
	
	set(0x01);
    _delay_ms(50);
	
	while(1)
    {
	data=recieved_byte();
	character(data);
	
        //TODO:: Please write your application code
    }
}
void comm_init()
{
	UCSRB |= 1<<RXEN | 1<<TXEN ;
	UCSRC |= 1<<URSEL | 1<<UCSZ2 | 1<<UCSZ1 | 1<<UCSZ0 | 1<<USBS;
	UCSRC |= 0<<URSEL; // FOR BAUD RATE
	UBRR = (16000000/(16*9600))-1; // BAUD REGISTER VALUE   (XTAL FREQ/(16*BAUD RATE))-1
	UBRRL = UBRR;
}
char recieved_byte()
{
	while((UCSRA & (1<<RXC))==0);
	return UDR;
}
void transmitted_byte(char ch)
{
	while((UCSRA & (1<<UDRE))==0);
	UDR = ch;
}



