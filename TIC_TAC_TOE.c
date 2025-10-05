#include<stdio.h>   //standard i/o
#include<unistd.h>  //sleep-POSIX
#include<stdlib.h>  //std-random num & genrl utiliy
#include<time.h>    //time function to initialize random seed

#define MAX 10      //maximum board & player

char board[MAX][MAX];//represent board(2D)
int size;            //hold board size 

// Clear the game log at the start of a new game
int clearLogFile()
{
    FILE *fp = fopen("game_log.txt", "w");   // Open for write, clears file
    if (fp == NULL) return -1;
    fprintf(fp, "=== Tic Tac Toe Game Log ===\n");
    fclose(fp);
    return 0;
}

// Log a move to the file
int logMove(int player, int row, int col)
{
    FILE *fp = fopen("game_log.txt", "a");   // Open for append
    if (fp == NULL) return -1;
    fprintf(fp, "Player %d move: (%d, %d)\n", player, row + 1, col + 1); // 1-based coords
    fclose(fp);
    return 0;
}

                                                    // 2D char array matches grid layout and allows EC access to rows, columns,& diagonal
// board initialize
int initBoard()
{
    int i, j;                            
    for (i = 0; i < size; i++)            // row loop
        for (j = 0; j < size; j++)        //column loop
            board[i][j] = ' ';            //set empty cell
    return 0;                             
}

// Draw board
int drawBoard()
{
    int i, j, k;

    //column
    printf("     ");                      //row number
    for (j = 0; j < size; j++)            //print column NO
	    printf(" %d  ", j + 1);
    printf("\n");

    for (i = 0; i < size; i++)            //each row   
    {

        printf("    ");
        for (k = 0; k < size; k++)        //horizon line border
	       	printf("+---");
        printf("+\n");

        printf(" %2d ", i + 1);           //row NO
        for (j = 0; j < size; j++)        //vertical bar value
	       	printf("| %c ", board[i][j]);
        printf("|\n");
    }


//bottom border
    printf("    ");
    for (k = 0; k < size; k++)            //bottom border line
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
        first = board[i][0];              //Get 1st symbol in row
        if (first == ' ')                 //skip empty strt
	       	continue;
        int same = 1;
        for (j = 1; j < size; j++)        //rest of the row check
            if (board[i][j] != first)
		    same = 0;             //all same,declare WIN
        if (same)
	       	return 1;
    }

    // Check columns
    for (j = 0; j < size; j++)
    {
        first = board[0][j];
        if (first == ' ')
	       
		continue;                 //skipp if empty

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
		    return 0;             //still spacce available
    return 2;                             //draw (No space & No winner) 
}

// Player move with input validation
int playerMove(int player, char symbol)
{
    int row, col;
    while (1)
    {
        printf("Player %d (%c), enter move (row col): ", player, symbol);
        if (scanf("%d %d", &row, &col) != 2)                  //Read 2 integer
       	{
            printf("⚠ Invalid input! Please enter two numbers.\n");
            while (getchar() != '\n');                        //clear buffer
        
	    continue;                                         //repeat prompt

        }
        if (row < 1 || row > size || col < 1 || col > size)   //bound check
       	{
            printf("⚠ Move out of range! Please enter values between 1 and %d.\n", size);
       
       	    continue;
        }

        if (board[row - 1][col - 1] != ' ')                   //check if cell is freee
       	{
            printf("⚠ Cell already occupied! Try a different cell.\n");
            continue;
        }
        board[row - 1][col - 1] = symbol ;             	      //set playe symbol
        
	logMove(player, row -1, col -1);                     // Log move

        break;                                                //exit input loop
    }
    return 0;
}

// Computer move (random empty cell)
int computerMove(char symbol)
{
    int row, col;
    while (1)
    {
        row = rand() % size;                                  //genarate randow row
        col = rand() % size;                                  //genarate random col
							      
        if (board[row][col] == ' ')                           //check if empty
       	{
            board[row][col] = symbol;                         //pllace symbol
            printf("Computer places %c at (%d, %d).\n", symbol, row + 1, col + 1);

	    logMove(0, row, col);                             // Use 0 for computer player
            break;                                            //move done
        }
    }
    return 0;
}

