
#include "search.h"

int pruningNum = 0;
int leafNum = 0;
double pickTime = 0;
double evaluateTime = 0;

int minMaxSearch(int board[BOARD_SIZE][BOARD_SIZE], int *x, int *y, int depth, int maxDepth, int width, int parentScore, int allowPruning) {
//    for (int i = 0; i < maxDepth - depth; ++i) {
//        printf("\t");
//    }
//    printf("depth: %d, parentScore: %d, allowPruning: %d. ", depth, parentScore, allowPruning);
    clock_t t0, t1;
    int side = depth % 2 == 0 ? SELF : OP;
    Coord candidate[20];
    if (searchToFivePoint(board, side, candidate)) {
        // 此方胜利
        if (depth == maxDepth) {
            *x = candidate[0].x;
            *y = candidate[0].y;
        }
//        printf("this win.\n");
        return 100000000 * side;
    }
    if (!searchToFivePoint(board, getOp(side), candidate) && searchToFourPoint(board, side, candidate)) {
        // 此方活四必胜
        if (depth == maxDepth) {
            *x = candidate[0].x;
            *y = candidate[0].y;
        }
//        printf("this live4 win.\n");
        return 100000000 * side;
    }

    if (depth == 0) {
        // 叶子结点，计算分数
        ++leafNum;

        t0 = clock();
        int score = evaluate(board);
        t1 = clock();
        evaluateTime += (double)(t1 - t0) / CLOCKS_PER_SEC;
//        printf("leaf node score: %d\n", score);
        return score;
    }
    int minMaxScore;
    t0 = clock();
    int num = pickPoint(board, side, width, candidate);
    t1 = clock();
    pickTime += (double)(t1 - t0) / CLOCKS_PER_SEC;
//    for (int i = 0; i < num; ++i) {
//        printf("(%d,%d) ", candidate[i].x, candidate[i].y);
//    }
//    printf("\n");
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
                ++pruningNum;
//                for (int i = 0; i < maxDepth - depth; ++i) {
//                    printf("\t");
//                }
//                printf("pruning score: %d\n", minMaxScore);
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
//    for (int i = 0; i < maxDepth - depth; ++i) {
//        printf("\t");
//    }
//    printf("return score: %d\n", minMaxScore);
    return minMaxScore;
}

//int iterativeDeepening(int **board, int *x, int *y, int maxDepth, int width) {
//    for (int depth = 0; depth <= maxDepth; ++depth) {
//        int score = minMaxSearch(board, &x, &y, depth, depth, width, 0, 0);
//
//    }
//
//}

