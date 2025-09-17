#include<stdio.h>

int main()
{
    int row,column,move,gameStatus;
    int player =1;

    while(1)
    {
        system(cls);
        drawBoard();
        player =(player %2 )? 1: 2;
        printf("Player %d move: ",player);
        scanf("%d",&move);

        //define row column
        row = (move - 1)/3;
        column = (move - 1)%3;

        //checking valid input

        if(board[row][column] !='X'&& board[row][column] != 'O')
        {
            if(player == 1)
            {
                 board[row][column] = 'X';

            }
            else
            {
                board[row][column] = 'O';
            }

        }
        else
        {
             printf("This cell is already filled!!\n");
             player--;
        }

        drawBoard();

        game status = checkWin();

        if(gameStatus == 1)
        {
            printf("Player %d win",player);
            break;
        }
        if(gameStatus == 2)
        {
            printf("Draw");
            break;
        }
        player++;


    }
}
