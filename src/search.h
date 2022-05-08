

#ifndef SOULGOMOKU_SEARCH_H
#define SOULGOMOKU_SEARCH_H

#include "evaluate.h"
#include "pickPoint.h"

#endif //SOULGOMOKU_SEARCH_H

extern int pruningNum;
extern int leafNum;
extern double pickTime;
extern double evaluateTime;

int minMaxSearch(int board[BOARD_SIZE][BOARD_SIZE], int *x, int *y, int depth, int maxDepth, int width, int parentScore, int allowPruning);

