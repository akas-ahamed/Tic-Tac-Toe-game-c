#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

#define MAX 10

char board[MAX][MAX];
int size;

// board
int initBoard()
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            board[i][j] = ' ';
   
    return 0;
}

// Draw board
int drawBoard()
{

    int i, j, k;

    // Column 
    printf("     "); //  row number
    for (j = 0; j < size; j++)
	    printf(" %d  ", j+1);
    printf("\n");

    for (i = 0; i < size; i++)
    {

        printf("    ");
        for (k = 0; k < size; k++)
	       	printf("+---");
        printf("+\n");


        printf(" %2d ", i+1);
        for (j = 0; j < size; j++)
	       	printf("| %c ", board[i][j]);
        printf("|\n");
    }

    // Bottom border
    printf("    ");
    for (k = 0; k < size; k++)
	    printf("+---");
    printf("+\n");

    return 0;
}

// Check win/draw
int checkWin(int players)
{
    int i, j;

    // Rows
    for (i = 0; i < size; i++)
    {
        char first = board[i][0];
        if (first == ' ')
	       	continue;
        int same = 1;
        for (j = 1; j < size; j++)
	       	if (board[i][j] != first) same = 0;
        if (same)
	       	return 1;
    }

    // Columns
    for (j = 0; j < size; j++)
    {
        char first = board[0][j];
        if (first == ' ')
	       	continue;
        int same = 1;
        for (i = 1; i < size; i++)
	       	if
		       	(board[i][j] != first) same = 0;
        if (same)
	       	return 1;
    }


    // Main diagonal
    char first = board[0][0];
    if (first != ' ')

    {
        int same = 1;
        for (i = 1; i < size; i++)
	       	if
		       	(board[i][i] != first) same = 0;
        if (same)
	       	return 1;
    }


    // Anti  diagonal
    first = board[0][size-1];
    if (first != ' ')
    {
        int same = 1;
        for (i = 1; i < size; i++)
	       	if
		       	(board[i][size-1-i] != first) same = 0;
        if (same)
	       	return 1;
    }


    // Draw check
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            if
		    (board[i][j] == ' ')
			    return 0;

    return 2; // draw
}




// Multiplayer game
int multiplayerGame(int players)
{
    int turn = 1, row, col;
    char symbols[10] = {'X','O','A','B','C','D','E','F','G','H'};

    initBoard();

    while (1)
   
    {
        drawBoard();
        int current = (turn - 1) % players;
        printf("Player %d (%c), enter move (row col): ", current+1, symbols[current]);

        if(scanf("%d %d", &row, &col) != 2)
	{
            printf("⚠  Invalid input! Enter two numbers.\n");
            while(getchar() != '\n');
            sleep(2);
            continue;
        }


        if (row < 1 || row > size || col < 1 || col > size)
       	{
            printf("⚠ Invalid move! Row/Col must be 1-%d.\n", size);
            sleep(2);
            continue;

        }


        if (board[row-1][col-1] != ' ')
       	{
            printf("⚠ Cell already filled! Choose another.\n");
            sleep(2);
            continue;

        }


        board[row-1][col-1] = symbols[current];

        int status = checkWin(players);
        if (status == 1)
       	{
            drawBoard();
            printf("🎉 Player %d (%c) wins!🎉\n", current+1, symbols[current]);//U0001F389
            break;
        }

       
	else if (status == 2)
       	{

            drawBoard();
            printf("🤝  It's a draw!\n");// u1F91D spce
            break;
        }

        turn++;
   }
    return 0;
}

// Computers move
int computerMove(char symbol)
{
    int row, col;
    while (1)
    {
        row = rand() % size;
        col = rand() % size;
        if (board[row][col] == ' ')
       	{
            board[row][col] = symbol;
            break;
       
       	}

    }

    return 0;
}

// Player vs computer
int playVsComputer()
{
    int turn=1,row,col;
    char symbols[2]={'X','O'};

    initBoard();

    while(1)
    {
        drawBoard();
        int current = turn-1;

        if(current==1)
	{
	       	// Computer turn

            printf("Computer's move...\n");
            sleep(1);
          
	    computerMove(symbols[current]);
        }
       	else
       	{
	       	// Human turn
            printf("Player 1 (%c), enter move (row col):\n ", symbols[0]);
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

            board[row-1][col-1] = symbols[current];
        }

        int status = checkWin(2);
        if(status==1)
	{
            drawBoard();
            if(current==1) printf("🤖  computer  wins!\n");
	    //cntrlv + u1F916+spce
            else printf("🧑  Player 1 wins!🎉\n");
	    //U1F9D1,0001F389
            break;

        }
       	else if(status==2)
	{
            drawBoard();
            printf("🤝  It's a draw!\n");
	    //u1F91D
            break;
        }

        turn = (turn==1)?2:1;
    }
    return 0;
}


//main
int main() 
{
    srand(time(NULL));

    int choice, players;

    printf("==== TIC TAC TOE ====\n");
    printf("Enter board size (3-10): ");
    scanf("%d", &size);
    if (size < 3) size = 3;
    if (size > 10) size = 10;

    printf("\nChoose Game Mode:\n");
    printf("1. Multiplayer\n");
    printf("2. Play vs Computer\n");
    printf("Enter choice:\n ");
    scanf("%d", &choice);

    if(choice==1)
    {
        printf("Enter number of players (2-%d): ", size);
        scanf("%d", &players);
        if(players < 2) players = 2;
        if(players > size) players = size;
        multiplayerGame(players);
    }
    else
    {
        playVsComputer();
    }

    return 0;
}

