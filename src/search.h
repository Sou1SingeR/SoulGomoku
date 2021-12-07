

#ifndef SOULGOMOKU_SEARCH_H
#define SOULGOMOKU_SEARCH_H

#include "evaluate.h"

#define SEARCH_WIDTH 10

void minMaxSearch(ChessType map[MAP_SIZE][MAP_SIZE], int *x, int *y, int side);


#endif //SOULGOMOKU_SEARCH_H
