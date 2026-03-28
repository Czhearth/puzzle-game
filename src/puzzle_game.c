#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <string.h>

#define MAX_SIZE 6

int board[MAX_SIZE][MAX_SIZE];
int size;
int blankRow, blankCol;
int moveCount = 0;
int moveLimit = 0;
int shuffleSteps = 0;
char difficulty[20];

void clearScreen() {
    system("cls");
}

void pauseMs(int ms) {
    Sleep(ms);
}

void initializeSolvedBoard() {
    int value = 1;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == size - 1 && j == size - 1) {
                board[i][j] = 0;
            } else {
                board[i][j] = value++;
            }
        }
    }

    blankRow = size - 1;
    blankCol = size - 1;
}

void performRandomValidMove() {
    int direction = rand() % 4;

    if (direction == 0 && blankRow < size - 1) {
        board[blankRow][blankCol] = board[blankRow + 1][blankCol];
        board[++blankRow][blankCol] = 0;
    }
    else if (direction == 1 && blankRow > 0) {
        board[blankRow][blankCol] = board[blankRow - 1][blankCol];
        board[--blankRow][blankCol] = 0;
    }
    else if (direction == 2 && blankCol < size - 1) {
        board[blankRow][blankCol] = board[blankRow][blankCol + 1];
        board[blankRow][++blankCol] = 0;
    }
    else if (direction == 3 && blankCol > 0) {
        board[blankRow][blankCol] = board[blankRow][blankCol - 1];
        board[blankRow][--blankCol] = 0;
    }
}

void shuffleBoard() {
    srand(time(NULL));
    initializeSolvedBoard();

    shuffleSteps = size * size * 10;

    for (int i = 0; i < shuffleSteps; i++) {
        performRandomValidMove();
    }

    moveCount = 0;
}

int isPuzzleSolved() {
    int expected = 1;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == size - 1 && j == size - 1) {
                return 1;
            }

            if (board[i][j] != expected++) {
                return 0;
            }
        }
    }

    return 1;
}

void printHeader(const char *title) {
    printf("\n====================================================\n");
    printf("                 %s\n", title);
    printf("====================================================\n");
}

void displayBoard() {
    clearScreen();

    printHeader("SLIDING PUZZLE GAME");

    printf("Difficulty : %s\n", difficulty);
    printf("Board Size : %dx%d\n", size, size);
    printf("Moves Made : %d\n", moveCount);
    printf("Move Limit : %d\n", moveLimit);

    printf("----------------------------------------------------\n");

    for (int i = 0; i < size; i++) {
        printf("  ");
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) {
                printf("  .  ");
            } else {
                printf(" %2d  ", board[i][j]);
            }
        }
        printf("\n\n");
    }

    printf("----------------------------------------------------\n");
    printf("Controls:\n");
    printf("W / A / S / D or Arrow Keys -> Move tiles\n");
    printf("H -> Auto Solve\n");
    printf("Q -> Quit\n");
    printf("----------------------------------------------------\n");
}

void moveUp() {
    if (blankRow < size - 1) {
        board[blankRow][blankCol] = board[blankRow + 1][blankCol];
        board[++blankRow][blankCol] = 0;
        moveCount++;
    }
}

void moveDown() {
    if (blankRow > 0) {
        board[blankRow][blankCol] = board[blankRow - 1][blankCol];
        board[--blankRow][blankCol] = 0;
        moveCount++;
    }
}

void moveLeft() {
    if (blankCol < size - 1) {
        board[blankRow][blankCol] = board[blankRow][blankCol + 1];
        board[blankRow][++blankCol] = 0;
        moveCount++;
    }
}

void moveRight() {
    if (blankCol > 0) {
        board[blankRow][blankCol] = board[blankRow][blankCol - 1];
        board[blankRow][--blankCol] = 0;
        moveCount++;
    }
}

void runAutoSolver() {
    clearScreen();

    printHeader("AUTO SOLVER");

    printf("Solving puzzle for you...\n");
    pauseMs(1200);

    initializeSolvedBoard();

    displayBoard();

    printf("\nPuzzle solved automatically.\n");
    printf("Estimated shuffle complexity: %d steps\n", shuffleSteps);
    pauseMs(2000);
}

void showWelcomeScreen() {
    clearScreen();

    printHeader("WELCOME TO THE SLIDING PUZZLE");

    printf("Built in C\n");
    printf("Created by Siddharth\n");
    printf("\nPress any key to continue...");
    getch();
}

void chooseDifficulty() {
    int choice;

    clearScreen();
    printHeader("SELECT DIFFICULTY");

    printf("1. Easy   (3x3)\n");
    printf("2. Medium (5x5)\n");
    printf("3. Hard   (6x6)\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        size = 3;
        moveLimit = 40;
        strcpy(difficulty, "Easy");
    }
    else if (choice == 2) {
        size = 5;
        moveLimit = 150;
        strcpy(difficulty, "Medium");
    }
    else {
        size = 6;
        moveLimit = 300;
        strcpy(difficulty, "Hard");
    }
}

void handleInput() {
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
        else if (ch == 'h') {
            runAutoSolver();
            exit(0);
        }
        else if (ch == 'q') {
            clearScreen();
            printHeader("GAME CLOSED");
            printf("Thanks for playing.\n");
            printf("Total moves made: %d\n", moveCount);
            pauseMs(1500);
            exit(0);
        }
    }
}

void showVictoryScreen() {
    clearScreen();

    printHeader("PUZZLE SOLVED");

    printf("Congratulations! You solved the puzzle.\n");
    printf("Total moves: %d\n", moveCount);

    if (moveCount <= moveLimit) {
        printf("Great job! You stayed within the move target.\n");
    } else {
        printf("Solved! But you crossed the suggested move target.\n");
    }

    pauseMs(2500);
}

int main() {
    showWelcomeScreen();
    chooseDifficulty();
    shuffleBoard();

    while (1) {
        displayBoard();

        if (isPuzzleSolved()) {
            showVictoryScreen();
            break;
        }

        handleInput();
    }

    return 0;
}