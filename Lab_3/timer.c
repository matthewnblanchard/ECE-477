#include <stdio.h>
#include <unistd.h>
#include <sys/io.h>

int init(void);

int main(int argc, char *argv[]){

	int final_t = 0;
	int initial_t = 0;
	int port_val = 0;

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
	printf("0x43 reads: %x\n", inb(0x43));
	
	// Read initial time value
	initial_t = inb(0x42);
	initial_t |= (inb(0x42) << 4);

	// Sleep for a bit
	usleep(100000);

	// Read final time value
	final_t = inb(0x42);
	final_t |= (inb(0x42) << 4);

	// Print results
	printf("initial: %d\nfinal: %d\n", initial_t, final_t);
	return 0;
}

