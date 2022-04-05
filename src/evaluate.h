
#ifndef SOULGOMOKU_EVALUATE_H
#define SOULGOMOKU_EVALUATE_H

#include "common.h"

#endif //SOULGOMOKU_EVALUATE_H


int evaluate(int board[BOARD_SIZE][BOARD_SIZE]);

void addOne(int num[3], int type);

void minusOne(int num[3], int type);

int getScore(int pattern1[3], int pattern2[3], int bothEmpty);
