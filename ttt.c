#include <stdio.h>


struct wins {
        char x;         // '1' if x won, '0' otherwise
        char o;         // '1' if o won, '0' otherwise
};


int printgame(char *gamelist);
int win_check(struct wins *res, char brd[]);

int main()
{
	int piece = 0;
	char board[] = "123456789";
	struct wins notlose;
	int i = 0;
	while(1){
		printgame(board);
		printf("Player one: Choose where you want to place your tile (x)\n");
		printf("Type in an integer between 1 and 9:");
		scanf("%d",&piece);
		board[piece - 1] = 'x';
		win_check(&notlose, board);
		if(notlose.x == 1){
			printgame(board);
			printf("Player 1 Wins!\n");
			return 0;
		}
		if(i == 4)
			printf("Tie!");
			return 0;
		printgame(board);
		printf("Player two: Choose where you want to place your tile (o)\n");
		printf("Type in an integer between 1 and 9:");
		scanf("%d",&piece);
		board[piece - 1] = 'o';
		win_check(&notlose, board);
		if(notlose.o == 1){
			printgame(board);
			printf("Player 2 Wins!\n");
			return 0;
		}
		i++;
	}
	return 0;
}

int printgame( char *gamelist)
{
	printf("%c | %c | %c\n",gamelist[0], gamelist[1], gamelist[2]);
	printf("---------\n");
	printf("%c | %c | %c\n",gamelist[3], gamelist[4], gamelist[5]);
	printf("---------\n");
	printf("%c | %c | %c\n\n",gamelist[6], gamelist[7], gamelist[8]);
	return 0;
}

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
