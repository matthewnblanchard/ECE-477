#include <stdio.h>

int printgame(char *gamelist);

int main()
{
	int piece = 0;
	char board[] = "123456789";
	while(1){
		printgame(board);
		printf("Player one: Choose where you want to place your tile (x)\n");
		printf("Type in an integer between 1 and 9:");
		scanf("%d",&piece);
		board[piece - 1] = 'x';
		printgame(board);
		printf("Player two: Choose where you want to place your tile (o)\n");
		printf("Type in an integer between 1 and 9:");
		scanf("%d",&piece);
		board[piece - 1] = 'o';
	}
	return 0;
}

int printgame( char *gamelist)
{
	printf("%c | %c | %c\n",gamelist[0], gamelist[1], gamelist[2]);
	printf("---------\n");
	printf("%c | %c | %c\n",gamelist[3], gamelist[4], gamelist[5]);
	printf("---------\n");
	printf("%c | %c | %c\n",gamelist[6], gamelist[7], gamelist[8]);
	return 0;
}
