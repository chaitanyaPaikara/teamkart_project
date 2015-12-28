#ifndef LCD_h
#define LCD_h
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#define LCDPORT PORTB
#define RS PD4
#define RW PD5
#define EN PD6
#define CONTROL_PORT PORTD
void init(void);
void character(char ch);
void set(char comm);
void check_busy(void);


void check_busy()
{
	DDRB = 0;
	CONTROL_PORT |= 1<<RW | 0<<RS | 0<<EN;
	while (LCDPORT >= 0x80);
	{
		CONTROL_PORT |= 1<<EN;
		_delay_ms(1);
		CONTROL_PORT |= 0<<EN;
	}
	DDRB = 0xFF;
}
void init()
{
	DDRD = 0xFF;
	set(0x38);
	//_delay_ms(50);
	set(0x01);
	//_delay_ms(50);
	set(0x0E);
	//_delay_ms(50);
	set(0x80);
	//_delay_ms(50);
	CONTROL_PORT = 0;
}
void character(char ch)
{
	//check_busy();
	DDRB=0xFF;
	LCDPORT=ch;
	CONTROL_PORT |= 0<<RW |1<<RS | 1<<EN;
	_delay_ms(1);
	CONTROL_PORT = 0<<RW |1<<RS | 0<<EN;
	//_delay_ms(50);
}
void set(char comm)
{
	//check_busy();
	DDRB=0xFF;
	LCDPORT=comm;
	CONTROL_PORT |= 0<<RW |0<<RS | 1<<EN;
	_delay_ms(1);
	CONTROL_PORT = 0<<RW |0<<RS | 0<<EN;
	//_delay_ms(50);
}

#endif