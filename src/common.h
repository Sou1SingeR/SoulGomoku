
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

#endif //SOULGOMOKU_COMMON_H

// 方向分别为横向、纵向、斜向、反斜向
extern int directX[4];
extern int directY[4];
extern int startNum[4];
extern Coord start[4][BOARD_SIZE * 2];

// 判断是否在棋盘内
int inBoard(int x, int y);

int doSth();

// 初始化遍历方向起始点
void initDirectionStartPoint();

// 将棋盘状态打印到控制台
void showBoard(int board[BOARD_SIZE][BOARD_SIZE], int ifClean);

// 生成指定局面
void generateBoard(int board[BOARD_SIZE][BOARD_SIZE], Coord *move, int moveNum, int firstSide);

// 初始化
void init();

