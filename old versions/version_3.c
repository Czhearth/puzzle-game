#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <string.h>

#define MAX 6

int board[MAX][MAX];
int N;
int blankX, blankY;
int moves = 0;
int moveLimit;
char difficulty[10];

void initSolvedBoard() {
    int num = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == N - 1 && j == N - 1)
                board[i][j] = 0;
            else
                board[i][j] = num++;
        }
    }
    blankX = N - 1;
    blankY = N - 1;
}

void randomMove() {
    int r = rand() % 4;

    if (r == 0 && blankX < N - 1) {
        board[blankX][blankY] = board[blankX + 1][blankY];
        board[++blankX][blankY] = 0;
    }
    else if (r == 1 && blankX > 0) {
        board[blankX][blankY] = board[blankX - 1][blankY];
        board[--blankX][blankY] = 0;
    }
    else if (r == 2 && blankY < N - 1) {
        board[blankX][blankY] = board[blankX][blankY + 1];
        board[blankX][++blankY] = 0;
    }
    else if (r == 3 && blankY > 0) {
        board[blankX][blankY] = board[blankX][blankY - 1];
        board[blankX][--blankY] = 0;
    }
}

void shuffleBoard() {
    srand(time(0));
    initSolvedBoard();
    for (int i = 0; i < N * N * 10; i++)
        randomMove();
}

int isSolved() {
    int count = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == N - 1 && j == N - 1)
                return 1;
            if (board[i][j] != count++)
                return 0;
        }
    }
    return 1;
}

void printBoard() {
    system("cls");
    printf("\n====================================================\n");
    printf("          %dx%d PUZZLE | %s | © 2025 Siddharth       \n", N, N, difficulty);
    printf("====================================================\n");
    printf("Moves: %d / %d\n", moves, moveLimit);
    printf("----------------------------------------------------\n");

    for (int i = 0; i < N; i++) {
        printf("  ");
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0)
                printf("  .  ");
            else
                printf(" %2d  ", board[i][j]);
        }
        printf("\n\n");
    }

    printf("----------------------------------------------------\n");
    printf("Controls: W/A/S/D or Arrow Keys\n");
    printf("Press Q to Quit\n");
    printf("----------------------------------------------------\n");
}

void autoSolve() {
    system("cls");
    printf("\n====================================================\n");
    printf("            AUTO SOLVER ACTIVATED                   \n");
    printf("              © 2025 Siddharth                      \n");
    printf("====================================================\n");
    Sleep(1200);

    initSolvedBoard();
    printBoard();
    printf("\nPuzzle solved automatically.\n");
    Sleep(1500);
}

void moveUp() {
    if (blankX < N - 1) {
        board[blankX][blankY] = board[blankX + 1][blankY];
        board[++blankX][blankY] = 0;
        moves++;
    }
}

void moveDown() {
    if (blankX > 0) {
        board[blankX][blankY] = board[blankX - 1][blankY];
        board[--blankX][blankY] = 0;
        moves++;
    }
}

void moveLeft() {
    if (blankY < N - 1) {
        board[blankX][blankY] = board[blankX][blankY + 1];
        board[blankX][++blankY] = 0;
        moves++;
    }
}

void moveRight() {
    if (blankY > 0) {
        board[blankX][blankY] = board[blankX][blankY - 1];
        board[blankX][--blankY] = 0;
        moves++;
    }
}

int main() {
    int choice;

    system("cls");
    printf("\n====================================================\n");
    printf("                 PUZZLE GAME                        \n");
    printf("               © 2025 Siddharth                     \n");
    printf("====================================================\n\n");
    printf("Select Difficulty:\n");
    printf("1. Easy   (3x3)\n");
    printf("2. Medium (5x5)\n");
    printf("3. Hard   (6x6)\n");
    printf("\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        N = 3;
        moveLimit = 150;
        strcpy(difficulty, "Easy");
    }
    else if (choice == 2) {
        N = 5;
        moveLimit = 300;
        strcpy(difficulty, "Medium");
    }
    else {
        N = 6;
        moveLimit = 500;
        strcpy(difficulty, "Hard");
    }

    shuffleBoard();

    while (1) {
        printBoard();

        if (isSolved()) {
            printf("\nYOU SOLVED IT IN %d MOVES!\n", moves);
            Sleep(1500);
            break;
        }

        if (moves >= moveLimit) {
            autoSolve();
            break;
        }

        int ch = getch();

        if (ch == 224) {
            ch = getch();
            if (ch == 72) moveUp();
            else if (ch == 80) moveDown();
            else if (ch == 75) moveLeft();
            else if (ch == 77) moveRight();
        }
        else {
            ch = tolower(ch);
            if (ch == 'w') moveUp();
            else if (ch == 's') moveDown();
            else if (ch == 'a') moveLeft();
            else if (ch == 'd') moveRight();
            else if (ch == 'q') break;
        }
    }

    return 0;
}
