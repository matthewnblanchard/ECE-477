#include <stdio.h>
#include <sys/io.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{  int port, val;
    if(argc <3 ) { printf("Usage is %s port value \n",argv[0]); return(-1); }
    if(sscanf(argv[1],"%i",&port )!=1) { printf("Invalid port \n"); return(-2); }
    if(sscanf(argv[2],"%i",&val)!=1) { printf("Invalid value \n"); return(-3); }
    if(ioperm(port,1,1)!=0) {perror("ioperm"); return(-4); }
    outb(val,port); return(0);
}
