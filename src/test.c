
//#include "search.h"
#include "common.h"
#include "pickPoint.h"

//void printBoard(ChessType board[MAP_SIZE][MAP_SIZE]);
//void revertSide(ChessType board[MAP_SIZE][MAP_SIZE]);

int main() {
    init();
    int board[BOARD_SIZE][BOARD_SIZE] = {0};

    int moveNum = 8;
    Coord move[100] = {
            {13, 11}, {8, 8},
            {14, 10}, {9, 10},
            {12, 13}, {10, 10},
            {11, 13}, {11, 11}
    };
    generateBoard(board, move, moveNum, 1);
    showBoard(board, 0);

    Coord point[10];
    int num = pickPoint(board, 10, point);
    printf("return: %d, x: %d, y: %d", num, point[0].x, point[0].y);
//    showBoard(board, 1);

//
//    printBoard(board);
//    revertSide(board);


//    int x, y, score;
//    score = minMaxSearch(board, &x, &y, 6);
//    printf("x: %d, y: %d, score: %d\n", x, y, score);
//
//    Point bestPoints[10];
//    int num = findTheBest(board, SEARCH_WIDTH, bestPoints);
//    printf("num: %d\n\n", num);
//    for (int i = 0; i < num; ++i) {
//        printf("x: %d, y: %d, value: %d\n", bestPoints[i].x, bestPoints[i].y, bestPoints[i].value);
//    }
}

//void printBoard(ChessType board[MAP_SIZE][MAP_SIZE]) {
//    printf("\n");
//    for (int i = 0; i < MAP_SIZE; ++i) {
//        printf("%2d  ", i);
//        for (int j = 0; j < MAP_SIZE; ++j) {
//            if (board[i][j] == EMPTY) {
//                printf(" . ");
//            } else if (board[i][j] == WHITE) {
//                printf(" O ");
//            } else if (board[i][j] == BLACK) {
//                printf(" X ");
//            }
//        }
//        printf("\n");
//    }
//    printf("    ");
//    for (int i = 0; i < MAP_SIZE; ++i) {
//        printf("%2d ", i);
//    }
//    printf("\n\n");
//}
//
//void revertSide(ChessType board[MAP_SIZE][MAP_SIZE]) {
//    for (int i = 0; i < MAP_SIZE; ++i) {
//        for (int j = 0; j < MAP_SIZE; ++j) {
//            if (board[i][j] == EMPTY) {
//                continue;
//            } else if (board[i][j] == WHITE) {
//                board[i][j] = BLACK;
//            } else if (board[i][j] == BLACK) {
//                board[i][j] = WHITE;
//            }
//        }
//    }
//}


