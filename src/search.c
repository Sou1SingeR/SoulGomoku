
#include "search.h"

int minMaxSearch(ChessType map[MAP_SIZE][MAP_SIZE], int *x, int *y, int depth) {
    Point bestPoints[10];
    int side = depth % 2; // 0 -> ai; 1 -> opponent
    int nextNum = findTheBest(map, SEARCH_WIDTH, bestPoints);

    if (depth == 0) {
        return bestPoints[0].value;
    }

    ChessType searchMap[MAP_SIZE][MAP_SIZE];
    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            searchMap[i][j] = map[i][j];
            if (side == 0) {
                continue;
            }

            // ai 与对手互换
            if (searchMap[i][j] == WHITE) {
                searchMap[i][j] = BLACK;
            }
            else if (searchMap[i][j] == BLACK) {
                searchMap[i][j] = WHITE;
            }
        }
    }
    for (int i = 0; i < nextNum; ++i) {
        if (side != 0) {
            searchMap[bestPoints[i].x][bestPoints[i].y] = WHITE;
        }
        int maxValue = minMaxSearch(searchMap, )
        searchMap[bestPoints[i].x][bestPoints[i].y] = EMPTY;
    }
    return;
};
