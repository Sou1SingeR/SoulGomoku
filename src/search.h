

#ifndef SOULGOMOKU_SEARCH_H
#define SOULGOMOKU_SEARCH_H

#include "evaluate.h"
#include "pickPoint.h"

#endif //SOULGOMOKU_SEARCH_H

int minMaxSearch(int board[BOARD_SIZE][BOARD_SIZE], int *x, int *y, int depth, int maxDepth, int width, int parentScore, int allowPruning);

