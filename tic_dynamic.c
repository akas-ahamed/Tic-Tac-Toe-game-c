#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

char **board;  // Dynamic 2D array
int size;

// ---------- File Logging ----------
int clearLogFile() {
    FILE *fp = fopen("game_log.txt", "w");
    if (fp == NULL) return -1;
    fprintf(fp, "=== Tic Tac Toe Game Log ===\n");
    fclose(fp);
    return 0;
}

int logMove(int player, int row, int col) {
    FILE *fp = fopen("game_log.txt", "a");
    if (fp == NULL) return -1;
    fprintf(fp, "Player %d move: (%d, %d)\n", player, row + 1, col + 1);
    fclose(fp);
    return 0;
}

// ---------- Board Functions ----------
int initBoard() {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            board[i][j] = ' ';
    return 0;
}

int drawBoard() {
    printf("\n     ");
    for (int j = 0; j < size; j++) printf(" %d  ", j + 1);
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("    ");
        for (int k = 0; k < size; k++) printf("+---");
        printf("+\n");

        printf(" %2d ", i + 1);
        for (int j = 0; j < size; j++) printf("| %c ", board[i][j]);
        printf("|\n");
    }

    printf("    ");
    for (int k = 0; k < size; k++) printf("+---");
    printf("+\n");
    return 0;
}

int checkWin() {
    int i, j;
    char first;

    // Rows
    for (i = 0; i < size; i++) {
        first = board[i][0];
        if (first == ' ') continue;
        int same = 1;
        for (j = 1; j < size; j++)
            if (board[i][j] != first) same = 0;
        if (same) return 1;
    }

    // Columns
    for (j = 0; j < size; j++) {
        first = board[0][j];
        if (first == ' ') continue;
        int same = 1;
        for (i = 1; i < size; i++)
            if (board[i][j] != first) same = 0;
        if (same) return 1;
    }

    // Main diagonal
    first = board[0][0];
    if (first != ' ') {
        int same = 1;
        for (i = 1; i < size; i++)
            if (board[i][i] != first) same = 0;
        if (same) return 1;
    }

    // Anti-diagonal
    first = board[0][size - 1];
    if (first != ' ') {
        int same = 1;
        for (i = 1; i < size; i++)
            if (board[i][size - 1 - i] != first) same = 0;
        if (same) return 1;
    }

    // Draw check
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            if (board[i][j] == ' ') return 0;

    return 2;
}

// ---------- Move Functions ----------
int playerMove(int player, char symbol) {
    int row, col;
    while (1) {
        printf("Player %d (%c), enter move (row col): ", player, symbol);
        if (scanf("%d %d", &row, &col) != 2) {
            printf("⚠ Invalid input! Enter two numbers.\n");
            while (getchar() != '\n');
            continue;
        }
        if (row < 1 || row > size || col < 1 || col > size) {
            printf("⚠ Out of range! Enter values 1–%d.\n", size);
            continue;
        }
        if (board[row - 1][col - 1] != ' ') {
            printf("⚠ Cell already filled! Try another.\n");
            continue;
        }
        board[row - 1][col - 1] = symbol;
        logMove(player, row - 1, col - 1);
        break;
    }
    return 0;
}

int computerMove(char symbol) {
    int row, col;
    while (1) {
        row = rand() % size;
        col = rand() % size;
        if (board[row][col] == ' ') {
            board[row][col] = symbol;
            printf("Computer places %c at (%d, %d).\n", symbol, row + 1, col + 1);
            logMove(0, row, col);
            break;
        }
    }
    return 0;
}

// ---------- Game Modes ----------
int twoPlayerMode() {
    clearLogFile();
    char symbols[2] = {'X', 'O'};
    int turn = 0;
    initBoard();

    while (1) {
        drawBoard();
        playerMove(turn + 1, symbols[turn]);
        int status = checkWin();
        if (status == 1) {
            drawBoard();
            printf("🎉 Player %d (%c) wins!\n", turn + 1, symbols[turn]);
            break;
        } else if (status == 2) {
            drawBoard();
            printf("🤝 It's a draw!\n");
            break;
        }
        turn = 1 - turn;
    }
    return 0;
}

