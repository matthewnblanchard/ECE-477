#include<avr/io.h>

int main()
{
	unsigned char count = 8;	//keeper of the bits
	int i = 0;			//delay counter
	int direction = 0;		//direction variable
	unsigned char pb;		//gets input from switches
	
	DDRB = 0x0F;			//Sets input and output
	PORTB = 0xF0;			//enables pull up resistor on upper inputs
	
	while(1){
		pb = PINB;		//read pins
		PINB &= ~(0x0F);	//clear LEDs
		PINB |= count;		//send current position

		//Logic to configure which direction the lights flow
		if( direction == 0){
			count >>= 1;
		}
		else {
			count <<= 1;
		}

		//loops LED position when boundary is reached
		if( count == 0){
			count = 8;
		}
		else if (count == 16){
			count = 1;
		}

		//checks for a specific switch, then changes direction accordingly
		if (!(pb & 0x10)){
			direction = 1;
		}
		else {
			direction = 0;
		}

		//arbitrary delay
		for (i = 0; i < 10000; i++){
		}
	}
	return 0;
}
