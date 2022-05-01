
#include <stdio.h>

#define SELF 1
#define OP -1
#define EM 0
#define BOARD_SIZE 15

typedef struct Coord {
    int x;
    int y;
} Coord;

typedef struct Point {
    int x;
    int y;
    int value;
} Point;

// 方向分别为横向、纵向、斜向、反斜向
int directX[4] = {1, 0, 1, -1};
int directY[4] = {0, 1, 1, 1};
int startNum[4] = {BOARD_SIZE, BOARD_SIZE, BOARD_SIZE * 2 - 1, BOARD_SIZE * 2 - 1};
Coord start[4][BOARD_SIZE * 2];

int gBoard[BOARD_SIZE][BOARD_SIZE] = {EM};
int size = BOARD_SIZE;

/*************** common ****************/
int inBoard(int x, int y) {
    return x >= 0 && x < size && y >= 0 && y < size;
}

int isEmpty(int board[BOARD_SIZE][BOARD_SIZE], int x, int y) {
    return inBoard(x, y) && board[x][y] == EM;
}

int getOp(int side) {
    return side * -1;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void showBoard(int board[BOARD_SIZE][BOARD_SIZE], int ifClean) {
    printf("\n");
    for (int i = size - 1; i >= 0; --i) {
        printf("%2d  ", i);
        for (int j = 0; j < size; ++j) {
            if (board[j][i] == 0) {
                printf(" . ");
            } else if (board[j][i] == 1) {
                printf(" O ");
            } else if (board[j][i] == -1) {
                printf(" X ");
            }
        }
        printf("\n");
    }
    printf("    ");
    for (int i = 0; i < size; ++i) {
        printf("%2d ", i);
    }
    printf("\n\n");
}

void copyBoard(int board[BOARD_SIZE][BOARD_SIZE], int newBoard[BOARD_SIZE][BOARD_SIZE]) {
    for (int  i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            newBoard[i][j] = board[i][j];
        }
    }
}

void revertBoard(int board[BOARD_SIZE][BOARD_SIZE], int newBoard[BOARD_SIZE][BOARD_SIZE]) {
    for (int  i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            newBoard[i][j] = getOp(board[i][j]);
        }
    }
}

void initDirectionStartPoint() {
    for (int i = 0; i < size; ++i) {
        start[0][i].x = 0;
        start[0][i].y = i;
    }
    for (int i = 0; i < size; ++i) {
        start[1][i].x = i;
        start[1][i].y = 0;
    }
    for (int i = 0; i < size; ++i) {
        start[2][i].x = i;
        start[2][i].y = 0;
    }
    for (int i = 1; i < size; ++i) {
        start[2][i - 1 + size].x = 0;
        start[2][i - 1 + size].y = i;
    }
    for (int i = 0; i < size; ++i) {
        start[3][i].x = i;
        start[3][i].y = 0;
    }
    for (int i = 1; i < size; ++i) {
        start[3][i - 1 + size].x = size - 1;
        start[3][i - 1 + size].y = i;
    }
}

void init() {
    initDirectionStartPoint();
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
/*************** common ****************/

/*************** pickPoint ****************/
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

int getTopN(int score[BOARD_SIZE][BOARD_SIZE], Point *bestPoints, int expectedN) {
    Point maxHeap[size * size];
    int l = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
//            if (score[i][j] <= 40000) {
//                continue;
//            }
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

//    showBoardWithScore(board, score, 1);

    Point bestPoints[100];
    int realNum = getTopN(score, bestPoints, expectedNum);
    for (int i = 0; i < realNum; ++i) {
        point[i].x = bestPoints[i].x;
        point[i].y = bestPoints[i].y;
//        printf("rank %d: (%d, %d) - %d\n", i + 1, bestPoints[i].x, bestPoints[i].y, bestPoints[i].value);
    }
    return realNum;
}

// 从给定的局面中，选出 expectedNum 个最佳的点
int pickPoint(int board[BOARD_SIZE][BOARD_SIZE], int side, int expectedNum, Coord *bestPoints) {
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
    if (side == SELF) {
        num = searchBestPoints(board, SELF, bestPoints, expectedNum);
        return num;
    } else {
        int newBoard[BOARD_SIZE][BOARD_SIZE];
        revertBoard(board, newBoard);
        num = searchBestPoints(newBoard, SELF, bestPoints, expectedNum);
        return num;
    }
}
/*************** pickPoint ****************/

/*************** evaluate ****************/
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
            rowScore += lastScore;

            score += rowScore;
        }
    }
    return score;
}
/*************** evaluate ****************/

/*************** search ****************/
int minMaxSearch(int board[BOARD_SIZE][BOARD_SIZE], int *x, int *y, int depth, int maxDepth, int width, int parentScore, int allowPruning) {
    int side = depth % 2 == 0 ? SELF : OP;
    Coord candidate[20];
    if (searchToFivePoint(board, side, candidate)) {
        // 此方胜利
        if (depth == maxDepth) {
            *x = candidate[0].x;
            *y = candidate[0].y;
        }
        return 100000000 * side;
    }
    if (searchToFivePoint(board, getOp(side), candidate)) {
        // 此方失败
        if (depth == maxDepth) {
            *x = candidate[0].x;
            *y = candidate[0].y;
        }
        return -100000000 * side;
    }
    if (searchToFourPoint(board, side, candidate)) {
        // 此方活四必胜
        if (depth == maxDepth) {
            *x = candidate[0].x;
            *y = candidate[0].y;
        }
        return 100000000 * side;
    }

    if (depth == 0) {
        // 叶子结点，计算分数
        return evaluate(board);
    }
    int minMaxScore;
    int num = pickPoint(board, side, width, candidate);
    for (int i = 0; i < num; ++i) {
        int newBoard[BOARD_SIZE][BOARD_SIZE];
        copyBoard(board, newBoard);
        newBoard[candidate[i].x][candidate[i].y] = side;

        int score = minMaxSearch(newBoard, x, y, depth - 1, maxDepth, width, minMaxScore, i != 0);
        if (i == 0) {
            minMaxScore = score;
            if (depth == maxDepth) {
                *x = candidate[i].x;
                *y = candidate[i].y;
            }
            continue;
        }
        if (allowPruning) {
            // alpha-bata 剪枝
            if (side == SELF && minMaxScore >= parentScore || side == OP && minMaxScore <= parentScore) {
                return minMaxScore;
            }
        }
        if (side == SELF && score > minMaxScore || side == OP && score < minMaxScore) {
            minMaxScore = score;
            if (depth == maxDepth) {
                *x = candidate[i].x;
                *y = candidate[i].y;
            }
        }
    }
    return minMaxScore;
}
/*************** search ****************/

int main()
{
    init();
    int x, y, side, len;
    scanf("%d", &len);
    len = len * 2 - 1;
    scanf("%d %d", &x, &y);
    side = OP;
    if (x == -1 && y == -1) {
        if (len == 1) {
            printf("%d %d", size / 2, size / 2);
            return 0;
        }
    } else {
        gBoard[x][y] = side;
    }
    side *= -1;
    for (int i = 1; i < len; ++i) {
        scanf("%d %d", &x, &y);
        gBoard[x][y] = side;
        side *= -1;
    }
    minMaxSearch(gBoard, &x, &y, 6, 6, 8, 0, 0);
    printf("%d %d", x, y);
    return 0;
}
