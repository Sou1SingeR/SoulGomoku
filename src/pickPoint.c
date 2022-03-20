
#include "pickPoint.h"


// 从给定的局面中，选出 expectedNum 个最佳的点
int pickPoint(int board[BOARD_SIZE][BOARD_SIZE], int expectedNum, Coord *bestPoints) {
    if (searchToFivePoint(board, 1, bestPoints)) {
        // 己方胜利
        return 1;
    }
    if (searchToFivePoint(board, -1, bestPoints)) {
        // 对方即将胜利，防守点唯一
        return 1;
    }
    if (searchToFourPoint(board, 1, bestPoints)) {
        // 己方可以活四
        return 1;
    }
    int num = searchToFourPoint(board, -1, bestPoints);
    if (num) {
        // 防守对方的若干活三
        return num;
    }

    bestPoints[0].x = BOARD_SIZE / 2;
    bestPoints[0].y = BOARD_SIZE / 2;
    return 1;
}

// 寻找指定 side 的第一个成五点，return: 寻找到的点个数，range: [0, 1]
// 原理：对最近五点的 empty 和 self 计数，如 empty 有 1 个且 self 有 4 个，则取最近一次的 empty 点坐标。
int searchToFivePoint(int board[BOARD_SIZE][BOARD_SIZE], int side, Coord *point) {
    // d 遍历所有方向, i 遍历该方向的所有起点, j 遍历对应的 1 维空间
    for (int d = 0; d < 4; ++d) {
        for (int i = 0; i < startNum[d]; ++i) {
            int startX = start[d][i].x;
            int startY = start[d][i].y;

            int cacheIdx = 0;
            int cache[5] = {9, 9, 9, 9, 9};
            int emptyNum = 0;
            int selfNum = 0;
            for (int j = 0; ; ++j, (cacheIdx = cacheIdx < 5 - 1 ? cacheIdx + 1 : 0)) {
                int x = startX + directX[d] * j;
                int y = startY + directY[d] * j;
                int pointStatus = board[x][y];
                if (!inBoard(x, y)) {
                    break;
                }

                // 清理覆盖位点的缓存
                if (cache[cacheIdx] == side) {
                    --selfNum;
                } else if (cache[cacheIdx] == 0) {
                    --emptyNum;
                }

                // 缓存状态、计数，如是空点则传值给 point
                cache[cacheIdx] = pointStatus;
                if (pointStatus == side) {
                    ++selfNum;
                } else if (pointStatus == 0) {
                    ++emptyNum;
                    (*point).x = x;
                    (*point).y = y;
                }

                if (emptyNum == 1 && selfNum ==4) {
                    // 找到目标，返回 point
                    return 1;
                }
            }
        }
    }
    return 0;
}

// 寻找指定 side 的第一个成活四点，return: 寻找到的点个数，range: [0, 3]
// 原理：对最近四点的 empty 和 self 计数，如 empty 有 1 个且 self 有 3 个且该四点的两头都为 empty，则取最近一次的 empty 点坐标。
int searchToFourPoint(int board[BOARD_SIZE][BOARD_SIZE], int side, Coord *point) {
    // d 遍历所有方向, i 遍历该方向的所有起点, j 遍历对应的 1 维空间
    for (int d = 0; d < 4; ++d) {
        for (int i = 0; i < startNum[d]; ++i) {
            int startX = start[d][i].x;
            int startY = start[d][i].y;

            int cacheIdx = 0;
            int cache[4] = {9, 9, 9, 9};
            int emptyNum = 0;
            int selfNum = 0;
            for (int j = 1; ; ++j, (cacheIdx = cacheIdx < 4 - 1 ? cacheIdx + 1 : 0)) {
                int x = startX + directX[d] * j;
                int y = startY + directY[d] * j;
                int pointStatus = board[x][y];
                if (!inBoard(x + directX[d], y + directY[d])) {
                    // 活四必须要求两头为空，故下一点必须在棋盘内，且 j 从 1 开始遍历
                    break;
                }

                // 清理覆盖位点的缓存
                if (cache[cacheIdx] == side) {
                    --selfNum;
                } else if (cache[cacheIdx] == 0) {
                    --emptyNum;
                }

                // 缓存状态、计数，如是空点则传值给 point
                cache[cacheIdx] = pointStatus;
                if (pointStatus == side) {
                    ++selfNum;
                } else if (pointStatus == 0) {
                    ++emptyNum;
                    point[0].x = x;
                    point[0].y = y;
                }

                if (emptyNum == 1 && selfNum ==3) {
                    Coord left = {x - directX[d] * 4, y - directY[d] * 4};
                    Coord right = {x + directX[d], y + directY[d]};
                    if (board[left.x][left.y] == 0 && board[right.x][right.y] == 0) {
                        // 左右都为空，找到目标，返回 point
                        if (side == 1) {
                            return 1;
                        }
                        // 对方的活三，需返回 2~3 个防守点
                        if ((point[0].x == x && point[0].y == y)) {
                            // 空点在最右
                            point[1].x = left.x;
                            point[1].y = left.y;
                            return 2;
                        } else if ((point[0].x == x - directX[d] * 3 && point[0].y == y - directY[d] * 3)) {
                            // 空点在最左
                            point[1].x = right.x;
                            point[1].y = right.y;
                            return 2;
                        } else {
                            // 跳活三
                            point[1].x = left.x;
                            point[1].y = left.y;
                            point[2].x = right.x;
                            point[2].y = right.y;
                            return 3;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

// 寻找指定 side 的最佳的 expectedNum 个点，return：寻找到的点个数，range: [1, expectedNum]
// 原理：对最近四点的 SELF/EM/OP 计数，根据棋型表来进行加分。
int searchBestPoint(int board[BOARD_SIZE][BOARD_SIZE], int side, Coord *point, int expectedNum) {
    return 1;
}
