
#include <stdio.h>
#include <math.h>

#define ERR_ARGC 1 << 0

int convert(int game, char *gamelist);

int main(int argc, char *argv[]) {
	
	unsigned int tri = 0;
	char trilist[9];
        // Argument checking
        if (argc > 2) {
                printf("Error: too many arguments");
                return ERR_ARGC;
        }

        return 0;
}

int convert(int game, char *gamelist){

	if( game > 19683)		//tests if game number is within the maximum (3^9)
		return 1;		//returns 1 if game number is too large

	char i;				//counter
	char digit;			//temporary value that has the current digit
	for( i = 0; i < 9; i++){	//calculates the value of each digit
		digit - 0;
		digit = game / (pow(3,(i + 1));//eliminate values below specified digit
		digit = digit % 3;		//eliminate values above specified digit
		gamelist[i] = digit;	//store digit
	}
	return 0;	
}			
