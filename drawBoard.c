#include <stdio.h>

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
    printf("Enter board size (3-10): ");
    scanf("%d", &size);
    if (size < 3) size = 3;
    if (size > 10) size = 10;

    initBoard();
    drawBoard();

    return 0;
}

