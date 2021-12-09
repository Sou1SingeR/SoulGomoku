
#ifndef SOULGOMOKU_COMMON_H
#define SOULGOMOKU_COMMON_H


#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define Stn int
#define SELF 1
#define OP -1

// 定义遍历方向
// 定义遍历起点


#define BOARD_SIZE 15

typedef struct Coord {
    int x;
    int y;
} Coord;

typedef struct Point {
    int x;
    int y;
    int value;
} Point;

// 方向分别为横向、纵向、斜向、反斜向
int directX[4] = {1, 0, 1, -1};
int directY[4] = {0, 1, 1, 1};
int startNum[4] = {BOARD_SIZE, BOARD_SIZE, BOARD_SIZE * 2 - 1, BOARD_SIZE * 2 - 1};
Coord start[4][BOARD_SIZE * 2];

// 判断是否在棋盘内
int inBoard(int x, int y);

int doSth();

void initDirectionStartPoint();

void showBoard(int board[BOARD_SIZE][BOARD_SIZE], int ifClean);

void init();

#endif //SOULGOMOKU_COMMON_H
