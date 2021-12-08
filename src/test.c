
#include "search.h"

void printBoard(ChessType board[MAP_SIZE][MAP_SIZE]);
void revertSide(ChessType board[MAP_SIZE][MAP_SIZE]);

int main() {
    ChessType board[MAP_SIZE][MAP_SIZE] = {EMPTY};
    board[7][7] = WHITE;
    board[6][7] = BLACK;
    board[6][6] = WHITE;
    board[7][6] = BLACK;
    board[5][8] = WHITE;
    board[5][4] = BLACK;
    board[4][8] = WHITE;
    board[6][8] = BLACK;
    board[5][5] = WHITE;
    board[4][4] = BLACK;
    board[3][5] = WHITE;
    board[3][4] = BLACK;
    board[2][4] = WHITE;
    board[5][7] = BLACK;

    printBoard(board);
    revertSide(board);


    int x, y, score;
    score = minMaxSearch(board, &x, &y, 6);
    printf("x: %d, y: %d, score: %d\n", x, y, score);

    Point bestPoints[10];
    int num = findTheBest(board, SEARCH_WIDTH, bestPoints);
    printf("num: %d\n\n", num);
    for (int i = 0; i < num; ++i) {
        printf("x: %d, y: %d, value: %d\n", bestPoints[i].x, bestPoints[i].y, bestPoints[i].value);
    }
}

void printBoard(ChessType board[MAP_SIZE][MAP_SIZE]) {
    printf("\n");
    for (int i = 0; i < MAP_SIZE; ++i) {
        printf("%2d  ", i);
        for (int j = 0; j < MAP_SIZE; ++j) {
            if (board[i][j] == EMPTY) {
                printf(" . ");
            } else if (board[i][j] == WHITE) {
                printf(" O ");
            } else if (board[i][j] == BLACK) {
                printf(" X ");
            }
        }
        printf("\n");
    }
    printf("    ");
    for (int i = 0; i < MAP_SIZE; ++i) {
        printf("%2d ", i);
    }
    printf("\n\n");
}

void revertSide(ChessType board[MAP_SIZE][MAP_SIZE]) {
    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            if (board[i][j] == EMPTY) {
                continue;
            } else if (board[i][j] == WHITE) {
                board[i][j] = BLACK;
            } else if (board[i][j] == BLACK) {
                board[i][j] = WHITE;
            }
        }
    }
}


