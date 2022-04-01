
#include "search.h"

int minMaxSearch(ChessType map[MAP_SIZE][MAP_SIZE], int *x, int *y, int depth, int width) {
    Point bestPoints[20];
    int nextNum = findTheBest(map, width, bestPoints);

    if (depth == 0 || nextNum == 1) {
        *x = bestPoints[0].x;
        *y = bestPoints[0].y;
        return bestPoints[0].value;
    }

    ChessType searchMap[MAP_SIZE][MAP_SIZE];
    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            searchMap[i][j] = map[i][j];
            // 双方交换
            if (searchMap[i][j] == WHITE) {
                searchMap[i][j] = BLACK;
            }
            else if (searchMap[i][j] == BLACK) {
                searchMap[i][j] = WHITE;
            }
        }
    }
    int bestPointValue = -1;
    int x0, y0;
    for (int i = 0; i < nextNum; ++i) {
        searchMap[bestPoints[i].x][bestPoints[i].y] = BLACK;
        int maxValue = minMaxSearch(searchMap, &x0, &y0, depth - 1, width);
        searchMap[bestPoints[i].x][bestPoints[i].y] = EMPTY;
        if (maxValue > bestPointValue) {
            bestPointValue = maxValue;
            *x = bestPoints[i].x;
            *y = bestPoints[i].y;
        }
    }
    return bestPointValue;
}
