#include<stdio.h>
//diagnal check


if(board[0][0] == board[1][1] && board[1][1]== board[2][2])
{
    return 1;
}

if(board[2][0] == board[1][1] && board[1][1]== board[0][2])
{
    return 1;
}
