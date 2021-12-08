

#ifndef SOULGOMOKU_SEARCH_H
#define SOULGOMOKU_SEARCH_H

#include "evaluate.h"

#define SEARCH_WIDTH 5

int minMaxSearch(ChessType map[MAP_SIZE][MAP_SIZE], int *x, int *y, int depth);


#endif //SOULGOMOKU_SEARCH_H
