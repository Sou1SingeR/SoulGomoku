
#include "search.h"

void minMaxSearch(ChessType map[MAP_SIZE][MAP_SIZE], int *x, int *y, int side) {
    Point bestPoints[10];
    int nextNum = findTheBest(map, SEARCH_WIDTH, bestPoints);
    return;
};
