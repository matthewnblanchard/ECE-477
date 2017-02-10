
#include <stdio.h>

#define ERR_ARGC 1 << 0

struct endgame {
	int dif;
	int spaces;
};

int convert(int game, char *gamelist);
int turns(char *gamelist, struct endgame *egame);

int main(int argc, char *argv[])

        // Argument checking
        if (argc > 2) {
                printf("Error: too many arguments");
                
	}
	return 0;
}

int convert(int game, char *gamelist){

	if( game > 19684)		//tests if game number is within the maximum (3^9)
		return 1;		//returns 1 if game number is too large

	char i;				//counter
	char k;
	int digit;			//temporary value that has the current digit
	int dfactor;			
	int pos = 8;
	for( i = 0; i < 9; i++){	//calculates the value of each digit
		digit = 0;
		dfactor = 1;
		for( k = 0; k < i; k++){
			dfactor = dfactor * 3;
		}
		digit = game / dfactor;//eliminate vdalues below 
		digit = digit % 3;		//eliminate values above specified digit
		gamelist[pos] = digit;	//store
		pos--;
	}
	return 0;	
}			

int turns(char *gamelist, struct endgame *egame){

	int x = 0;				//number of x's
	int o = 0;				//number of o's
	int i;				//counter
	int space = 0;
	int diff;			//difference between number of x's and o's
	for( i = 0; i < 9; i++){
		if( gamelist[i] == 1) 
			x += 1;
		else if(gamelist[i] == 2)
			o += 1;
		else if(gamelist[i] == 0)
			space += 1;
			
	}
	diff = x - o;
	egame->dif = diff;
	egame->spaces = space;
	printf("difference: %d spaces: %d\n",egame->dif, egame->spaces);
	return 0;	
}
