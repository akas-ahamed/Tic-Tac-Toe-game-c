#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

#define MAX 10

char board[MAX][MAX];
int size;

// board initialize
int initBoard()
{
    int i, j;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            board[i][j] = ' ';
    return 0;
}

// Draw board
int drawBoard()
{
    int i, j, k;

    //column
    printf("     ");//row number
    for (j = 0; j < size; j++)
	    printf(" %d  ", j + 1);
    printf("\n");

    for (i = 0; i < size; i++)
    {

        printf("    ");
        for (k = 0; k < size; k++)
	       	printf("+---");
        printf("+\n");

        printf(" %2d ", i + 1);
        for (j = 0; j < size; j++)
	       	printf("| %c ", board[i][j]);
        printf("|\n");
    }


//bottom border
    printf("    ");
    for (k = 0; k < size; k++)
	    printf("+---");
    printf("+\n");

    return 0;
}


// Check 1 win, 2 draw, 0 continue
int checkWin()
{
    int i, j;
    char first;

    // Check rows
    for (i = 0; i < size; i++)
    {
        first = board[i][0];
        if (first == ' ')
	       	continue;
        int same = 1;
        for (j = 1; j < size; j++)
            if (board[i][j] != first)
		    same = 0;
        if (same)
	       	return 1;
    }

    // Check columns
    for (j = 0; j < size; j++)
    {
        first = board[0][j];
        if (first == ' ')
	       
		continue;

        int same = 1;
        for (i = 1; i < size; i++)
            if (board[i][j] != first) same = 0;
        if (same)
	       	return 1;
    }

    // Check main diagonal
    first = board[0][0];
    if (first != ' ')
    {
        int same = 1;
        for (i = 1; i < size; i++)
            if (board[i][i] != first)
		    same = 0;
        if (same)
	       	return 1;
    }

    //Anti diagonal checking
    first = board[0][size - 1];
    if (first != ' ')
    {
        int same = 1;
        for (i = 1; i < size; i++)
            if (board[i][size - 1 - i] != first)
		    same = 0;
        if (same)
	       	return 1;
    }
    //Draw check
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            if (board[i][j] == ' ')
		    return 0;
    return 2; //draw
}

// Player move with input validation
int playerMove(int player, char symbol)
{
    int row, col;
    while (1)
    {
        printf("Player %d (%c), enter move (row col): ", player, symbol);
        if (scanf("%d %d", &row, &col) != 2)
       	{
            printf("⚠ Invalid input! Please enter two numbers.\n");
            while (getchar() != '\n');
        
	    continue;

        }
        if (row < 1 || row > size || col < 1 || col > size)
       	{
            printf("⚠ Move out of range! Please enter values between 1 and %d.\n", size);
       
       	    continue;
        }

        if (board[row - 1][col - 1] != ' ')
       	{
            printf("⚠ Cell already occupied! Try a different cell.\n");
            continue;
        }
        board[row - 1][col - 1] = symbol;

        break;
    }
    return 0;
}

// Computer move (random empty cell)
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
            printf("Computer places %c at (%d, %d).\n", symbol, row + 1, col + 1);
            break;
        }
    }
    return 0;
}

// Two player mode
int twoPlayerMode()
{
    char symbols[2] = {'X', 'O'};
    int turn = 0;

    initBoard();

    while (1)
    {
        drawBoard();
        playerMove(turn + 1, symbols[turn]);
        int status = checkWin();
        if (status == 1)
       	{
            drawBoard();
            printf("🎉 Player %d (%c) wins!\n", turn + 1, symbols[turn]);
            break;
        }
       	else if (status == 2)
       	{
            drawBoard();
            printf("🤝 It's a draw!\n");
            break;
        }
        turn = 1 - turn;
    }
    return 0;
}

// Play vs computer mode
int playVsComputer()
{
    char symbols[2] = {'X', 'O'};
    int turn = 0;

    initBoard();

    while (1)
    {
        drawBoard();
        if (turn == 0)
       	{
            playerMove(1, symbols[0]);
        }
       	else
       	{
            printf("Computer's turn...\n");
            sleep(1);
            computerMove(symbols[1]);
        }
        int status = checkWin();
        if (status == 1)
       	{
            drawBoard();
            if (turn == 0) printf("🎉 Player 1 wins!\n");
            else printf("🤖 Computer wins!\n");
            break;
        }
       	else if (status == 2)
       	{
            drawBoard();
            printf("🤝 It's a draw!\n");
            break;
        }
        turn = 1 - turn;
    }
    return 0;
}

// Three player mode with role selection human/computer
int threePlayerMode()
{

    char symbols[3] = {'X', 'O', 'Z'};
    int isHuman[3];
    int turn = 0;
    int choice;
    printf("Select Player types:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("Player %d (1=Human, 2=Computer): ", i + 1);
        scanf("%d", &choice);
        if (choice == 1) isHuman[i] = 1;
        else isHuman[i] = 0;
    }
    initBoard();
    while (1)
    {
        drawBoard();
        if (isHuman[turn]) playerMove(turn + 1, symbols[turn]);
        else
       	{
            printf("Computer Player %d's turn...\n", turn + 1);
            sleep(1);
            computerMove(symbols[turn]);
        }
        int status = checkWin();
        if (status == 1)
       	{
            drawBoard();
            printf("🎉 Player %d (%c) wins!\n", turn + 1, symbols[turn]);
            break;
        }
       	else if (status == 2)
       	{
            drawBoard();
            printf("🤝 It's a draw!\n");
            break;
        }
        turn = (turn + 1) % 3;
    }
    return 0;
}

// Multiplayer mode (1-10 players)
int multiplayerGame(int players)
{
    if (players < 1) players = 1;
    if (players > 10) players = 10;

    char symbols[10] = {'X', 'O', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    int turn = 0;

    initBoard();

    while (1)
    {
        drawBoard();
        playerMove(turn + 1, symbols[turn]);
        int status = checkWin();
        if (status == 1)
       	{
            drawBoard();
            printf("🎉 Player %d (%c) wins!\n", turn + 1, symbols[turn]);
            break;
        }
       	else if (status == 2)
       	{
            drawBoard();
            printf("🤝 It's a draw!\n");
            break;
        }
        turn = (turn + 1) % players;
    }
    return 0;
}

// Main function
int main()
{
    int choice, players;

    srand(time(NULL));

    printf("   ==== TIC TAC TOE ====\n");
    printf("*** WELCOME TO THE GAME ***\n");
    printf("Enter board size (3-10): ");
    scanf("%d", &size);

    if (size < 3) size = 3;
    if (size > 10) size = 10;

    printf("\nChoose Game Mode:\n\n");
    printf("1. Two Player(Human vs Human)\n");
    printf("2. Two Player(Human vs Computer)\n");
    printf("3. Three Player (choose roles)\n");
    printf("4. Multi Player(Human) (1-10 players)\n");
    printf("\nEnter choice: ");

    scanf("%d", &choice);

    if (choice == 1)
   
    {
        twoPlayerMode();
    }
    else if (choice == 2)
    {
        playVsComputer();
    }
    else if (choice == 3)
    {
        threePlayerMode();
    }
    else if (choice == 4)
    {
        printf("Enter number of players (1-10): ");
        scanf("%d", &players);
        if (players < 1) players = 1;
        if (players > 10) players = 10;
        multiplayerGame(players);
    }
    else
    {
        printf("Invalid choice.\n");
    }

    return 0;
}
