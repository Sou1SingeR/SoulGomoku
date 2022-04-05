#include "evaluate.h"



int evaluate(int board[BOARD_SIZE][BOARD_SIZE]) {
    int score = 0;
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

            int cd = 0;
            int rowScore = 0;
            int lastScore = 0;
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
                int thisScore = getScore(pattern1, pattern2, bothEmpty);
                if (lastScore >= 0 && thisScore > lastScore || lastScore <= 0 && thisScore < lastScore) {
                    lastScore = thisScore;
                    cd = 3;
                }
                if (cd == 0) {
                    rowScore += lastScore;
                    lastScore = 0;
                }
                if (cd > 0) {
                    --cd;
                }
            }
            if (cd == 0) {
                rowScore += lastScore;
            }
            score += rowScore;
        }
    }
    return score;
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

int getScore(int pattern1[3], int pattern2[3], int bothEmpty) {
    // 分数表
    int sleepScore[5] = {0, 1000, 10000, 100000, 1000000};
    int activeScore[4] = {0, 10000, 100000, 1000000};

    int score = 0;
    if (pattern1[2] == 0) {
        // 己方眠棋型
        score = sleepScore[pattern1[1]];
    }
    if (pattern2[2] == 0 && bothEmpty) {
        // 己方活棋型
        return max(score, activeScore[pattern2[1]]);
    }
    if (pattern1[1] == 0) {
        // 对方眠棋型
        score = sleepScore[pattern1[2]];
    }
    if (pattern2[1] == 0 && bothEmpty) {
        // 对方活棋型
        return max(score, activeScore[pattern2[2]]) * -1;
    }
    return 0;
}


