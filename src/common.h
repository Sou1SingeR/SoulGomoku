
#ifndef SOULGOMOKU_COMMON_H
#define SOULGOMOKU_COMMON_H

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SELF 1
#define OP -1
#define EM 0
#define BOARD_SIZE 20

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
extern int gBoard[BOARD_SIZE][BOARD_SIZE];
extern int size;

// 判断是否在棋盘内
int inBoard(int x, int y);

// 判断是否为空位
int isEmpty(int board[BOARD_SIZE][BOARD_SIZE], int x, int y);

// 判断是否为己方棋子
int isSelf(int board[BOARD_SIZE][BOARD_SIZE], int x, int y);

// 判断是否为对方棋子
int isOp(int board[BOARD_SIZE][BOARD_SIZE], int x, int y);

// 获取另一种棋子类型
int getOp(int side);

int max(int a, int b);

int min(int a, int b);

int doSth();

// 复制棋盘
void copyBoard(int board[BOARD_SIZE][BOARD_SIZE], int newBoard[BOARD_SIZE][BOARD_SIZE]);

// 复制并翻转棋盘
void revertBoard(int board[BOARD_SIZE][BOARD_SIZE], int newBoard[BOARD_SIZE][BOARD_SIZE]);

// 初始化遍历方向起始点
void initDirectionStartPoint();

// 将棋盘状态打印到控制台
void showBoard(int board[BOARD_SIZE][BOARD_SIZE], int ifClean);

// 将棋盘状态以及分数打印到控制台
void showBoardWithScore(int board[BOARD_SIZE][BOARD_SIZE], int score[BOARD_SIZE][BOARD_SIZE], int ifClean);

// 棋盘复位
void resetBoard(int board[BOARD_SIZE][BOARD_SIZE]);

// 生成指定局面
void generateBoard(int board[BOARD_SIZE][BOARD_SIZE], Coord *move, int moveNum, int firstSide);

// 初始化
void init();

// 棋型数组加一
void addOne(int num[3], int type);

// 棋型数组减一
void minusOne(int num[3], int type);
