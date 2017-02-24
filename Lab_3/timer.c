#include <stdio.h>
#include <unistd.h>
#include <sys/io.h>

#define CLOCK_FREQ 1192500.0

int main(int argc, char *argv[]){

	int final_t = 0;
	int initial_t = 0;
	int port_val = 0;
	double diff = 0;
	FILE *fp;
	int i = 0;
	int j = 0;	

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

	fp = fopen("out.txt", "w");
	for (i = 1; i <= 2000; i++) {
		for (j = 0; j < 10; j++) {	
			// Read initial time value
			outb(0x08, 0x43);        // Send latch command
			initial_t = inb(0x42);
			initial_t |= (inb(0x42) << 8);

			// Sleep for a bit
			usleep(i);

			// Read final time value
			outb(0x08, 0x43);	// Send latch command
			final_t = inb(0x42);
			final_t |= (inb(0x42) << 8);

			// Calculate time
			diff = initial_t - final_t;
			if (diff <= 0) { 	// A rollover must have occured
				diff = initial_t + (0xFFFF - final_t);
			}
			diff /= CLOCK_FREQ;
			diff *= 1000000;
			fprintf(fp, "%d,%f\n", i, diff);
		}
	}
	return 0;
}

