/* Matthew Blanchard & Christian Auspland
 * ECE 477
 * 2/10/2017
 * ttt.c
 * Description: Play tic-tac-toe against a simple AI. The player gets 'X' and always goes firts.
 *      The AI follows the following priority scheme:
 *      1.) Win          (Complete line of 3
 *      2.) Prevent Loss (Block player line of 2)
 *      3.) Line-up      (Play in line with one 'o' and no 'x')
 *      4.) Default      (Play in an empty line)
 */

#include <stdio.h>

// Error Codes
#define ERR_NOPLAY 1 << 0

// Structs
struct wins {
        char x;         // '1' if x won, '0' otherwise
        char o;         // '1' if o won, '0' otherwise
};


int printgame(char *gamelist);			// Prints board on the command line
int win_check(struct wins *res, char brd[]);	// Checks for a winning game
int error(int input, char *gamelist);		// Basic error checking
int comp_pick(char *brd);                       // Play computer's turn

int main() {
	int piece = 0;				// Player specified location
	char board[] = "123456789";		// Starting board to help players 
	struct wins notlose;			
	int j = 0;				// Keeps track of number of moves for a tie
	int success = 1;			// Error variable
	while(1) {		
		success = 1;			// Reset error
		while(success){			// While there is an error, ask the player to choose
			printgame(board);
			printf("Choose where you want to place your tile (x)\n");
			printf("Type in a whole number between 1 and 9:");
			scanf("%d",&piece);	
			success = error(piece, board);	// Checks for errors, returns 1 if error
		}
		board[piece - 1] = 'x';		// Replaces specified locatino with an 'x' char
		win_check(&notlose, board);	// Checks for win
		if(notlose.x == 1){		// If x wins, end the game
			printgame(board);
			printf("You win!\n");
			return 0;
		}
		if(j == 4){			// If the previous turn was the 9th, end the game
			printf("Tie!\n");
			return 0;
		}

		if (comp_pick(board)) {		// Comp chooses
                        printf("Error: computer failed to pick\n");
                        return 1;
                }
		win_check(&notlose, board);
		if(notlose.o == 1){		// If o wins, end the game
			printgame(board);
			printf("You lose\n");
			return 0;
		}
		j++;				// Iterate for a tie
	}
	return 0;
}
// Printgame simply prints the board along with the current board values
int printgame( char *gamelist)
{
	printf("%c | %c | %c\n",gamelist[0], gamelist[1], gamelist[2]);
	printf("---------\n");
	printf("%c | %c | %c\n",gamelist[3], gamelist[4], gamelist[5]);
	printf("---------\n");
	printf("%c | %c | %c\n\n",gamelist[6], gamelist[7], gamelist[8]);
	return 0;
}
// Checks for win conditions
int win_check(struct wins *res, char brd[]) {

        // Possible wins (r1, r2, r3, c1, c2, c3, diag l->r, diag r->l)
        char sets[8] = {'_', '_', '_', // Each character is either 'x', 'o',
                        '_', '_', '_', // or '_', corresponding to which won
                        '_', '_'};     // that set of 4 ('_' for no match).

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

        int i = 0;
        for (i = 0; i < 8; i++) {
                if (sets[i] == 'x')
                        res->x = 1;
                else if (sets[i] == 'o')
                        res->o = 1;
        }

        return 0;
}

// Error checks that the input is within the correct region
// and that the specified location hasn't already been chosen.
int error(int input, char *gamelist) {
	if(input < 1 || input > 9){	//if outside of 1-9, alert the player
		printf("INVALID INPUT\n");
		return 1;
	}
	//if the specified location already has an x or o, then alert the player
	else if((gamelist[input - 1] == 'x') || (gamelist[input - 1] == 'o')) {
		printf("Space already taken, pick another space\n");
		return 1;
	}
	else{	
		return 0;
	}
}

int comp_pick(char *brd) {
        
        int i = 0;      // Counter
        int j = 0;      // Counter
        int x_cnt = 0;  // # of x's in win condition
        int o_cnt = 0;  // # of o's in win condition

        // Possible win combos 
        char win[8][5] = {
        {brd[0], brd[1], brd[2], 0, 0},       // Row 1
        {brd[3], brd[4], brd[5], 0, 0},       // Row 2
        {brd[6], brd[7], brd[8], 0, 0},       // Row 3
        {brd[0], brd[3], brd[6], 0, 0},       // Col 1
        {brd[1], brd[4], brd[7], 0, 0},       // Col 2
        {brd[2], brd[5], brd[8], 0, 0},       // Col 3
        {brd[0], brd[4], brd[8], 0, 0},       // L->R Diagonal
        {brd[2], brd[4], brd[6], 0, 0}};      // R->L Diagonal
        /* ^ Piece in place ^    ^  ^  */
        /*         Dominant piece|  |  */           
        /*              # Dom pieces|  */

        // Win combo indices
        int win_i[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}};

        // Fill out remainder of win table
        for (i = 0; i < 8; i++) {
                x_cnt = 0;     // Reset counts
                o_cnt = 0;
                for (j = 0; j < 3; j++) {
                        if (win[i][j] == 'x') {
                                x_cnt++;
                        } else if (win[i][j] == 'o') {
                                o_cnt++;   
                        }                     
                }
                if (x_cnt != 0 && o_cnt == 0) {          // X dominant
                        win[i][3] = 'x';
                        win[i][4] = x_cnt;       
                } else if (x_cnt == 0 && o_cnt != 0) {   // O dominant
                        win[i][3] = 'o';
                        win[i][4] = o_cnt;
                }
        }

        // 1st Priority: Win the game (fill out final index of 'o' dominant win conditions)
        for (i = 0; i < 8; i++) {
                if (win[i][3] == 'o' && win[i][4] == 2){
                        for (j = 0; j < 3; j++) {
                                if (win[i][j] != 'x' && win[i][j] != 'o') {
                                        brd[win_i[i][j]] = 'o';
                                        return 0;
                                }
                        }
                }
        }

        // 2nd Priority: Block an opposing win condition about to be completed (2 x's)
        for (i = 0; i < 8; i++) {
                if (win[i][3] == 'x' && win[i][4] == 2){
                        for (j = 0; j < 3; j++) {
                                if (win[i][j] != 'x' && win[i][j] != 'o') {
                                        brd[win_i[i][j]] = 'o';
                                        return 0;
                                }
                        }
                }
        }

        // 3rd Priority: Pick partially filled win condition
        for (i = 0; i < 8; i++) {
                if (win[i][3] == 'o' && win[i][4] == 1){
                        for (j = 0; j < 3; j++) {
                                if (win[i][j] != 'x' && win[i][j] != 'o') {
                                        brd[win_i[i][j]] = 'o';
                                        return 0;
                                }
                        }
                }
        }

        // 4th Priority: Pick first empty win condition
        for (i = 0; i < 8; i++) {
                if (win[i][3] == 0){
                        for (j = 0; j < 3; j++) {
                                if (win[i][j] != 'x' && win[i][j] != 'o') {
                                        brd[win_i[i][j]] = 'o';
                                        return 0;
                                }
                        }
                }
        }

        return ERR_NOPLAY;
}
