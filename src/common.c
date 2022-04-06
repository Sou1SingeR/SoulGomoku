#include "common.h"


// 方向分别为横向、纵向、斜向、反斜向
int directX[4] = {1, 0, 1, -1};
int directY[4] = {0, 1, 1, 1};
int startNum[4] = {BOARD_SIZE, BOARD_SIZE, BOARD_SIZE * 2 - 1, BOARD_SIZE * 2 - 1};
Coord start[4][BOARD_SIZE * 2];

int gBoard[BOARD_SIZE][BOARD_SIZE];
int size = BOARD_SIZE;

int inBoard(int x, int y) {
    return x >= 0 && x < size && y >= 0 && y < size;
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

void copyBoard(int board[BOARD_SIZE][BOARD_SIZE], int newBoard[BOARD_SIZE][BOARD_SIZE]) {
    for (int  i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            newBoard[i][j] = board[i][j];
        }
    }
}

void revertBoard(int board[BOARD_SIZE][BOARD_SIZE], int newBoard[BOARD_SIZE][BOARD_SIZE]) {
    for (int  i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            newBoard[i][j] = getOp(board[i][j]);
        }
    }
}

void initDirectionStartPoint() {
    for (int i = 0; i < size; ++i) {
        start[0][i].x = 0;
        start[0][i].y = i;
    }
    for (int i = 0; i < size; ++i) {
        start[1][i].x = i;
        start[1][i].y = 0;
    }
    for (int i = 0; i < size; ++i) {
        start[2][i].x = i;
        start[2][i].y = 0;
    }
    for (int i = 1; i < size; ++i) {
        start[2][i - 1 + size].x = 0;
        start[2][i - 1 + size].y = i;
    }
    for (int i = 0; i < size; ++i) {
        start[3][i].x = i;
        start[3][i].y = 0;
    }
    for (int i = 1; i < size; ++i) {
        start[3][i - 1 + size].x = size - 1;
        start[3][i - 1 + size].y = i;
    }
}

void showBoard(int board[BOARD_SIZE][BOARD_SIZE], int ifClean) {
    if (ifClean) {
        system("cls");
    }
    printf("\n");
    for (int i = size - 1; i >= 0; --i) {
        printf("%2d  ", i);
        for (int j = 0; j < size; ++j) {
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
    for (int i = 0; i < size; ++i) {
        printf("%2d ", i);
    }
    printf("\n\n");
}

void showBoardWithScore(int board[BOARD_SIZE][BOARD_SIZE], int score[BOARD_SIZE][BOARD_SIZE], int ifClean) {
//    if (ifClean) {
//        system("cls");
//    }
    printf("\n");
    for (int i = size - 1; i >= 0; --i) {
        printf("\n");
        printf("%2d  ", i);
        for (int j = 0; j < size; ++j) {
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
        for (int j = 0; j < size; ++j) {
            printf(" %7d ", score[j][i]);
        }
        printf("\n");
    }
    printf("    ");
    for (int i = 0; i < size; ++i) {
        printf("   %2d    ", i);
    }
    printf("\n\n");
}

void resetBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            board[i][j] = EM;
        }
    }
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

void addOne(int num[3], int type) {
    // 棋型数组计数器中对应的棋子类型加一
    if (type == EM) {
        num[0]++;
    } else if (type == SELF) {
        num[1]++;
    } else if (type == OP) {
        num[2]++;
    }
}

void minusOne(int num[3], int type) {
    // 棋型数组计数器中对应的棋子类型减一
    if (type == EM) {
        num[0]--;
    } else if (type == SELF) {
        num[1]--;
    } else if (type == OP) {
        num[2]--;
    }
}

