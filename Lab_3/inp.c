#include <stdio.h>
#include <sys/io.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{  int port, val;
    if(argc <2 ) { printf("Usage is %s port [print]  \n",argv[0]); return(-1); }
    if(sscanf(argv[1],"%i",&port )!=1) { printf("Invalid port \n"); return(-2); }
    if(ioperm(port,1,1)!=0) {perror("ioperm"); return(-4); }
    val=inb(port);
    if(argc>2) printf("Value is %x \n",val);
    return(val);
}
