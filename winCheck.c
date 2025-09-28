#include<stdio.h>
#include<unistd.h>

#define MAX 10
char board[MAX][MAX];
int size;


int initBoard()

{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            board[i][j] = ' ';
    return 0;
}


int drawBoard()
{
    printf("    ");
    for (int j = 0; j < size; j++) printf(" %d  ", j+1);
    printf("\n");

    for (int i = 0; i < size; i++)
    {
        printf("   ");
        for (int k = 0; k < size; k++) printf("+---");
        printf("+\n");

        printf(" %d ", i+1);
        for (int j = 0; j < size; j++) printf("| %c ", board[i][j]);
        printf("|\n");
    }

    printf("   ");
    for (int k = 0; k < size; k++) printf("+---");
    printf("+\n");

    return 0;
}


int checkWin()
{
    int i, j;

    
    for (i = 0; i < size; i++)
    {
        char first = board[i][0];
        if (first == ' ') continue;
        int same = 1;
        for (j = 1; j < size; j++)
       	{
            if (board[i][j] != first)
	    {
                same = 0;
                break;
            }
        }
        if (same) return 1; 
    }

    
    for (j = 0; j < size; j++)
    {
        char first = board[0][j];
        if (first == ' ') continue;
        int same = 1;
        for (i = 1; i < size; i++)
       	{
            if (board[i][j] != first)
	    {
                same = 0;
                break;
            }
        }
        if (same) return 1; 
    }

    
    char first = board[0][0];
    if (first != ' ')
    {
        int same = 1;
        for (i = 1; i < size; i++)
            if (board[i][i] != first) same = 0;
        if (same) return 1;
    }

    
    first = board[0][size-1];
    if (first != ' ') {
        int same = 1;
        for (i = 1; i < size; i++)
            if (board[i][size-1-i] != first) same = 0;
        if (same) return 1;
    }

    
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            if (board[i][j] == ' ') return 0; 

    return 2;
}

int main()
{
    int row, col, turn = 1;
    char symbols[2] = {'X','O'};

    printf("Enter board size (3-10): ");
    scanf("%d", &size);
    if (size < 3) size = 3;
    if (size > 10) size = 10;

    initBoard();

    while (1)
    {
        drawBoard();
        printf("Player %d (%c), enter move (row col): ", turn, symbols[turn-1]);
        if (scanf("%d %d", &row, &col) != 2)
       	{
            printf("⚠ Invalid input! Enter two numbers.\n");
            while(getchar() != '\n');
            sleep(2);
            continue;
        }

        if (row < 1 || row > size || col < 1 || col > size) {
            printf("⚠ Invalid move! Row/Col must be 1-%d.\n", size);
            sleep(2);
            continue;
        }

        if (board[row-1][col-1] != ' ') {
            printf("⚠ Cell already filled! Choose another.\n");
            sleep(2);
            continue;
        }

        board[row-1][col-1] = symbols[turn-1];

        int status = checkWin();
        if (status == 1) {
            drawBoard();
            printf("Player %d (%c) wins!\n", turn, symbols[turn-1]);
            break;
        } else if (status == 2) {
            drawBoard();
            printf("It's a draw!\n");
            break;
        }

        turn = (turn == 1) ? 2 : 1;
    }

    return 0;
}

