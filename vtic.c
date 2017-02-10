#include <stdio.h>

// Error codes
#define ERR_ARGC 1 << 0
#define ERR_FILE 1 << 1
#define ERR_BOUNDS 1 << 2
#define ERR_TRI 1 << 3
#define ERR_CNT 1 << 4
#define ERR_WIN 1 << 5

// Constants
#define TRI_LIM 3*3*3*3*3*3*3*3*3

// Structs
struct wins {
        char x;         // '1' if x won, '0' otherwise
        char o;         // '1' if o won, '0' otherwise
};

struct endgame {
	int dif;
	int spaces;
};

int win_check(struct wins *res, char brd[]);      // Checks for winning combos and saves winners to res
int convert(unsigned int game, char *gamelist);   // Converts trinary # to array of x's o's and spaces
int turns(char *gamelist, struct endgame *egame); // Compares # of x's o's and spaces

int main(int argc, char *argv[]) {

        FILE *out = stdout;     // Output stream. Default to stdout
        unsigned int tri = 0;   // Numeric board state (interpreted in trinary)
        char board[9];          // Board state
        unsigned int state = 0; // Game status (numeric)
        char * sstate;          // Game status (string)
        struct wins wn;         // Game winner(s)
        struct endgame end;     // Ending # of x's and o's
        int valid = 0;          // '1' of board is valid, '0' otherwise
        int i = 0;              // Counter

        // Argument checking
        if (argc > 2) {
                printf("Error: too many arguments");
                return ERR_ARGC;
        }
        
        // Attempt to open file if argument present
        if (argc == 2) {
                out = fopen(argv[1], "w");
                if (out == NULL) {
                        printf("Error: could not open file: %s\n", argv[1]);
                        return ERR_FILE;
                }
        }

        for (tri = 0; tri < TRI_LIM; tri++) {

                // Process trinary # to board state array
                if (convert(tri, board)) {
                        printf("Error: bad trinary conversion\n");
                        return ERR_TRI;
                }

                // Count # of x's and o'x, and determine precense of spaces
                if (turns(board, &end)) {
                        printf("Error: failed to count # of x's and o's\n");
                        return ERR_CNT;
                }

                // Check for winners
                if (win_check(&wn, board)) {
                        printf("Error: failed to determine winner\n");
                        return ERR_WIN;
                }

                // Determine validity
                if (end.dif > 1 || end.dif < 0) {       // Invalid: improper ratio of x's to o's
                        valid = 0;
                } else if (wn.x == 1 && wn.o == 1) {     // Invalid: two winners
                        valid = 0;
                } else if (wn.x == 1 && end.dif == 1) {  // Valid: X wins
                        valid = 1;
                        state = 2;
                        sstate = "X wins";
                } else if (wn.o == 1 && end.dif == 0) {  // Valid: O wins
                        valid = 1;
                        state = 3;
                        sstate = "O wins";
                } else if (wn.o == 0 && wn.x == 0 && end.spaces == 0) {    // Valid: stalemate
                        valid = 1;
                        state = 4;
                        sstate = "No winner";
                } else if (wn.o == 0 && wn.x == 0 && (end.spaces != 0)) {  // Valid: game incomplete
                        valid = 1;
                        state = 1;
                        sstate = "Game in Progress";
                } else {                                 // Everything else is invalid
                       valid = 0;
                }

                // Print if valid
                if (valid) {
                        for (i = 8; i >= 0; i--) {
                                fprintf(out, "%c,", board[i]);
                        }
                        fprintf(out, "%d,", state);
                        fprintf(out, "\"%s\"\n", sstate);
                } 
        }
        
        // Close file if open
        if (out != stdout)
              fclose(out);

        return 0;
};

int win_check(struct wins *res, char brd[]) {
        
        int i = 0;      // Counter

        // Possible wins (r1, r2, r3, c1, c2, c3, diag l->r, diag r->l)
        char sets[8] = {'_', '_', '_', // Each character is either 'x', 'o',
                        '_', '_', '_', // or '_', corresponding to which won
                        '_', '_'};     // that set of 3 ('_' for no match).

        // Reset results
        res->x = 0;
        res->o = 0;

        // Check each possible win line                 // Board indices:
        if (brd[0] == brd[1] && brd[0] == brd[2])       // 0 1 2
                sets[0] = brd[0];                       // 3 4 5
        if (brd[3] == brd[4] && brd[3] == brd[5])       // 6 7 8
                sets[1] = brd[3];
        if (brd[6] == brd[7] && brd[6] == brd[8])
                sets[2] = brd[6];
        if (brd[0] == brd[3] && brd[0] == brd[6])
                sets[3] = brd[0];
        if (brd[1] == brd[4] && brd[1] == brd[7])
                sets[4] = brd[1];
        if (brd[2] == brd[5] && brd[2] == brd[8])
                sets[5] = brd[2];
        if (brd[0] == brd[4] && brd[0] == brd[8])
                sets[6] = brd[0];
        if (brd[2] == brd[4] && brd[2] == brd[6])
                sets[7] = brd[2];

        // Determine winners
        for (i = 0; i < 8; i++) {
                if (sets[i] == 'x')
                        res->x = 1;
                else if (sets[i] == 'o')
                        res->o = 1;
        }

        return 0;
};

int convert(unsigned int game, char *gamelist) {

	if (game >= TRI_LIM)		// Tests if game number is within the maximum (3^9)
		return ERR_BOUNDS;	// Return with error if game number is too large

	int  i = 0;			// Counter
	int dfactor = 1;                // Division factor for trinary #			
	for( i = 0; i < 9; i++) {  	// Calculates the value of each digit
		gamelist[i] = (game / dfactor) % 3;
                dfactor *= 3;
                switch (gamelist[i]) {   // Convert to appropriate character
                case 0: 
                        gamelist[i] = ' ';
                        break;
                case 1:
                        gamelist[i] = 'x';
                        break;
                case 2:
                        gamelist[i] = 'o';
                        break;
                }
        }        
	return 0;	
};			

int turns(char *gamelist, struct endgame *egame) {

	int x = 0;			// Number of x's
	int o = 0;			// Number of o's
	int i = 0;			// Counter
	int space = 0;                  // # of empty spaces
	int diff = 0;			// Difference between number of x's and o's
	for (i = 0; i < 9; i++) {
		if (gamelist[i] == 'x') 
			x += 1;
		else if(gamelist[i] == 'o')
			o += 1;
		else if(gamelist[i] == ' ')
			space += 1;
			
	}
	diff = x - o;
	egame->dif = diff;
	egame->spaces = space;
	return 0;	
};
