#include<stdio.h>

// checck for draw
int count = 0;
for(int i=0; i<3; i++)
{
    for(int j=0; j<3; j++)
    {
      if(board[1][j] != 'X' && board[i][j] != '0')
      {
          count++;
      }
    }
}

if(count ==0)
{
    return 2;
   //draw
}

return 0;
