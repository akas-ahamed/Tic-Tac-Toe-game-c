
#include <stdio.h>

int size;  

int main()
{
    printf("Welcome to Tic Tac Toe!\n");
    printf("Choose board size (3-10): ");
    scanf("%d", &size);

    if (size < 3) size = 3;
    if (size > 10) size = 10;

    printf("Board size set to %d\n", size);

    return 0;
}
