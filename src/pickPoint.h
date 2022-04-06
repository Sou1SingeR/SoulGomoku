
#ifndef SOULGOMOKU_PICKPOINT_H
#define SOULGOMOKU_PICKPOINT_H

#include "common.h"

#endif //SOULGOMOKU_PICKPOINT_H


int pickPoint(int board[BOARD_SIZE][BOARD_SIZE], int side, int expectedNum, Coord *bestPoints);

int searchToFivePoint(int board[BOARD_SIZE][BOARD_SIZE], int side, Coord *point);

int searchToFourPoint(int board[BOARD_SIZE][BOARD_SIZE], int side, Coord *point);

int searchBestPoints(int board[BOARD_SIZE][BOARD_SIZE], int side, Coord *point, int expectedNum);

void setScore(int score[BOARD_SIZE], int pos, Coord fivePoint[5], int board[BOARD_SIZE][BOARD_SIZE], int pattern1[3], int pattern2[3], int bothEmpty);

int getTopN(int score[BOARD_SIZE][BOARD_SIZE], Point bestPoints[100], int expectedN);

void buildMaxHeap(Point *heap, int l, int p);
