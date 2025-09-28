#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

#define MAX 10
char board[MAX][MAX];
int size;
int i,j,k;

int initBoard()
{
    for ( i=0;i<size;i++)
        for ( j=0;j<size;j++)
            board[i][j]=' ';
    return 0;
}

// boarddd
int drawBoard()

{
    printf("     ");
    for(j=0;j<size;j++)
	    printf(" %d  ",j+1);
    printf("\n");

    for( i=0;i<size;i++)
    {
        printf("    ");
        for( k=0;k<size;k++)
	       	printf("+---");
        printf("+\n");

        printf(" %2d ",i+1);
        for( j=0;j<size;j++)
	       	printf("| %c ",board[i][j]);
        printf("|\n");
    }

    printf("    ");
    for( k=0;k<size;k++) printf("+---");
    printf("+\n");
    return 0;
}

//win
int checkWin(int players)
{
    int i,j;
    for(i=0;i<size;i++)
    {
        char first=board[i][0];
        if(first==' ')
	       	continue;
        int same=1;
        for(j=1;j<size;j++)
	       	if(board[i][j]!=first) same=0;
        if(same)
	       	return 1;
    }
    for(j=0;j<size;j++)
    {
        char first=board[0][j];
        if(first==' ')
	       	continue;
        int same=1;
        for(i=1;i<size;i++)
	       	if(board[i][j]!=first) same=0;
        if(same) return 1;
    }
    char first=board[0][0];
    if(first!=' ')
    {
        int same=1;
        for(i=1;i<size;i++)
	       	if(board[i][i]!=first) same=0;
        if(same)
	       	return 1;
    }
    first=board[0][size-1];
    if(first!=' ')
    {
        int same=1;
        for(i=1;i<size;i++)
	       	if(board[i][size-1-i]!=first) same=0;
        if(same)
	       	return 1;
    }
    for(i=0;i<size;i++)
        for(j=0;j<size;j++)
            if(board[i][j]==' ')
		    return 0;
    return 2; 
}

// Multi
int multiplayerGame(int players)
{
    int turn=1,row,col;
    char symbols[10]={'X','O','A','B','C','D','E','F','G','H'};

    initBoard();

    while(1)
    {
        drawBoard();
        int current= (turn-1)%players;
        printf("Player %d (%c), enter move (row col): ",current+1,symbols[current]);
        if(scanf("%d %d",&row,&col)!=2)
	{
            printf("⚠ Invalid input! Enter two numbers.\n");
            while(getchar()!='\n');
            sleep(2);
            continue;
        }

        if(row<1||row>size||col<1||col>size)
	{ 
            printf("⚠ Invalid move! Row/Col must be 1-%d.\n", size);
            sleep(2);
            continue;
        }

        if(board[row-1][col-1]!=' ')
	{
	       	
            printf("⚠ Cell already filled! Choose another.\n");
            sleep(2);
            continue;
        }

        board[row-1][col-1]=symbols[current];

        int status=checkWin(players);
        if(status==1)
	{
            drawBoard();
            printf("Player %d (%c) wins!\n",current+1,symbols[current]);
            break;
        }
       	else if(status==2)
	{
            drawBoard();
            printf("It's a draw!\n");
            break;
        }

        turn++;
    }
    return 0;
}


int main() 
{
    srand(time(NULL));
    int choice, players;

    printf("Enter board size (3-10): ");
    scanf("%d",&size);
    if(size<3) size=3;
    if(size>10) size=10;

    printf("\nGame Modes:\n1. 2 Players\n2. Multiplayer (3–10 players)\nEnter choice: ");
    scanf("%d",&choice);

    if(choice==1) multiplayerGame(2);
    else if(choice==2)
    {
        printf("Enter number of players (3–10): ");
        scanf("%d",&players);
        if(players<3) players=3;
        if(players>10) players=10;
        multiplayerGame(players);
    }
    else printf("⚠ Invalid choice!\n");

    return 0;
}

