#include "common.h"


// 方向分别为横向、纵向、斜向、反斜向
int directX[4] = {1, 0, 1, -1};
int directY[4] = {0, 1, 1, 1};
int startNum[4] = {BOARD_SIZE, BOARD_SIZE, BOARD_SIZE * 2 - 1, BOARD_SIZE * 2 - 1};
Coord start[4][BOARD_SIZE * 2];


int inBoard(int x, int y) {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

int isEmpty(int board[BOARD_SIZE][BOARD_SIZE], int x, int y) {
    return inBoard(x, y) && board[x][y] == EM;
}

int isSelf(int board[BOARD_SIZE][BOARD_SIZE], int x, int y) {
    return inBoard(x, y) && board[x][y] == SELF;
}

int isOpponent(int board[BOARD_SIZE][BOARD_SIZE], int x, int y) {
    return inBoard(x, y) && board[x][y] == OP;
}

int getOp(int side) {
    return side * -1;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
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
    for (int i = BOARD_SIZE - 1; i >= 0; --i) {
        printf("%2d  ", i);
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[j][i] == 0) {
                printf(" . ");
            } else if (board[j][i] == 1) {
                printf(" O ");
            } else if (board[j][i] == -1) {
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

void showBoardWithScore(int board[BOARD_SIZE][BOARD_SIZE], int score[BOARD_SIZE][BOARD_SIZE], int ifClean) {
//    if (ifClean) {
//        system("cls");
//    }
    printf("\n");
    for (int i = BOARD_SIZE - 1; i >= 0; --i) {
        printf("\n");
        printf("%2d  ", i);
        for (int j = 0; j < BOARD_SIZE; ++j) {
            printf("   ");
            if (board[j][i] == 0) {
                printf("[.]");
            } else if (board[j][i] == 1) {
                printf("[O]");
            } else if (board[j][i] == -1) {
                printf("[X]");
            }
            printf("   ");
        }
        printf("\n   ");
        for (int j = 0; j < BOARD_SIZE; ++j) {
            printf(" %7d ", score[j][i]);
        }
        printf("\n");
    }
    printf("    ");
    for (int i = 0; i < BOARD_SIZE; ++i) {
        printf("   %2d    ", i);
    }
    printf("\n\n");
}

void generateBoard(int board[BOARD_SIZE][BOARD_SIZE], Coord *move, int moveNum, int firstSide) {
    int side = firstSide;
    for (int i = 0; i < moveNum; ++i, side *= -1) {
        board[move[i].x][move[i].y] = side;
    }
}

void init() {
    initDirectionStartPoint();
}


