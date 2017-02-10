
#include <stdio.h>

// Error codes
#define ERR_ARGC 1 << 0
#define ERR_FILE 1 << 1

// Constants
#define TRI_MAX = 3*3*3*3*3*3*3*3*3

// Structs
struct wins {
        char x;         // '1' if x won, '0' otherwise
        char o;         // '1' if o won, '0' otherwise
};

int win_check(struct wins *res, char brd[]);

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
                out = fopen(argv[1], "w+");
                if (out == NULL) {
                        printf("Error: could not open file: %s\n", argv[1]);
                        return ERR_FILE;
                }
        }

        for (tri = 0; tri < TRI_MAX; tri++) {

                // Process trinary # to board state array
                if (convert(tri, board)) {
                        printf("Error: bad trinary conversion\n");
                        return 1 << 2;
                }

                // Count # of x's and o'x, and determine precense of spaces
                if (turns(board, end)) {
                        printf("Error: failed to count # of x's and o's\n");
                        return 1 << 3;
                }

                // Check for winners
                if (win_check(&wn, board)) {
                        printf("Error: failed to determine winner\n");
                        return;
                }
                
                // Determine validity
                if (end.diff > 1 || end.diff < 0) {
                        valid = 0;
                } else if (wn.x == 1 && wn.o == 1) {
                        valid = 0;
                } else if (wn.x == 1 && end.diff == 1) {
                        valid = 1;
                        state = 2;
                        sstate = "X wins";
                } else if (wn.o == 1 && end.diff == 0) {
                        valid = 1;
                        state = 3;
                        sstate = "O wins";
                } else if (wn.o == 0 && wn.x == 0 && end.space == 0) {
                        valid = 1;
                        state = 4;
                        sstate = "No winner";
                } else if (wn.o == 0 && wn.x == 0 && (end.space != 0)) {
                        valid = 1;
                        state = 1;
                        sstate = "Game in Progress";
                } else {
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
        return 0;
};

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
};