int playVsComputer() {
    clearLogFile();
    char symbols[2] = {'X', 'O'};
    int turn = 0;
    initBoard();

    while (1) {
        drawBoard();
        if (turn == 0)
            playerMove(1, symbols[0]);
        else {
            printf("Computer's turn...\n");
            sleep(1);
            computerMove(symbols[1]);
        }
        int status = checkWin();
        if (status == 1) {
            drawBoard();
            if (turn == 0) printf("🎉 Player 1 wins!\n");
            else printf("🤖 Computer wins!\n");
            break;
        } else if (status == 2) {
            drawBoard();
            printf("🤝 It's a draw!\n");
            break;
        }
        turn = 1 - turn;
    }
    return 0;
}

int threePlayerMode() {
    clearLogFile();
    char symbols[3] = {'X', 'O', 'Z'};
    int isHuman[3], turn = 0, choice;

    printf("Select Player Types:\n");
    for (int i = 0; i < 3; i++) {
        printf("Player %d (1=Human, 2=Computer): ", i + 1);
        scanf("%d", &choice);
        isHuman[i] = (choice == 1) ? 1 : 0;
    }

    initBoard();
    while (1) {
        drawBoard();
        if (isHuman[turn])
            playerMove(turn + 1, symbols[turn]);
        else {
            printf("Computer Player %d's turn...\n", turn + 1);
            sleep(1);
            computerMove(symbols[turn]);
        }
        int status = checkWin();
        if (status == 1) {
            drawBoard();
            printf("🎉 Player %d (%c) wins!\n", turn + 1, symbols[turn]);
            break;
        } else if (status == 2) {
            drawBoard();
            printf("🤝 It's a draw!\n");
            break;
        }
        turn = (turn + 1) % 3;
    }
    return 0;
}

int multiplayerGame(int players) {
    clearLogFile();
    if (players < 1) players = 1;
    if (players > 10) players = 10;

    char symbols[10] = {'X','O','A','B','C','D','E','F','G','H'};
    int turn = 0;
    initBoard();

    while (1) {
        drawBoard();
        playerMove(turn + 1, symbols[turn]);
        int status = checkWin();
        if (status == 1) {
            drawBoard();
            printf("🎉 Player %d (%c) wins!\n", turn + 1, symbols[turn]);
            break;
        } else if (status == 2) {
            drawBoard();
            printf("🤝 It's a draw!\n");
            break;
        }
        turn = (turn + 1) % players;
    }
    return 0;
}

// ---------- Main ----------
int main() {
    srand(time(NULL));
    int choice, players;

    printf("==== TIC TAC TOE ====\n");
    printf("Enter board size (3–10): ");
    scanf("%d", &size);
    if (size < 3) size = 3;
    if (size > 10) size = 10;

    // Allocate dynamic board
    board = (char **)malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++)
        board[i] = (char *)malloc(size * sizeof(char));

    printf("\nSelect Game Mode:\n");
    printf("1. Two Player (Human vs Human)\n");
    printf("2. Play vs Computer\n");
    printf("3. Three Player (Human/Computer)\n");
    printf("4. Multiplayer (1–10 Humans)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: twoPlayerMode(); break;
        case 2: playVsComputer(); break;
        case 3: threePlayerMode(); break;
        case 4:
            printf("Enter number of players (1–10): ");
            scanf("%d", &players);
            multiplayerGame(players);
            break;
        default:
            printf("Invalid choice.\n");
    }

    // Free allocated memory
    for (int i = 0; i < size; i++)
        free(board[i]);
    free(board);

    printf("\nGame session logged in 'game_log.txt'.\n");
    return 0;
}

