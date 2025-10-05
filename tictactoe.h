#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#define MAX_SIZE 10
#define MAX_PLAYERS 10

extern char board[MAX_SIZE][MAX_SIZE];
extern int size;

void initBoard();
int drawBoard();
int checkWin(int players);
int multiplayerGame(int players);

#endif // TIC_TAC_TOE_H

