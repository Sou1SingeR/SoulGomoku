
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


