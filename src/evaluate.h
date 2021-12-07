
#ifndef SOULGOMOKU_EVALUATE_H
#define SOULGOMOKU_EVALUATE_H

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <windows.h>

#define random(x) (rand()%x)

#define BOOL  int
#define TRUE   1
#define FALSE  0

#define WIDTH_MAX  100
#define HEIGHT_MAX  100
#define WIDTH_MIN   5
#define HEIGHT_MIN  5
#define TIME_DELAY 1000
#define MAP_SIZE 15

typedef enum ChessType {
    EMPTY = 0,
    WHITE = 1,
    BLACK = 2
} ChessType;

typedef struct Point {
    int x;
    int y;
    int value;
} Point;

//enum ChessType chessmap[MAP_SIZE][MAP_SIZE];

// 算法相关 //////////////////////////////////////////////////////////////////


//To Three参数
int map_3(enum ChessType chessMap[MAP_SIZE][MAP_SIZE], int x, int map3[MAP_SIZE][MAP_SIZE]);

//To Four参数
int map_4(enum ChessType chessMap[MAP_SIZE][MAP_SIZE], int x, int map4[MAP_SIZE][MAP_SIZE]);

//valueD表
int table_B(enum ChessType str[4], int x);

//valueA表
int table_A(enum ChessType str[4], int x);

//valueD计算
void value_B(enum ChessType chessMap[MAP_SIZE][MAP_SIZE], int x, int valueMap[MAP_SIZE][MAP_SIZE]);

//valueA计算
void value_A(enum ChessType chessMap[MAP_SIZE][MAP_SIZE], int x, int valueMap[MAP_SIZE][MAP_SIZE]);

// 下一步落子位置
int findTheBest(enum ChessType chessMap[MAP_SIZE][MAP_SIZE], int expectedLen, Point *points);

#endif //SOULGOMOKU_EVALUATE_H
