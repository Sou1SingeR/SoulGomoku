
#ifndef SOULGOMOKU_PICKPOINT_H
#define SOULGOMOKU_PICKPOINT_H

#include "common.h"

#endif //SOULGOMOKU_PICKPOINT_H


int pickPoint(int board[BOARD_SIZE][BOARD_SIZE], int expectedNum, Coord *bestPoints);

int searchToFivePoint(int board[BOARD_SIZE][BOARD_SIZE], int side, Coord *point);

int searchToFourPoint(int board[BOARD_SIZE][BOARD_SIZE], int side, Coord *point);

int searchBestPoint(int board[BOARD_SIZE][BOARD_SIZE], int side, Coord *point, int expectedNum);
