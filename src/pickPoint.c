
#include "pickPoint.h"


// 从给定的局面中，选出 expectedNum 个最佳的点
int pickPoint(int board[BOARD_SIZE][BOARD_SIZE], int expectedNum, Coord *bestPoints) {
    bestPoints[0].x = BOARD_SIZE / 2;
    bestPoints[0].y = BOARD_SIZE / 2;
    return 1;
}

// 寻找指定 side 的第一个成五点
int searchToFivePoint(int board[BOARD_SIZE][BOARD_SIZE], int side, Coord *point) {
    int op = side * -1;
    // d 遍历所有方向, i 遍历该方向的所有起点, j 遍历对应的 1 维空间
    for (int d = 0; d < 4; ++d) {
        for (int i = 0; i < startNum[d]; ++i) {
            int startX = start[d][i].x;
            int startY = start[d][i].y;

            int cacheIdx = 0;
            Point cache[5];
            int emptyNum = 0;
            int selfNum = 0;
            for (int j = 0; ; ++j) {
                int x = startX + directX[d] * j;
                int y = startY + directY[d] * j;
                if (!inBoard(x, y)) {
                    break;
                }
                if (board[x][y] == side) {
                    continue;
                } else if (board[x][y] == op) {
                    ;
                } else if (board[x][y] == 0) {
                    ;
                }

                if (emptyNum == 1 && selfNum ==4) {
                    for (int i = 0; i < 5; ++i) {
                        if (cache[i].value == 0) {
                            (*point).x = x;
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
