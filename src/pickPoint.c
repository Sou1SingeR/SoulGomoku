
#include "pickPoint.h"


// 从给定的局面中，选出 expectedNum 个最佳的点
int pickPoint(int board[BOARD_SIZE][BOARD_SIZE], int expectedNum, Coord *bestPoints) {
    if (searchToFivePoint(board, SELF, bestPoints)) {
        // 己方胜利
        return 1;
    }
    if (searchToFivePoint(board, OP, bestPoints)) {
        // 对方即将胜利，防守点唯一
        return 1;
    }
    if (searchToFourPoint(board, SELF, bestPoints)) {
        // 己方可以活四
        return 1;
    }
    int num = searchToFourPoint(board, OP, bestPoints);
    if (num) {
        // 防守对方的若干活三
        return num;
    }

    num = searchBestPoints(board, SELF, bestPoints, expectedNum);
    return num;
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
                        if (side == SELF) {
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
// 原理：对 [-4, 0], [-4, -1] 的 SELF/EM/OP 计数，根据棋型表来进行加分。
int searchBestPoints(int board[BOARD_SIZE][BOARD_SIZE], int side, Coord *point, int expectedNum) {
    int score[BOARD_SIZE][BOARD_SIZE] = {0};
    // d 遍历所有方向, i 遍历该方向的所有起点, j 遍历对应的 1 维空间
    for (int d = 0; d < 4; ++d) {
        for (int i = 0; i < startNum[d]; ++i) {
            int startX = start[d][i].x;
            int startY = start[d][i].y;
            if (!inBoard(startX + directX[d] * 4, startY + directY[d] * 4)) {
                // 长度不够 5，该一维空间不具备价值
                continue;
            }

            int cacheIdx = 0;
            int cache[5] = {9, 9, 9, 9, 9};
            int pattern1[3] = {0}; // [-4, 0] EM, SELF, OP 的数量
            int pattern2[3] = {0}; // [-4, -1] EM, SELF, OP 的数量
            int thisScore[BOARD_SIZE] = {0};

            for (int j = 0; j < 5; ++j) {
                int x = startX + directX[d] * j;
                int y = startY + directY[d] * j;
                int pointStatus = board[x][y];
                cache[j] = pointStatus;
                addOne(pattern1, pointStatus);
                if (j != 4) {
                    addOne(pattern2, pointStatus);
                }
            }
            for (int j = 5 - 1; ; ++j) {
                int x = startX + directX[d] * j;
                int y = startY + directY[d] * j;
                if (!inBoard(x, y)) break;

                // cache 操作
                if (j != 5 - 1) {
                    minusOne(pattern1, cache[cacheIdx]);
                    minusOne(pattern2, cache[cacheIdx]);
                    cache[cacheIdx] = board[x][y];
                    cacheIdx += cacheIdx == 4 ? -4 : 1;
                    addOne(pattern1, board[x][y]);
                    addOne(pattern2, board[x - directX[d]][y - directY[d]]);
                }

                // TODO: 计分
                int bothEmpty = isEmpty(board, x, y) && isEmpty(board, x - directX[d] * 5, y - directY[d] * 5);
                Coord fivePoint[5];
                for (int k = 0; k < 5; ++k) {
                    fivePoint[5 - 1 - k].x = x - directX[d] * k;
                    fivePoint[5 - 1 - k].y = y - directY[d] * k;
                }
                setScore(thisScore, j - (5 - 1), fivePoint, board, pattern1, pattern2, bothEmpty);
            }

            for (int j = 0; ; ++j) {
                int x = startX + directX[d] * j;
                int y = startY + directY[d] * j;
                if (!inBoard(x, y)) break;
                score[x][y] += thisScore[j];
            }
        }
    }

    showBoardWithScore(board, score, 1);

    Point bestPoints[100];
    int realNum = getTopN(score, bestPoints, expectedNum);
    for (int i = 0; i < realNum; ++i) {
        point[i].x = bestPoints[i].x;
        point[i].y = bestPoints[i].y;
//        printf("rank %d: (%d, %d) - %d\n", i + 1, bestPoints[i].x, bestPoints[i].y, bestPoints[i].value);
    }
    return realNum;
}

void addOne(int num[3], int type) {
    // 棋型数组计数器中对应的棋子类型加一
    if (type == EM) {
        num[0]++;
    } else if (type == SELF) {
        num[1]++;
    } else if (type == OP) {
        num[2]++;
    }
}

void minusOne(int num[3], int type) {
    // 棋型数组计数器中对应的棋子类型减一
    if (type == EM) {
        num[0]--;
    } else if (type == SELF) {
        num[1]--;
    } else if (type == OP) {
        num[2]--;
    }
}

void setScore(int score[BOARD_SIZE], int pos, Coord fivePoint[5], int board[BOARD_SIZE][BOARD_SIZE], int pattern1[3], int pattern2[3], int bothEmpty) {
    // 分数表
    int attackSleepScore[4] = {0, 9999, 99999, 999999};
    int attackActiveScore[3] = {10000, 100000, 1000000};
    int defenceSleepScore[4] = {0, 0, 9999, 99999};
    int defenceActiveScore[3] = {0, 10000, 100000};

    // 更新一维空间的分数
    if (pattern1[2] == 0) {
        // 眠棋型攻击
        int worth = attackSleepScore[pattern1[1]];
        for (int i = 0; i < 5; ++i) {
            if (board[fivePoint[i].x][fivePoint[i].y] == EM) {
                score[pos + i] = max(score[pos + i], worth);
            }
        }
    }
    if (pattern2[2] == 0 && bothEmpty) {
        // 活棋型攻击
        int worth = attackActiveScore[pattern2[1]];
        for (int i = 0; i < 4; ++i) {
            if (board[fivePoint[i].x][fivePoint[i].y] == EM) {
                score[pos + i] = max(score[pos + i], worth);
            }
        }
    }
    if (pattern1[1] == 0) {
        // 眠棋型防守
        int worth = defenceSleepScore[pattern1[2]];
        for (int i = 0; i < 5; ++i) {
            if (board[fivePoint[i].x][fivePoint[i].y] == EM) {
                score[pos + i] = max(score[pos + i], worth);
            }
        }
    }
    if (pattern2[1] == 0 && bothEmpty) {
        // 活棋型防守
        // 有 bug -> 数字为空，X 为 OP，1XX456 的 5 不应有分
        int worth = defenceActiveScore[pattern2[2]];
        for (int i = 0; i < 4; ++i) {
            if (board[fivePoint[i].x][fivePoint[i].y] == EM) {
                score[pos + i] = max(score[pos + i], worth);
            }
        }
    }
}

int getTopN(int score[BOARD_SIZE][BOARD_SIZE], Point *bestPoints, int expectedN) {
    Point maxHeap[BOARD_SIZE * BOARD_SIZE];
    int l = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (score[i][j] <= 40000) {
                continue;
            }
            maxHeap[l].x = i;
            maxHeap[l].y = j;
            maxHeap[l].value = score[i][j];
            ++l;
        }
    }
    for (int i = l / 2 - 1; i >= 0; --i) {
        // 构造大顶堆
        buildMaxHeap(maxHeap, l, i);
    }
    int n = min(expectedN, l);
    for (int i = 0; i < n; ++i) {
        // 依次取点
        bestPoints[i] = maxHeap[0];
        maxHeap[0] = maxHeap[--l];
        buildMaxHeap(maxHeap, l, 0);
    }
    return n;
}

void buildMaxHeap(Point *heap, int l, int p) {
    if (p > l) {
        printf("error: length exceeds limit(p > n).\n");
        return;
    }
    if (p > l / 2 - 1) {
        // 叶子结点
        return;
    }
    if (p == l / 2 - 1 && l % 2 == 0) {
        // 只有左子结点
        if (heap[p].value > heap[p * 2 + 1].value) {
            return;
        }
        Point tmp = heap[p];
        heap[p] = heap[p * 2 + 1];
        heap[p * 2 + 1] = tmp;
        return;
    }
    // 有两个子结点
    int pMax = heap[p * 2 + 1].value > heap[p * 2 + 2].value ? p * 2 + 1 : p * 2 + 2;
    if (heap[p].value > heap[pMax].value) {
        return;
    }
    Point tmp = heap[p];
    heap[p] = heap[pMax];
    heap[pMax] = tmp;
    buildMaxHeap(heap, l, pMax);
}






