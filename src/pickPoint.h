
#ifndef SOULGOMOKU_PICKPOINT_H
#define SOULGOMOKU_PICKPOINT_H

#include "common.h"


int pickPoint(int board[BOARD_SIZE][BOARD_SIZE], int expectedNum, Coord *bestPoints);

int searchToFivePoint(int board[BOARD_SIZE][BOARD_SIZE], int side, Coord *point);



#endif //SOULGOMOKU_PICKPOINT_H
