#include<stdio.h>

#define MAX 10
char board[MAX][MAX];

int size;

int initBoard()

{
    int i, j;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            board[i][j] = ' ';
    return 0;
}

int drawBoard()
{
    int i, j, k;
    printf("    ");
    for (j = 0; j < size; j++) printf(" %d  ", j+1);
    printf("\n");

    for (i = 0; i < size; i++)
    {
        printf("   ");
        for (k = 0; k < size; k++) printf("+---");
        printf("+\n");

        printf(" %d ", i+1);
        for (j = 0; j < size; j++) printf("| %c ", board[i][j]);
        printf("|\n");
    }

    printf("   ");
    for (k = 0; k < size; k++) printf("+---");
    printf("+\n");

    return 0;
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

    int moves;
    for (moves = 0; moves < size*size; moves++)
    {
        drawBoard();
        printf("Player %d (%c), enter move (row col): ", turn, symbols[turn-1]);
        scanf("%d %d", &row, &col);

        if (row < 1 || row > size || col < 1 || col > size || board[row-1][col-1] != ' ')
       	{
            printf("Invalid move! Try again.\n");
            moves--; 
            continue;
        }

        board[row-1][col-1] = symbols[turn-1];
        turn = (turn == 1) ? 2 : 1;
    }

    drawBoard();
    printf("Board full. Game over.\n");

    return 0;
}

