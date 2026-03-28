#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

#define SIZE 4
#define MAX_MOVES 1000
#define SOLVER_LIMIT 50

int board[SIZE][SIZE];
int blankX, blankY;
int moves = 0;
char moveStack[MAX_MOVES];
int top = -1;

void pushMove(char m) {
    if (top < MAX_MOVES - 1) moveStack[++top] = m;
}

char popMove() {
    if (top >= 0) return moveStack[top--];
    return '\0';
}

void printBoard() {
    system("cls");
    printf("\n====================================================\n");
    printf("                 WELCOME TO 15 PUZZLE               \n");
    printf("            Made by Siddharth | © 2025              \n");
    printf("====================================================\n");
    printf("Moves Made: %d\n", moves);
    printf("----------------------------------------------------\n");

    for (int i = 0; i < SIZE; i++) {
        printf("  ");
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0)
                printf("  .   ");
            else
                printf(" %2d   ", board[i][j]);
        }
        printf("\n\n");
    }

    printf("----------------------------------------------------\n");
    printf("W/A/S/D or Arrow Keys to move\n");
    printf("U to Undo | Q to Quit\n");
    if (moves >= SOLVER_LIMIT) printf("H to let the solver complete the puzzle\n");
    printf("----------------------------------------------------\n");
    printf("Your choice: ");
}

int isSolved() {
    int count = 1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == SIZE - 1 && j == SIZE - 1) return 1;
            if (board[i][j] != count) return 0;
            count++;
        }
    }
    return 1;
}

void shuffleBoard() {
    int temp[SIZE * SIZE];
    for (int i = 0; i < SIZE * SIZE; i++) temp[i] = i;

    srand(time(0));
    for (int i = SIZE * SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int t = temp[i];
        temp[i] = temp[j];
        temp[j] = t;
    }

    int k = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = temp[k];
            if (temp[k] == 0) {
                blankX = i;
                blankY = j;
            }
            k++;
        }
    }
}

void moveUp() {
    if (blankX < SIZE - 1) {
        board[blankX][blankY] = board[blankX + 1][blankY];
        board[blankX + 1][blankY] = 0;
        blankX++;
        moves++;
    }
}

void moveDown() {
    if (blankX > 0) {
        board[blankX][blankY] = board[blankX - 1][blankY];
        board[blankX - 1][blankY] = 0;
        blankX--;
        moves++;
    }
}

void moveLeft() {
    if (blankY < SIZE - 1) {
        board[blankX][blankY] = board[blankX][blankY + 1];
        board[blankX][blankY + 1] = 0;
        blankY++;
        moves++;
    }
}

void moveRight() {
    if (blankY > 0) {
        board[blankX][blankY] = board[blankX][blankY - 1];
        board[blankX][blankY - 1] = 0;
        blankY--;
        moves++;
    }
}

void undoMove() {
    char last = popMove();
    if (last == '\0') return;

    if (last == 'w') moveDown();
    else if (last == 's') moveUp();
    else if (last == 'a') moveRight();
    else if (last == 'd') moveLeft();
    moves--;
}

void autoSolver() {
    system("cls");
    printf("\n====================================================\n");
    printf("                 SOLVER ACTIVATED                   \n");
    printf("            Made by Siddharth | © 2025              \n");
    printf("====================================================\n");
    printf("Sit back and relax. Solving your board...\n\n");
    Sleep(800);

    int num = 1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            if (i == SIZE - 1 && j == SIZE - 1)
                board[i][j] = 0;
            else
                board[i][j] = num++;

            system("cls");
            printf("\n====================================================\n");
            printf("              SOLVER IS COMPLETING THE PUZZLE       \n");
            printf("            Made by Siddharth | © 2025              \n");
            printf("====================================================\n\n");

            for (int r = 0; r < SIZE; r++) {
                printf("  ");
                for (int c = 0; c < SIZE; c++) {
                    if (board[r][c] == 0)
                        printf("  .   ");
                    else
                        printf(" %2d   ", board[r][c]);
                }
                printf("\n\n");
            }

            Sleep(70);
        }
    }

    printf("\nPuzzle solved.\n");
    Sleep(1200);
}

int main() {
    system("cls");
    printf("\n====================================================\n");
    printf("                 WELCOME TO 15 PUZZLE               \n");
    printf("            Made by Siddharth | © 2025              \n");
    printf("====================================================\n");
    Sleep(1500);

    shuffleBoard();

    while (1) {
        printBoard();

        if (isSolved()) {
            printf("\n====================================================\n");
            printf("                 YOU COMPLETED THE PUZZLE           \n");
            printf("              Total Moves Taken: %d                 \n", moves);
            printf("            Made by Siddharth | © 2025              \n");
            printf("====================================================\n");
            break;
        }

        int ch = getch();

        if (ch == 224) {
            ch = getch();
            if (ch == 72) { moveUp(); pushMove('w'); }
            else if (ch == 80) { moveDown(); pushMove('s'); }
            else if (ch == 75) { moveLeft(); pushMove('a'); }
            else if (ch == 77) { moveRight(); pushMove('d'); }
        } else {
            ch = tolower(ch);
            if (ch == 'w') { moveUp(); pushMove('w'); }
            else if (ch == 's') { moveDown(); pushMove('s'); }
            else if (ch == 'a') { moveLeft(); pushMove('a'); }
            else if (ch == 'd') { moveRight(); pushMove('d'); }
            else if (ch == 'u') undoMove();
            else if (ch == 'h' && moves >= SOLVER_LIMIT) {
                autoSolver();
                break;
            }
            else if (ch == 'q') {
                printf("\n====================================================\n");
                printf("                     GAME CLOSED                    \n");
                printf("                You made %d moves                   \n", moves);
                printf("            Made by Siddharth | © 2025              \n");
                printf("====================================================\n");
                break;
            }
        }
    }

    return 0;
}
