#include<stdio.h>
#include<stdlib.h>


char board[3][3] =
{
    { '1', '2', '3' },
    { '4', '5', '6' },
    { '7', '8', '9' }

};

int drawBoard()
{
    system("cls");
    for (int i = 0; i < 3; i++)
    {
        printf(" %c  | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i != 2)
        {
            printf("---+---+---\n");
        }
    }
    return 0;
}


int checkWin()
{
    
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 1;
    }

   
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 1;
    }

    
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 1;

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 1;

    
    int filled = 1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 'X' && board[i][j] != 'O')
                filled = 0;
        }
    }
    if (filled)
        return 2; 

    return 0; 
}

int main()
{
    int player = 1, move, row, col, status;

    while (1)
    {
        drawBoard();
        printf("Player %d, enter your move (1-9): ", player);
        scanf("%d", &move);

        if (move < 1 || move > 9)
        {
            printf("Invalid move!!!!!! Try again.....\n");
            continue;
        }

        row = (move - 1) / 3;
        col = (move - 1) % 3;

        if (board[row][col] != 'X' && board[row][col] != 'O')
        {
            board[row][col] = (player == 1) ? 'X' : 'O';
        }
        else
        {
            printf("Cell already filled!!! Try again....\n");
            continue;
        }

        status = checkWin();
        if (status == 1)
        {
            drawBoard();
            printf("Player %d wins!!1!\n", player);
            break;
        }
        else if (status == 2)
        {
            drawBoard();
            printf("It's a draw!!!\n");
            break;
        }

        player = (player == 1) ? 2 : 1; 
    }

    return 0;
}
