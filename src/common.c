#include "common.h"

int inBoard(int x, int y) {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

int doSth() {
    return 0;
}

void initDirectionStartPoint() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        start[0][i].x = 0;
        start[0][i].y = i;
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
        start[1][i].x = i;
        start[1][i].y = 0;
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
        start[2][i].x = i;
        start[2][i].y = 0;
    }
    for (int i = 1; i < BOARD_SIZE; ++i) {
        start[2][i - 1 + BOARD_SIZE].x = 0;
        start[2][i - 1 + BOARD_SIZE].y = i;
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
        start[3][i].x = i;
        start[3][i].y = 0;
    }
    for (int i = 1; i < BOARD_SIZE; ++i) {
        start[3][i - 1 + BOARD_SIZE].x = BOARD_SIZE - 1;
        start[3][i - 1 + BOARD_SIZE].y = i;
    }
}


void showBoard(int board[BOARD_SIZE][BOARD_SIZE], int ifClean) {
    if (ifClean) {
        system("cls");
    }
    printf("\n");
    for (int i = BOARD_SIZE - 1; i > 0; ++i) {
        printf("%2d  ", i);
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == 0) {
                printf(" . ");
            } else if (board[i][j] == 1) {
                printf(" O ");
            } else if (board[i][j] == -1) {
                printf(" X ");
            }
        }
        printf("\n");
    }
    printf("    ");
    for (int i = 0; i < BOARD_SIZE; ++i) {
        printf("%2d ", i);
    }
    printf("\n\n");
}

void init() {
    initDirectionStartPoint();
}