// Two player mode
int twoPlayerMode()
{
    clearLogFile();
    char symbols[2] = {'X', 'O'};
    int turn = 0;                                             //start with plyer 1

    initBoard();                                              //board init

    while (1)
    {
        drawBoard();
        playerMove(turn + 1, symbols[turn]);                  //player move
        int status = checkWin();                              //check for game status
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
        turn = 1 - turn;                                      //switchh player
    }
    return 0;
}

// Human vs computer mode
int playVsComputer()
{
    clearLogFile();
    char symbols[2] = {'X', 'O'};
    int turn = 0;

    initBoard();

    while (1)
    {
        drawBoard();
        if (turn == 0)
       	{
            playerMove(1, symbols[0]);                        //human mmove
        }
       	else
       	{
            printf("Computer's turn...\n");
            sleep(1);                                         //pausefor realize
            computerMove(symbols[1]);                         //commputer move
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
        turn = 1 - turn;                                      //alternate turn
    }
    return 0;
}

// Three player mode with role selection human/computer
int threePlayerMode()
{
    clearLogFile();

    char symbols[3] = {'X', 'O', 'Z'};
    int isHuman[3];                                           //track wich player human
    int turn = 0;
    int choice;
    printf("Select Player types:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("Player %d (1=Human, 2=Computer): ", i + 1);
        scanf("%d", &choice);
        if (choice == 1) isHuman[i] = 1;
        else isHuman[i] = 0;                                  //1 human ,else pc
    }
    initBoard();
    while (1)
    {
        drawBoard();
        if (isHuman[turn]) playerMove(turn + 1, symbols[turn]);         //human move
        else
       	{
            printf("Computer Player %d's turn...\n", turn + 1);
            sleep(1);
            computerMove(symbols[turn]);                                //pc move
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
            printf("🤝 It's a draw!\n");                      //U1F91D
            break;
        }
        turn = (turn + 1) % 3;                                //next move
    }
    return 0;
}

// Multiplayer mode (1-10 players)
int multiplayerGame(int players)
{
    clearLogFile();
    if (players < 1) players = 1;
    if (players > 10) players = 10;                           //bountry check

    char symbols[10] = {'X', 'O', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    int turn = 0;

    initBoard();

    while (1)
    {
        drawBoard();
        playerMove(turn + 1, symbols[turn]);                  //current player move
							      //
        int status = checkWin();                              //check WIN or DRAW
        if (status == 1)
       	{
            drawBoard();
            printf("🎉 Player %d (%c) wins!\n", turn + 1, symbols[turn]);
            break;                                            //U0001F389
        }
       	else if (status == 2)
       	{
            drawBoard();
            printf("🤝 It's a DRAWWW!!!\n");                  //U1F91D
            break;
        }
        turn = (turn + 1) % players;                          //next player
    }
    return 0;
}

// Main function
int main()
{
    int choice, players;

    srand(time(NULL));                                        //seed random NO genarate

    printf("   ==== TIC TAC TOE ====\n");
    printf("*** WELCOME TO THE GAME ***\n");
    printf("Enter board size (3-10): ");
    scanf("%d", &size);

    if (size < 3) size = 3;                                   //MIN board size
    if (size > 10) size = 10;                                 //MAX board size

    printf("\nChoose Game Mode:\n\n");
    printf("1. Two Player(Human vs Human)\n");
    printf("2. Two Player(Human vs Computer)\n");
    printf("3. Three Player (choose roles)\n");
    printf("4. Multi Player(Human) (1-10 players)\n");
    printf("\nEnter choice: ");

    scanf("%d", &choice);

    if (choice == 1)                                          //2 human
   
    {
        twoPlayerMode();
    }
    else if (choice == 2)
    {
        playVsComputer();                                     //Human vs PC
    }
    else if (choice == 3)
    {
        threePlayerMode();                                    //3 player MIX mode
    }
    else if (choice == 4)
    {
        printf("Enter number of players (1-10): ");
        scanf("%d", &players);
        if (players < 1) players = 1;
        if (players > 10) players = 10;
        multiplayerGame(players);                             //multy player
    }
    else
    {
        printf("Invalid choice.\n");
    }

    return 0;
}
