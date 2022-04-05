
#include "search.h"

int minMaxSearch(int board[BOARD_SIZE][BOARD_SIZE], int *x, int *y, int depth, int maxDepth, int width, int parentScore, int allowPruning) {
    int side = depth % 2 == 0 ? SELF : OP;
    Coord candidate[20];
    if (side == SELF && searchToFivePoint(board, SELF, candidate)) {
        // 己方胜利
        if (depth == maxDepth) {
            *x = candidate[0].x;
            *y = candidate[0].y;
        }
        return 100000000;
    }
    if (side == OP && searchToFivePoint(board, OP, candidate)) {
        // 对方胜利
        if (depth == maxDepth) {
            *x = candidate[0].x;
            *y = candidate[0].y;
        }
        return -100000000;
    }
    if (side == SELF && searchToFourPoint(board, SELF, candidate)) {
        // 己方活四必胜
        if (depth == maxDepth) {
            *x = candidate[0].x;
            *y = candidate[0].y;
        }
        return 100000000;
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

