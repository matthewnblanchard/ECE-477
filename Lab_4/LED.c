#include<avr/io.h>

int main()
{
	unsigned char pb;

	DDRB = 0x0F;

	PORTB = 0xF0;

	while(1) {
		pb = PINB;
		PINB &= ~(0x0F);
		PINB |= ~(pb >> 4);
	}
	return 0;
}
