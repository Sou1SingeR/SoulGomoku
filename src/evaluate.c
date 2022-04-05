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
}



