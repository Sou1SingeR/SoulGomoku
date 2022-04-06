
#include "unitTest.h"


void t_getTopN() {
    Point bestPoints[100];
    int score[BOARD_SIZE][BOARD_SIZE] = {0};
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            score[i][j] = rand() % 1000;
        }
    }
    int realNum = getTopN(score, bestPoints, 66);
    printf("realNum: %d\n\n", realNum);
    for (int i = 0; i < realNum; ++i) {
        printf("rank %2d: (%d, %d) [%d]\n", i + 1, bestPoints[i].x, bestPoints[i].y, bestPoints[i].value);
    }
}

void t_pickPoint() {

    init();
    int board[BOARD_SIZE][BOARD_SIZE] = {0};

    int moveNum = 14;
    Coord move[100] = {
            {13, 11}, {8, 8},
            {14, 10}, {9, 10},
            {12, 13}, {10, 10},
            {11, 13}, {11, 11},
            {9, 9}, {12, 12},
            {2, 2}, {2, 3},
            {3, 2}, {3, 3}
    };
    generateBoard(board, move, moveNum, SELF);
    showBoard(board, 0);

    Coord point[10];
    int num = pickPoint(board, SELF, 10, point);
    printf("return: %d\n", num);
    for (int i = 0; i < num; ++i) {
        printf("(%d, %d) ", point[i].x, point[i].y);
    }

}

void t_setScore() {
    int score[BOARD_SIZE][BOARD_SIZE] = {0};
    int board[BOARD_SIZE][BOARD_SIZE] = {0};
    int moveNum = 14;
    Coord move[100] = {
            {13, 11}, {8, 8},
            {14, 10}, {9, 10},
            {12, 13}, {10, 10},
            {11, 13}, {11, 11},
            {9, 9}, {12, 12},
            {2, 2}, {2, 3},
            {3, 2}, {3, 3}
    };
    generateBoard(board, move, moveNum, SELF);
    showBoard(board, 0);

    // d 遍历所有方向, i 遍历该方向的所有起点, j 遍历对应的 1 维空间
//    for (int d = 0; d < 4; ++d) {
//        for (int i = 0; i < startNum[d]; ++i) {
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
                for (int j = 0; j < size; ++j) {
                    printf("%d, ", board[j][i]);
                }
                printf("\ncache: %d, %d, %d, %d, %d, cacheIdx: %d, pattern1: %d, %d, %d, pattern2: %d, %d, %d\n", cache[0], cache[1], cache[2], cache[3], cache[4], cacheIdx, pattern1[0], pattern1[1], pattern1[2], pattern2[0], pattern2[1], pattern2[2]);
                for (int k = 0; k < size; ++k) {
                    printf("%d, ", thisScore[k]);
                }
                printf("\n\n");
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
    Coord point[100];
    int realNum = getTopN(score, bestPoints, 10);
    for (int i = 0; i < realNum; ++i) {
        point[i].x = bestPoints[i].x;
        point[i].y = bestPoints[i].y;
    }
    printf("\n");
}

void t_evaluate() {
    init();
    int board[BOARD_SIZE][BOARD_SIZE] = {0};

    int moveNum = 14;
    Coord move[100] = {
            {13, 11}, {8, 8},
            {14, 10}, {9, 10},
            {12, 13}, {10, 10},
            {11, 13}, {11, 11},
            {9, 9}, {12, 12},
            {2, 2}, {2, 3},
            {3, 2}, {3, 3}
    };
    generateBoard(board, move, moveNum, SELF);
    showBoard(board, 0);
    int score = evaluate(board);
    printf("\nTotal score: %d\n", score);
}

void t_minMaxSearch() {
    init();
    int board[BOARD_SIZE][BOARD_SIZE] = {0};

    int moveNum = 14;
    Coord move[100] = {
            {13, 11}, {8, 8},
            {14, 10}, {9, 10},
            {12, 13}, {10, 10},
            {11, 13}, {11, 11},
            {9, 9}, {12, 12},
            {2, 2}, {2, 3},
            {3, 2}, {3, 3}
    };
    generateBoard(board, move, moveNum, SELF);
    showBoard(board, 0);

    int x, y;
    clock_t time0 = clock();
    minMaxSearch(board, &x, &y, 8, 8, 10, 0, 0);
    clock_t time1 = clock();
    double dur = (double)(time1 - time0) / CLOCKS_PER_SEC;

    printf("bestPoint: (%2d,%2d), use time: %fs", x, y, dur);
}
