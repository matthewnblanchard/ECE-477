#include <stdio.h>
#include <unistd.h>
#include <sys/io.h>
#include <stdlib.h>

#define CLOCK_FREQ 1192500.0

int main(int argc, char *argv[]){

        int final_t = 0;
        int initial_t = 0;
        int port_val = 0;
        double diff = 0;
        FILE *fp;
        int i = 0;
	int j = 0;
        char *str;
	char *ptr;

        // Intialization
        // Set port permissions
        if (ioperm(0x42, 1, 1) || ioperm(0x43, 1, 1) || ioperm(0x61, 1, 1)) {
                printf("Error: ioperm failed ...\n");
                return 1;
        }

        // Enable timer
        port_val = inb(0x61);
        outb(port_val | 1, 0x61);

        // Configure timer channel 2 to output in binary, outputing
        // lower bits then upper bits   
        outb(0xB4, 0x43);

        // Set reload value
        outb(0xFF, 0x42);
        outb(0xFF, 0x42);
        fp = fopen("memoryout.csv", "w");
        for (i = 1; i <= 10000000; i *= 10) {
		str = (char *)malloc(i);
		ptr = str;

               // Read initial time value
               outb(0x08, 0x43);        // Send latch command
               initial_t = inb(0x42);
               initial_t |= (inb(0x42) << 8);

		for(j = 0; j < i; j++){
			*ptr = 5;
			ptr += 1;
		}             	

               // Read final time value
               outb(0x08, 0x43);       // Send latch command
               final_t = inb(0x42);
               final_t |= (inb(0x42) << 8);
		free(str);
		
               // Calculate time
               diff = initial_t - final_t;
               if (diff <= 0) {        // A rollover must have occured
                       diff = initial_t + (0xFFFF - final_t);
               }
               diff /= CLOCK_FREQ;
               diff *= 1000000;
               fprintf(fp, "%d,%f\n", i, diff);
            
        }
        return 0;
}
 
