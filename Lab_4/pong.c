nclude<avr/ioh.>
#include<unistd.h>

int main()
{
        unsigned char pb;
        char direction;
        int count = 8;

        //initialization
        DDRB = 0x0F;
        PORTB = 0xF0;

        while(1){
                if(count == 1){
                        count = 8;
                }
                PINB &= ~(0x0F);
                PINB |= (count >> 1);
                usleep(500000);
}

