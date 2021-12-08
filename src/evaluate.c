#include "evaluate.h"

//To Three参数
int map_3(enum ChessType chessMap[MAP_SIZE][MAP_SIZE], int x, int map3[MAP_SIZE][MAP_SIZE]) {
    int i, j, k, i1, j1, k1, i2, j2, k2;
    int i0, j0, max = 0;
    for (i = 0; i < MAP_SIZE; i++) {
        for (j = 0; j < MAP_SIZE; j++) {
            map3[i][j] = 0;
        }
    }
    //竖线搜索
    i0 = 1;
    j0 = 0;
    for (i = 0; i < MAP_SIZE; i++) {
        for (j = 0; j < MAP_SIZE; j++) {
            if (chessMap[i][j] != EMPTY) {
                continue;
            }
            for (i1 = i - i0 * 3, j1 = j - j0 * 3, k1 = 0; k1 < 4; i1 += i0, j1 += j0, k1++) {
                int mE = 0, mX = 0, f = 0;
                for (i2 = i1, j2 = j1, k2 = 0; k2 < 4; i2 += i0, j2 += j0, k2++) {
                    if (i2 < 1 || j2 < 1 || i2 > MAP_SIZE - 2 || j2 > MAP_SIZE - 2) {
                        f = 1;
                        break;
                    }
                    if (chessMap[i2][j2] == EMPTY) {
                        mE++;
                    } else if (chessMap[i2][j2] == x) {
                        mX++;
                    }
                }
                if (f == 1) {
                    continue;
                }
                if (mE == 2 && mX == 2 && chessMap[i1 - i0][j1 - j0] == EMPTY &&
                    chessMap[i1 + i0 * 4][j1 + j0 * 4] == EMPTY) {
                    map3[i][j]++;
                    break;
                }
            }
        }
    }
    //横线搜索
    i0 = 0;
    j0 = 1;
    for (i = 0; i < MAP_SIZE; i++) {
        for (j = 0; j < MAP_SIZE; j++) {
            if (chessMap[i][j] != EMPTY) {
                continue;
            }
            for (i1 = i - i0 * 3, j1 = j - j0 * 3, k1 = 0; k1 < 4; i1 += i0, j1 += j0, k1++) {
                int mE = 0, mX = 0, f = 0;
                for (i2 = i1, j2 = j1, k2 = 0; k2 < 4; i2 += i0, j2 += j0, k2++) {
                    if (i2 < 1 || j2 < 1 || i2 > MAP_SIZE - 2 || j2 > MAP_SIZE - 2) {
                        f = 1;
                        break;
                    }
                    if (chessMap[i2][j2] == EMPTY) {
                        mE++;
                    } else if (chessMap[i2][j2] == x) {
                        mX++;
                    }
                }
                if (f == 1) {
                    continue;
                }
                if (mE == 2 && mX == 2 && chessMap[i1 - i0][j1 - j0] == EMPTY &&
                    chessMap[i1 + i0 * 4][j1 + j0 * 4] == EMPTY) {
                    map3[i][j]++;
                    break;
                }
            }
        }
    }
    //反斜线搜索
    i0 = 1;
    j0 = 1;
    for (i = 0; i < MAP_SIZE; i++) {
        for (j = 0; j < MAP_SIZE; j++) {
            if (chessMap[i][j] != EMPTY) {
                continue;
            }
            for (i1 = i - i0 * 3, j1 = j - j0 * 3, k1 = 0; k1 < 4; i1 += i0, j1 += j0, k1++) {
                int mE = 0, mX = 0, f = 0;
                for (i2 = i1, j2 = j1, k2 = 0; k2 < 4; i2 += i0, j2 += j0, k2++) {
                    if (i2 < 1 || j2 < 1 || i2 > MAP_SIZE - 2 || j2 > MAP_SIZE - 2) {
                        f = 1;
                        break;
                    }
                    if (chessMap[i2][j2] == EMPTY) {
                        mE++;
                    } else if (chessMap[i2][j2] == x) {
                        mX++;
                    }
                }
                if (f == 1) {
                    continue;
                }
                if (mE == 2 && mX == 2 && chessMap[i1 - i0][j1 - j0] == EMPTY &&
                    chessMap[i1 + i0 * 4][j1 + j0 * 4] == EMPTY) {
                    map3[i][j]++;
                    break;
                }
            }
        }
    }
    //正斜线搜索
    i0 = -1;
    j0 = 1;
    for (i = 0; i < MAP_SIZE; i++) {
        for (j = 0; j < MAP_SIZE; j++) {
            if (chessMap[i][j] != EMPTY) {
                continue;
            }
            for (i1 = i - i0 * 3, j1 = j - j0 * 3, k1 = 0; k1 < 4; i1 += i0, j1 += j0, k1++) {
                int mE = 0, mX = 0, f = 0;
                for (i2 = i1, j2 = j1, k2 = 0; k2 < 4; i2 += i0, j2 += j0, k2++) {
                    if (i2 < 1 || j2 < 1 || i2 > MAP_SIZE - 2 || j2 > MAP_SIZE - 2) {
                        f = 1;
                        break;
                    }
                    if (chessMap[i2][j2] == EMPTY) {
                        mE++;
                    } else if (chessMap[i2][j2] == x) {
                        mX++;
                    }
                }
                if (f == 1) {
                    continue;
                }
                if (mE == 2 && mX == 2 && chessMap[i1 - i0][j1 - j0] == EMPTY &&
                    chessMap[i1 + i0 * 4][j1 + j0 * 4] == EMPTY) {
                    map3[i][j]++;
                    break;
                }
            }
        }
    }
    for (i = 0; i < MAP_SIZE; i++) {
        for (j = 0; j < MAP_SIZE; j++) {
            if (map3[i][j] > max) {
                max = map3[i][j];
            }
        }
    }
    return max;
}

//To Four参数
int map_4(enum ChessType chessMap[MAP_SIZE][MAP_SIZE], int x, int map4[MAP_SIZE][MAP_SIZE]) {
    int i, j, k, i1, j1, k1, i2, j2, k2;
    int i0, j0, max = 0;
    for (i = 0; i < MAP_SIZE; i++) {
        for (j = 0; j < MAP_SIZE; j++) {
            map4[i][j] = 0;
        }
    }
    //竖线搜索
    i0 = 1;
    j0 = 0;
    for (i = 0; i < MAP_SIZE; i++) {
        for (j = 0; j < MAP_SIZE; j++) {
            if (chessMap[i][j] != EMPTY) {
                continue;
            }
            for (i1 = i - i0 * 4, j1 = j - j0 * 4, k1 = 0; k1 < 5; i1 += i0, j1 += j0, k1++) {
                int mE = 0, mX = 0;
                for (i2 = i1, j2 = j1, k2 = 0; k2 < 5; i2 += i0, j2 += j0, k2++) {
                    if (i2 < 0 || j2 < 0 || i2 > MAP_SIZE - 1 || j2 > MAP_SIZE - 1) {
                        break;
                    }
                    if (chessMap[i2][j2] == EMPTY) {
                        mE++;
                    } else if (chessMap[i2][j2] == x) {
                        mX++;
                    }
                }
                if (mE == 2 && mX == 3) {
                    map4[i][j]++;
                    break;
                }
            }
        }
    }
    //横线搜索
    i0 = 0;
    j0 = 1;
    for (i = 0; i < MAP_SIZE; i++) {
        for (j = 0; j < MAP_SIZE; j++) {
            if (chessMap[i][j] != EMPTY) {
                continue;
            }
            for (i1 = i - i0 * 4, j1 = j - j0 * 4, k1 = 0; k1 < 5; i1 += i0, j1 += j0, k1++) {
                int mE = 0, mX = 0;
                for (i2 = i1, j2 = j1, k2 = 0; k2 < 5; i2 += i0, j2 += j0, k2++) {
                    if (i2 < 0 || j2 < 0 || i2 > MAP_SIZE - 1 || j2 > MAP_SIZE - 1) {
                        break;
                    }
                    if (chessMap[i2][j2] == EMPTY) {
                        mE++;
                    } else if (chessMap[i2][j2] == x) {
                        mX++;
                    }
                }
                if (mE == 2 && mX == 3) {
                    map4[i][j]++;
                    break;
                }
            }
        }
    }
    //反斜线搜索
    i0 = 1;
    j0 = 1;
    for (i = 0; i < MAP_SIZE; i++) {
        for (j = 0; j < MAP_SIZE; j++) {
            if (chessMap[i][j] != EMPTY) {
                continue;
            }
            for (i1 = i - i0 * 4, j1 = j - j0 * 4, k1 = 0; k1 < 5; i1 += i0, j1 += j0, k1++) {
                int mE = 0, mX = 0;
                for (i2 = i1, j2 = j1, k2 = 0; k2 < 5; i2 += i0, j2 += j0, k2++) {
                    if (i2 < 0 || j2 < 0 || i2 > MAP_SIZE - 1 || j2 > MAP_SIZE - 1) {
                        break;
                    }
                    if (chessMap[i2][j2] == EMPTY) {
                        mE++;
                    } else if (chessMap[i2][j2] == x) {
                        mX++;
                    }
                }
                if (mE == 2 && mX == 3) {
                    map4[i][j]++;
                    break;
                }
            }
        }
    }
    //正斜线搜索
    i0 = -1;
    j0 = 1;
    for (i = 0; i < MAP_SIZE; i++) {
        for (j = 0; j < MAP_SIZE; j++) {
            if (chessMap[i][j] != EMPTY) {
                continue;
            }
            for (i1 = i - i0 * 4, j1 = j - j0 * 4, k1 = 0; k1 < 5; i1 += i0, j1 += j0, k1++) {
                int mE = 0, mX = 0;
                for (i2 = i1, j2 = j1, k2 = 0; k2 < 5; i2 += i0, j2 += j0, k2++) {
                    if (i2 < 0 || j2 < 0 || i2 > MAP_SIZE - 1 || j2 > MAP_SIZE - 1) {
                        break;
                    }
                    if (chessMap[i2][j2] == EMPTY) {
                        mE++;
                    } else if (chessMap[i2][j2] == x) {
                        mX++;
                    }
                }
                if (mE == 2 && mX == 3) {
                    map4[i][j]++;
                    break;
                }
            }
        }
    }
    for (i = 0; i < MAP_SIZE; i++) {
        for (j = 0; j < MAP_SIZE; j++) {
            if (map4[i][j] > max) {
                max = map4[i][j];
            }
        }
    }
    return max;
}

//valueD表
int table_B(enum ChessType str[4], int x) {
    if (x == 0) {
        if (str[0] == BLACK && str[1] == BLACK && str[2] == BLACK)//BBB-100
            return 100;
        if (str[0] == BLACK && str[1] == BLACK && str[2] == EMPTY && str[3] == BLACK)//BBEB-100
            return 100;
        if (str[0] == BLACK && str[1] == EMPTY && str[2] == BLACK && str[3] == BLACK)//BEBB-100
            return 100;
        if (str[0] == EMPTY && str[1] == BLACK && str[2] == BLACK && str[3] == BLACK)//EBBB-100
            return 100;
        if (str[0] == BLACK && str[1] == BLACK && str[2] == EMPTY)//BBE-100
            return 100;
        if (str[0] == BLACK && str[1] == EMPTY && str[2] == BLACK && str[3] == EMPTY)//BEBE-90
            return 90;
        if (str[0] == EMPTY && str[1] == BLACK && str[2] == BLACK && str[3] == EMPTY)//EBBE-55
            return 55;
        if (str[0] == EMPTY && str[1] == BLACK && str[2] == BLACK && str[3] == WHITE)//EBBW-30
            return 30;
        if (str[0] == BLACK && str[1] == EMPTY && str[2] == BLACK && str[3] == WHITE)//BEBW-30
            return 30;
        if (str[0] == BLACK && str[1] == EMPTY)//BE-20
            return 20;
        if (str[0] == EMPTY && str[1] == BLACK && str[2] == EMPTY)//EBE-10
            return 10;
    }
    if (x == 1) {
        if (str[0] == WHITE && str[1] == WHITE && str[2] == WHITE)//WWW-100
            return 100;
        if (str[0] == WHITE && str[1] == WHITE && str[2] == EMPTY && str[3] == WHITE)//WWEW-100
            return 100;
        if (str[0] == WHITE && str[1] == EMPTY && str[2] == WHITE && str[3] == WHITE)//WEWW-100
            return 100;
        if (str[0] == EMPTY && str[1] == WHITE && str[2] == WHITE && str[3] == WHITE)//EWWW-100
            return 100;
        if (str[0] == WHITE && str[1] == WHITE && str[2] == EMPTY)//WWE-100
            return 100;
        if (str[0] == WHITE && str[1] == EMPTY && str[2] == WHITE && str[3] == EMPTY)//WEWE-90
            return 90;
        if (str[0] == EMPTY && str[1] == WHITE && str[2] == WHITE && str[3] == EMPTY)//EWWE-55
            return 55;
        if (str[0] == EMPTY && str[1] == WHITE && str[2] == WHITE && str[3] == BLACK)//EWWB-30
            return 30;
        if (str[0] == WHITE && str[1] == EMPTY && str[2] == WHITE && str[3] == BLACK)//WEWB-30
            return 30;
        if (str[0] == WHITE && str[1] == EMPTY)//WE-20
            return 20;
        if (str[0] == EMPTY && str[1] == WHITE && str[2] == EMPTY)//EWE-10
            return 10;
    }
    return 0;
}

//valueA表
int table_A(enum ChessType str[4], int x) {
    if (x == 0) {
        if (str[0] == EMPTY && str[1] == WHITE && str[2] == WHITE && str[3] == BLACK)//EWWB-100
            return 100;
        if (str[0] == WHITE && str[1] == EMPTY && str[2] == WHITE && str[3] == BLACK)//WEWB-100
            return 100;
        if (str[0] == WHITE && str[1] == WHITE && str[2] == EMPTY)//WWE-100
            return 100;
        if (str[0] == WHITE && str[1] == EMPTY && str[2] == WHITE && str[3] == EMPTY)//WEWE-90
            return 90;
        if (str[0] == EMPTY && str[1] == WHITE && str[2] == WHITE && str[3] == EMPTY)//EWWE-90
            return 90;
        if (str[0] == WHITE && str[1] == EMPTY)//WE-80
            return 80;
        if (str[0] == EMPTY && str[1] == WHITE && str[2] == EMPTY)//EWE-85
            return 85;
        if (str[0] == EMPTY && str[1] == EMPTY && str[2] == WHITE && str[3] == EMPTY)//EEWE-75
            return 75;
    }
    if (x == 1) {
        if (str[0] == EMPTY && str[1] == BLACK && str[2] == BLACK && str[3] == WHITE)//EBBW-100
            return 100;
        if (str[0] == BLACK && str[1] == EMPTY && str[2] == BLACK && str[3] == WHITE)//BEBW-100
            return 100;
        if (str[0] == BLACK && str[1] == BLACK && str[2] == EMPTY)//BBE-100
            return 100;
        if (str[0] == BLACK && str[1] == EMPTY && str[2] == BLACK && str[3] == EMPTY)//BEBE-90
            return 90;
        if (str[0] == EMPTY && str[1] == BLACK && str[2] == BLACK && str[3] == EMPTY)//EBBE-90
            return 90;
        if (str[0] == BLACK && str[1] == EMPTY)//BE-80
            return 80;
        if (str[0] == EMPTY && str[1] == BLACK && str[2] == EMPTY)//EBE-85
            return 85;
        if (str[0] == EMPTY && str[1] == EMPTY && str[2] == BLACK && str[3] == EMPTY)//EEBE-75
            return 75;
    }
    return 0;

}

//valueD计算
void value_B(enum ChessType chessMap[MAP_SIZE][MAP_SIZE], int x, int valueMap[MAP_SIZE][MAP_SIZE]) {
    int p;
    memset(valueMap, 0, sizeof(int) * MAP_SIZE * MAP_SIZE);
    enum ChessType str[4] = {EMPTY};
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (i - 1 >= 0) {
                if (j - 1 >= 0 && chessMap[i - 1][j - 1] != EMPTY) {//存在1点并一点不为空
                    for (p = 0; p < 4; p++) {
                        if ((i - 1 - p) < 0 || (j - 1 - p) < 0)break;
                        str[p] = chessMap[i - 1 - p][j - 1 - p];
                    }
                    valueMap[i][j] += table_B(str, x);//累计叠加防守值
                    memset(str, EMPTY, sizeof(str));
                }
                if (chessMap[i - 1][j] != EMPTY) {//2点存在并不为空
                    for (p = 0; p < 4; p++) {
                        if ((i - 1 - p) < 0)break;
                        str[p] = chessMap[i - 1 - p][j];
                    }
                    valueMap[i][j] += table_B(str, x);//累计叠加防守值
                    memset(str, EMPTY, sizeof(str));
                }
                if (j + 1 < MAP_SIZE && chessMap[i - 1][j + 1] != EMPTY) {//3点存在并不为空
                    for (p = 0; p < 4; p++) {
                        if ((i - 1 - p) < 0 || (j + 1 + p) > MAP_SIZE - 1)break;
                        str[p] = chessMap[i - 1 - p][j + 1 + p];
                    }
                    valueMap[i][j] += table_B(str, x);//累计叠加防守值
                    memset(str, EMPTY, sizeof(str));
                }
            }
            if (j + 1 < MAP_SIZE) {
                if (chessMap[i][j + 1] != EMPTY) {//4点存在并不为空
                    for (p = 0; p < 4; p++) {
                        if ((j + 1 + p) > MAP_SIZE - 1)break;
                        str[p] = chessMap[i][j + 1 + p];
                    }
                    valueMap[i][j] += table_B(str, x);//累计叠加防守值
                    memset(str, EMPTY, sizeof(str));
                }
                if (i + 1 < MAP_SIZE && chessMap[i + 1][j + 1] != EMPTY) {//5点存在并不为空
                    for (p = 0; p < 4; p++) {
                        if ((i + 1 + p) > MAP_SIZE - 1 || (j + 1 + p) > MAP_SIZE - 1)break;
                        str[p] = chessMap[i + 1 + p][j + 1 + p];
                    }
                    valueMap[i][j] += table_B(str, x);//累计叠加防守值
                    memset(str, EMPTY, sizeof(str));
                }
            }
            if (i + 1 < MAP_SIZE) {
                if (chessMap[i + 1][j] != EMPTY) {//6点存在并不为空
                    for (p = 0; p < 4; p++) {
                        if ((i + 1 + p) > MAP_SIZE - 1)break;
                        str[p] = chessMap[i + 1 + p][j];
                    }
                    valueMap[i][j] += table_B(str, x);//累计叠加防守值
                    memset(str, EMPTY, sizeof(str));
                }
                if (j - 1 >= 0 && chessMap[i + 1][j - 1] != EMPTY) {//7点存在并不为空
                    for (p = 0; p < 4; p++) {
                        if ((j - 1 - p) < 0 || (i + 1 + p) > MAP_SIZE - 1)break;
                        str[p] = chessMap[i + 1 + p][j - 1 - p];
                    }
                    valueMap[i][j] += table_B(str, x);//累计叠加防守值
                    memset(str, EMPTY, sizeof(str));
                }
            }
            if (j - 1 >= 0 && chessMap[i][j - 1] != EMPTY) {
                for (p = 0; p < 4; p++) {//反向探索
                    if ((j - 1 - p) < 0)break;
                    str[p] = chessMap[i][j - 1 - p];
                }
                valueMap[i][j] += table_B(str, x);//累计叠加防守值
                memset(str, EMPTY, sizeof(str));
            }
        }
    }
}

//valueA计算
void value_A(enum ChessType chessMap[MAP_SIZE][MAP_SIZE], int x, int valueMap[MAP_SIZE][MAP_SIZE]) {
    int p;
    memset(valueMap, 0, sizeof(int) * MAP_SIZE * MAP_SIZE);
    enum ChessType str[4] = {EMPTY};
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (i - 1 >= 0) {
                if (j - 1 >= 0 && chessMap[i - 1][j - 1] == EMPTY) {//存在1点并一点为空
                    for (p = 0; p < 4; p++) {//反向探索
                        if ((i + 1 + p) > MAP_SIZE - 1 || (j + 1 + p) > MAP_SIZE - 1)break;
                        str[p] = chessMap[i + 1 + p][j + 1 + p];
                    }
                    valueMap[i][j] += table_A(str, x);//累计叠加攻击值
                    memset(str, EMPTY, sizeof(str));
                }
                if (chessMap[i - 1][j] == EMPTY) {//2点存在并为空
                    for (p = 0; p < 4; p++) {//反向探索
                        if ((i + 1 + p) > MAP_SIZE - 1)break;
                        str[p] = chessMap[i + 1 + p][j];
                    }
                    valueMap[i][j] += table_A(str, x);//累计叠加攻击值
                    memset(str, EMPTY, sizeof(str));
                }
                if (j + 1 < MAP_SIZE && chessMap[i - 1][j + 1] == EMPTY) {//3点存在并为空
                    for (p = 0; p < 4; p++) {//反向探索
                        if ((i + 1 + p) > MAP_SIZE - 1 || (j - 1 - p) < 0)break;
                        str[p] = chessMap[i + 1 + p][j - 1 - p];
                    }
                    valueMap[i][j] += table_A(str, x);//累计叠加攻击值
                    memset(str, EMPTY, sizeof(str));
                }
            }
            if (j + 1 < MAP_SIZE) {
                if (chessMap[i][j + 1] == EMPTY) {//4点存在并为空
                    for (p = 0; p < 4; p++) {//反向探索
                        if ((j - 1 - p) < 0)break;
                        str[p] = chessMap[i][j - 1 - p];
                    }
                    valueMap[i][j] += table_A(str, x);//累计叠加攻击值
                    memset(str, EMPTY, sizeof(str));
                }
                if (i + 1 < MAP_SIZE && chessMap[i + 1][j + 1] == EMPTY) {//5点存在并为空
                    for (p = 0; p < 4; p++) {//反向探索
                        if ((i - 1 - p) < 0 || (j - 1 - p) < 0)break;
                        str[p] = chessMap[i - 1 - p][j - 1 - p];
                    }
                    valueMap[i][j] += table_A(str, x);//累计叠加攻击值
                    memset(str, EMPTY, sizeof(str));
                }
            }
            if (i + 1 < MAP_SIZE) {
                if (chessMap[i + 1][j] == EMPTY) {//6点存在并为空
                    for (p = 0; p < 4; p++) {//反向探索
                        if ((i - 1 - p) < 0)break;
                        str[p] = chessMap[i - 1 - p][j];
                    }
                    valueMap[i][j] += table_A(str, x);//累计叠加攻击值
                    memset(str, EMPTY, sizeof(str));
                }
                if (j - 1 >= 0 && chessMap[i + 1][j - 1] == EMPTY) {//7点存在并为空
                    for (p = 0; p < 4; p++) {//反向探索
                        if ((i - 1 - p) < 0 || (j + 1 + p) > MAP_SIZE - 1)break;
                        str[p] = chessMap[i - 1 - p][j + 1 + p];
                    }
                    valueMap[i][j] += table_A(str, x);//累计叠加攻击值
                    memset(str, EMPTY, sizeof(str));
                }
            }
            if (j - 1 >= 0 && chessMap[i][j - 1] == EMPTY) {
                for (p = 0; p < 4; p++) {//反向探索
                    if ((j + 1 + p) > MAP_SIZE - 1)break;
                    str[p] = chessMap[i][j + 1 + p];
                }
                valueMap[i][j] += table_A(str, x);//累计叠加攻击值
                memset(str, EMPTY, sizeof(str));
            }
        }
    }
}

/* Function: 构建大顶堆 */
void BuildMaxHeap(Point *heap, int len) {
    int i;
    Point temp;

    for (i = len / 2 - 1; i >= 0; i--) {
        if ((2 * i + 1) < len && heap[i].value < heap[2 * i + 1].value)    /* 根节点大于左子树 */
        {
            temp = heap[i];
            heap[i] = heap[2 * i + 1];
            heap[2 * i + 1] = temp;
            /* 检查交换后的左子树是否满足大顶堆性质 如果不满足 则重新调整子树结构 */
            if ((2 * (2 * i + 1) + 1 < len && heap[2 * i + 1].value < heap[2 * (2 * i + 1) + 1].value) ||
                (2 * (2 * i + 1) + 2 < len && heap[2 * i + 1].value < heap[2 * (2 * i + 1) + 2].value)) {
                BuildMaxHeap(heap, len);
            }
        }
        if ((2 * i + 2) < len && heap[i].value < heap[2 * i + 2].value)    /* 根节点大于右子树 */
        {
            temp = heap[i];
            heap[i] = heap[2 * i + 2];
            heap[2 * i + 2] = temp;
            /* 检查交换后的右子树是否满足大顶堆性质 如果不满足 则重新调整子树结构 */
            if ((2 * (2 * i + 2) + 1 < len && heap[2 * i + 2].value < heap[2 * (2 * i + 2) + 1].value) ||
                (2 * (2 * i + 2) + 2 < len && heap[2 * i + 2].value < heap[2 * (2 * i + 2) + 2].value)) {
                BuildMaxHeap(heap, len);
            }
        }
    }
}

/* Function: 交换交换根节点和数组末尾元素的值*/
void Swap(Point *heap, int len) {
    Point temp;
    temp = heap[0];
    heap[0] = heap[len - 1];
    heap[len - 1] = temp;
}

int min(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

// 下一步落子位置
int findTheBest(enum ChessType chessMap[MAP_SIZE][MAP_SIZE], int expectedLen, Point *points) {
    int i, j, k;
    int n = 1;
    int mW, mE, mB;  //白子数，黑子数和空格数
    int mQ;
    int x, y;
    int row, col;
    int Map0[MAP_SIZE][MAP_SIZE];   //战术地图

    //计算当前手数
    for (
            i = 0;
            i < MAP_SIZE;
            i++) {
        for (
                j = 0;
                j < MAP_SIZE;
                j++) {
            if (chessMap[i][j] != EMPTY) {
                n++;
            }
        }
    }

    if (n == 1) {
        row = MAP_SIZE / 2;
        col = MAP_SIZE / 2;
        points[0].x = MAP_SIZE / 2;
        points[0].y = MAP_SIZE / 2;
        return 1;
    }

//    if (n == 3) {
//        int x1, y1, x2, y2, x0, y0, x, y, flag;
//        int rand0, randx[3], randy[3];  //备选项
//        x1 = MAP_SIZE / 2;
//        y1 = MAP_SIZE / 2;
//        //寻找第二手位置
//        flag = 0;
//        for (
//                i = 0;
//                i < MAP_SIZE;
//                i++) {
//            for (
//                    j = 0;
//                    j < MAP_SIZE;
//                    j++) {
//                if (chessMap[i][j] == BLACK) {
//                    x2 = i;
//                    y2 = j;
//                    flag = 1;
//                    break;
//                }
//            }
//            if (flag == 1) {
//                break;
//            }
//        }
////阴防应对
//        if (x2 == MAP_SIZE / 2 - 1 && y2 == MAP_SIZE / 2 - 1 || x2 == MAP_SIZE / 2 + 1 && y2 == MAP_SIZE / 2 + 1) {
//            randx[0] = MAP_SIZE / 2 - 1;
//            randy[0] = MAP_SIZE / 2 + 1;
//            randx[1] = MAP_SIZE / 2 + 1;
//            randy[1] = MAP_SIZE / 2 - 1;
//            rand0 = random(2);
//            row = randx[rand0];
//            col = randy[rand0];
//            return;
//        }
//        if (x2 == MAP_SIZE / 2 - 1 && y2 == MAP_SIZE / 2 + 1 || x2 == MAP_SIZE / 2 + 1 && y2 == MAP_SIZE / 2 - 1) {
//            randx[0] = MAP_SIZE / 2 - 1;
//            randy[0] = MAP_SIZE / 2 - 1;
//            randx[1] = MAP_SIZE / 2 + 1;
//            randy[1] = MAP_SIZE / 2 + 1;
//            rand0 = random(2);
//            row = randx[rand0];
//            col = randy[rand0];
//            return;
//        }
////阳防应对
//        if (x2 == MAP_SIZE / 2 && y2 == MAP_SIZE / 2 - 1) {
//            randx[0] = MAP_SIZE / 2 - 1;
//            randy[0] = MAP_SIZE / 2 + 1;
//            randx[1] = MAP_SIZE / 2 + 1;
//            randy[1] = MAP_SIZE / 2 + 1;
//            rand0 = random(2);
//            row = randx[rand0];
//            col = randy[rand0];
//            return;
//        }
//        if (x2 == MAP_SIZE / 2 + 1 && y2 == MAP_SIZE / 2) {
//            randx[0] = MAP_SIZE / 2 - 1;
//            randy[0] = MAP_SIZE / 2 - 1;
//            randx[1] = MAP_SIZE / 2 - 1;
//            randy[1] = MAP_SIZE / 2 + 1;
//            rand0 = random(2);
//            row = randx[rand0];
//            col = randy[rand0];
//            return;
//        }
//        if (x2 == MAP_SIZE / 2 && y2 == MAP_SIZE / 2 + 1) {
//            randx[0] = MAP_SIZE / 2 - 1;
//            randy[0] = MAP_SIZE / 2 - 1;
//            randx[1] = MAP_SIZE / 2 + 1;
//            randy[1] = MAP_SIZE / 2 - 1;
//            rand0 = random(2);
//            row = randx[rand0];
//            col = randy[rand0];
//            return;
//        }
//        if (x2 == MAP_SIZE / 2 - 1 && y2 == MAP_SIZE / 2) {
//            randx[0] = MAP_SIZE / 2 + 1;
//            randy[0] = MAP_SIZE / 2 - 1;
//            randx[1] = MAP_SIZE / 2 + 1;
//            randy[1] = MAP_SIZE / 2 + 1;
//            rand0 = random(2);
//            row = randx[rand0];
//            col = randy[rand0];
//            return;
//        }
//        x0 = x1 - x2;
//        y0 = y1 - y2;
//        if (x0 >= 0) {
//            x = 1;
//        } else {
//            x = -1;
//        }
//        if (y0 >= 0) {
//            y = 1;
//        } else {
//            y = -1;
//        }
//        row = MAP_SIZE / 2 + x;
//        col = MAP_SIZE / 2 + y;
//        return;
//    }

//己方冲四搜索
//竖线搜索
    for (
            i = 0;
            i < MAP_SIZE - 4; i++) {
        for (
                j = 0;
                j < MAP_SIZE; j++) {
            mW = 0;
            mE = 0;
            for (
                    k = i;
                    k < i + 5; k++) {
                if (chessMap[k][j] == WHITE) {
                    mW++;
                } else if (chessMap[k][j] == EMPTY) {
                    mE++;
                    x = k;
                    y = j;
                }
            }
            if (mW == 4 && mE == 1) {
                points[0].x = x;
                points[0].y = y;
                return 1;
            }
        }
    }
//横线搜索
    for (
            i = 0;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 4; j++) {
            mW = 0;
            mE = 0;
            for (
                    k = j;
                    k < j + 5; k++) {
                if (chessMap[i][k] == WHITE) {
                    mW++;
                } else if (chessMap[i][k] == EMPTY) {
                    mE++;
                    x = i;
                    y = k;
                }
            }
            if (mW == 4 && mE == 1) {
                points[0].x = x;
                points[0].y = y;
                return 1;
            }
        }
    }
//反斜线搜索
    for (
            i = 0;
            i < MAP_SIZE - 4; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 4; j++) {
            mW = 0;
            mE = 0;
            for (
                    k = 0;
                    k < 5; k++) {
                if (chessMap[i + k][j + k] == WHITE) {
                    mW++;
                } else if (chessMap[i + k][j + k] == EMPTY) {
                    mE++;
                    x = i + k;
                    y = j + k;
                }
            }
            if (mW == 4 && mE == 1) {
                points[0].x = x;
                points[0].y = y;
                return 1;
            }
        }
    }
//正斜线搜索
    for (
            i = 4;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 4; j++) {
            mW = 0;
            mE = 0;
            for (
                    k = 0;
                    k < 5; k++) {
                if (chessMap[i - k][j + k] == WHITE) {
                    mW++;
                } else if (chessMap[i - k][j + k] == EMPTY) {
                    mE++;
                    x = i - k;
                    y = j + k;
                }
            }
            if (mW == 4 && mE == 1) {
                points[0].x = x;
                points[0].y = y;
                return 1;
            }
        }
    }
//对方冲四搜索
//竖线搜索
    for (
            i = 0;
            i < MAP_SIZE - 4; i++) {
        for (
                j = 0;
                j < MAP_SIZE; j++) {
            mB = 0;
            mE = 0;
            for (
                    k = i;
                    k < i + 5; k++) {
                if (chessMap[k][j] == BLACK) {
                    mB++;
                } else if (chessMap[k][j] == EMPTY) {
                    mE++;
                    x = k;
                    y = j;
                }
            }
            if (mB == 4 && mE == 1) {
                points[0].x = x;
                points[0].y = y;
                return 1;
            }
        }
    }
//横线搜索
    for (
            i = 0;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 4; j++) {
            mB = 0;
            mE = 0;
            for (
                    k = j;
                    k < j + 5; k++) {
                if (chessMap[i][k] == BLACK) {
                    mB++;
                } else if (chessMap[i][k] == EMPTY) {
                    mE++;
                    x = i;
                    y = k;
                }
            }
            if (mB == 4 && mE == 1) {
                points[0].x = x;
                points[0].y = y;
                return 1;
            }
        }
    }
//反斜线搜索
    for (
            i = 0;
            i < MAP_SIZE - 4; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 4; j++) {
            mB = 0;
            mE = 0;
            for (
                    k = 0;
                    k < 5; k++) {
                if (chessMap[i + k][j + k] == BLACK) {
                    mB++;
                } else if (chessMap[i + k][j + k] == EMPTY) {
                    mE++;
                    x = i + k;
                    y = j + k;
                }
            }
            if (mB == 4 && mE == 1) {
                points[0].x = x;
                points[0].y = y;
                return 1;
            }
        }
    }
//正斜线搜索
    for (
            i = 4;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 4; j++) {
            mB = 0;
            mE = 0;
            for (
                    k = 0;
                    k < 5; k++) {
                if (chessMap[i - k][j + k] == BLACK) {
                    mB++;
                } else if (chessMap[i - k][j + k] == EMPTY) {
                    mE++;
                    x = i - k;
                    y = j + k;
                }
            }
            if (mB == 4 && mE == 1) {
                points[0].x = x;
                points[0].y = y;
                return 1;
            }
        }
    }
//己方活三搜索
//竖线搜索
    for (
            i = 0;
            i < MAP_SIZE - 5; i++) {
        for (
                j = 0;
                j < MAP_SIZE; j++) {
            mW = 0;
            mE = 0;
            for (
                    k = i + 1;
                    k < i + 5; k++) {
                if (chessMap[k][j] == WHITE) {
                    mW++;
                } else if (chessMap[k][j] == EMPTY) {
                    mE++;
                    x = k;
                    y = j;
                }
            }
            if (mW == 3 && mE == 1 && chessMap[i][j] == EMPTY && chessMap[i + 5][j] == EMPTY) {
                points[0].x = x;
                points[0].y = y;
                return 1;
            }
        }
    }
//横线搜索
    for (
            i = 0;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mW = 0;
            mE = 0;
            for (
                    k = j + 1;
                    k < j + 5; k++) {
                if (chessMap[i][k] == WHITE) {
                    mW++;
                } else if (chessMap[i][k] == EMPTY) {
                    mE++;
                    x = i;
                    y = k;
                }
            }
            if (mW == 3 && mE == 1 && chessMap[i][j] == EMPTY && chessMap[i][j + 5] == EMPTY) {
                points[0].x = x;
                points[0].y = y;
                return 1;
            }
        }
    }
//反斜线搜索
    for (
            i = 0;
            i < MAP_SIZE - 5; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mW = 0;
            mE = 0;
            for (
                    k = 1;
                    k < 5; k++) {
                if (chessMap[i + k][j + k] == WHITE) {
                    mW++;
                } else if (chessMap[i + k][j + k] == EMPTY) {
                    mE++;
                    x = i + k;
                    y = j + k;
                }
            }
            if (mW == 3 && mE == 1 && chessMap[i][j] == EMPTY && chessMap[i + 5][j + 5] == EMPTY) {
                points[0].x = x;
                points[0].y = y;
                return 1;
            }
        }
    }
//正斜线搜索
    for (
            i = 5;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mW = 0;
            mE = 0;
            for (
                    k = 1;
                    k < 5; k++) {
                if (chessMap[i - k][j + k] == WHITE) {
                    mW++;
                } else if (chessMap[i - k][j + k] == EMPTY) {
                    mE++;
                    x = i - k;
                    y = j + k;
                }
            }
            if (mW == 3 && mE == 1 && chessMap[i][j] == EMPTY && chessMap[i - 5][j + 5] == EMPTY) {
                points[0].x = x;
                points[0].y = y;
                return 1;
            }
        }
    }

    int map4W[MAP_SIZE][MAP_SIZE];   //To Four参数-W
    map_4(chessMap,
          1, map4W);
    for (
            i = 0;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE; j++) {
            if (map4W[i][j] > 1) {
                points[0].x = i;
                points[0].y = j;
                return 1;
            }
        }
    }




//战术地图
//0-EMPTY
//1-WHITE
//2-BLACK
//3-WHITE冲四点

//地图复制
    for (
            i = 0;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE; j++) {
            if (chessMap[i][j] == EMPTY) {
                Map0[i][j] = 0;
            } else if (chessMap[i][j] == WHITE) {
                Map0[i][j] = 1;
            } else if (chessMap[i][j] == BLACK) {
                Map0[i][j] = 2;
            }
        }
    }
//搜索WHITE冲四点
//竖线搜索
    for (
            i = 0;
            i < MAP_SIZE - 4; i++) {
        for (
                j = 0;
                j < MAP_SIZE; j++) {
            mW = 0;
            mE = 0;
            for (
                    k = i;
                    k < i + 5; k++) {
                if (chessMap[k][j] == WHITE) {
                    mW++;
                } else if (chessMap[k][j] == EMPTY) {
                    mE++;
                }
            }
            if (mW == 3 && mE == 2) {
                for (
                        k = i;
                        k < i + 5; k++) {
                    if (chessMap[k][j] == EMPTY) {
                        Map0[k][j] = 3;
                    }
                }
            }
        }
    }
//横线搜索
    for (
            i = 0;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 4; j++) {
            mW = 0;
            mE = 0;
            for (
                    k = j;
                    k < j + 5; k++) {
                if (chessMap[i][k] == WHITE) {
                    mW++;
                } else if (chessMap[i][k] == EMPTY) {
                    mE++;
                }
            }
            if (mW == 3 && mE == 2) {
                for (
                        k = j;
                        k < j + 5; k++) {
                    if (chessMap[i][k] == EMPTY) {
                        Map0[i][k] = 3;
                    }
                }
            }
        }
    }
//反斜线搜索
    for (
            i = 0;
            i < MAP_SIZE - 4; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 4; j++) {
            mW = 0;
            mE = 0;
            for (
                    k = 0;
                    k < 5; k++) {
                if (chessMap[i + k][j + k] == WHITE) {
                    mW++;
                } else if (chessMap[i + k][j + k] == EMPTY) {
                    mE++;
                }
            }
            if (mW == 3 && mE == 2) {
                for (
                        k = 0;
                        k < 5; k++) {
                    if (chessMap[i + k][j + k] == EMPTY) {
                        Map0[i + k][j + k] = 3;
                    }
                }
            }
        }
    }
//正斜线搜索
    for (
            i = 4;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 4; j++) {
            mW = 0;
            mE = 0;
            for (
                    k = 0;
                    k < 5; k++) {
                if (chessMap[i - k][j + k] == WHITE) {
                    mW++;
                } else if (chessMap[i - k][j + k] == EMPTY) {
                    mE++;
                }
            }
            if (mW == 3 && mE == 2) {
                for (
                        k = 0;
                        k < 5; k++) {
                    if (chessMap[i - k][j + k] == EMPTY) {
                        Map0[i - k][j + k] = 3;
                    }
                }
            }
        }
    }

//搜索己方活三（1冲四点+2白子）
//竖线搜索
    for (
            i = 0;
            i < MAP_SIZE - 5; i++) {
        for (
                j = 0;
                j < MAP_SIZE; j++) {
            mW = 0;
            mE = 0;
            mQ = 0;   //用来表示白方冲四点数目
            for (
                    k = i + 1;
                    k < i + 5; k++) {
                if (Map0[k][j] == 1) {
                    mW++;
                } else if (chessMap[k][j] == EMPTY) {
                    mE++;
                }
                if (Map0[k][j] == 3) {
                    mQ++;
                }
            }
            if (mW == 2 && mE == 2 && mQ >= 1 && chessMap[i][j] == EMPTY && chessMap[i + 5][j] == EMPTY) {
//未判断黑方是否有反（冲四）————待改进
                for (
                        k = i + 1;
                        k < i + 5; k++) {
                    if (Map0[k][j] == 3) {
                        points[0].x = k;
                        points[0].y = j;
                        return 1;
                    }
                }
            }
        }
    }
//横线搜索
    for (
            i = 0;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mW = 0;
            mE = 0;
            mQ = 0;   //用来表示白方冲四点数目
            for (
                    k = j + 1;
                    k < j + 5; k++) {
                if (Map0[i][k] == 1) {
                    mW++;
                } else if (chessMap[i][k] == EMPTY) {
                    mE++;
                }
                if (Map0[i][k] == 3) {
                    mQ++;
                }
            }
            if (mW == 2 && mE == 2 && mQ >= 1 && chessMap[i][j] == EMPTY && chessMap[i][j + 5] == EMPTY) {
//未判断黑方是否有反（冲四）————待改进
                for (
                        k = j + 1;
                        k < j + 5; k++) {
                    if (Map0[i][k] == 3) {
                        points[0].x = i;
                        points[0].y = k;
                        return 1;
                    }
                }
            }
        }
    }
//反斜线搜索
    for (
            i = 0;
            i < MAP_SIZE - 5; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mW = 0;
            mE = 0;
            mQ = 0;   //用来表示白方冲四点数目
            for (
                    k = 1;
                    k < 5; k++) {
                if (Map0[i + k][j + k] == 1) {
                    mW++;
                } else if (chessMap[i + k][j + k] == EMPTY) {
                    mE++;
                }
                if (Map0[i + k][j + k] == 3) {
                    mQ++;
                }
            }
            if (mW == 2 && mE == 2 && mQ >= 1 && chessMap[i][j] == EMPTY && chessMap[i + 5][j + 5] == EMPTY) {
//未判断黑方是否有反（冲四）————待改进
                for (
                        k = 1;
                        k < 5; k++) {
                    if (Map0[i + k][j + k] == 3) {
                        points[0].x = i + k;
                        points[0].y = j + k;
                        return 1;
                    }
                }
            }
        }
    }
//正斜线搜索
    for (
            i = 5;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mW = 0;
            mE = 0;
            mQ = 0;   //用来表示白方冲四点数目
            for (
                    k = 1;
                    k < 5; k++) {
                if (Map0[i - k][j + k] == 1) {
                    mW++;
                } else if (chessMap[i - k][j + k] == EMPTY) {
                    mE++;
                }
                if (Map0[i - k][j + k] == 3) {
                    mQ++;
                }
            }
            if (mW == 2 && mE == 2 && mQ >= 1 && chessMap[i][j] == EMPTY && chessMap[i - 5][j + 5] == EMPTY) {
//未判断黑方是否有反（冲四）————待改进
                for (
                        k = 1;
                        k < 5; k++) {
                    if (Map0[i - k][j + k] == 3) {
                        points[0].x = i - k;
                        points[0].y = j + k;
                        return 1;
                    }
                }
            }
        }
    }
//搜索己方活三（2冲四点+1白子）
//竖线搜索
    for (
            i = 0;
            i < MAP_SIZE - 5; i++) {
        for (
                j = 0;
                j < MAP_SIZE; j++) {
            mW = 0;
            mE = 0;
            mQ = 0;   //用来表示白方冲四点数目
            for (
                    k = i + 1;
                    k < i + 5; k++) {
                if (Map0[k][j] == 1) {
                    mW++;
                } else if (chessMap[k][j] == EMPTY) {
                    mE++;
                }
                if (Map0[k][j] == 3) {
                    mQ++;
                }
            }
            if (mW == 1 && mE == 3 && mQ >= 2 && chessMap[i][j] == EMPTY && chessMap[i + 5][j] == EMPTY) {
//未判断黑方是否有反（冲四）————待改进
                for (
                        k = i + 1;
                        k < i + 5; k++) {
                    if (Map0[k][j] == 3) {
                        points[0].x = k;
                        points[0].y = j;
                        return 1;
                    }
                }
            }
        }
    }
//横线搜索
    for (
            i = 0;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mW = 0;
            mE = 0;
            mQ = 0;   //用来表示白方冲四点数目
            for (
                    k = j + 1;
                    k < j + 5; k++) {
                if (Map0[i][k] == 1) {
                    mW++;
                } else if (chessMap[i][k] == EMPTY) {
                    mE++;
                }
                if (Map0[i][k] == 3) {
                    mQ++;
                }
            }
            if (mW == 1 && mE == 3 && mQ >= 2 && chessMap[i][j] == EMPTY && chessMap[i][j + 5] == EMPTY) {
//未判断黑方是否有反（冲四）————待改进
                for (
                        k = i + 1;
                        k < i + 5; k++) {
                    if (Map0[i][k] == 3) {
                        points[0].x = i;
                        points[0].y = k;
                        return 1;
                    }
                }
            }
        }
    }
//反斜线搜索
    for (
            i = 0;
            i < MAP_SIZE - 5; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mW = 0;
            mE = 0;
            mQ = 0;   //用来表示白方冲四点数目
            for (
                    k = 1;
                    k < 5; k++) {
                if (Map0[i + k][j + k] == 1) {
                    mW++;
                } else if (chessMap[i + k][j + k] == EMPTY) {
                    mE++;
                }
                if (Map0[i + k][j + k] == 3) {
                    mQ++;
                }
            }
            if (mW == 1 && mE == 3 && mQ >= 2 && chessMap[i][j] == EMPTY && chessMap[i + 5][j + 5] == EMPTY) {
//未判断黑方是否有反（冲四）————待改进
                for (
                        k = 1;
                        k < 5; k++) {
                    if (Map0[i + k][j + k] == 3) {
                        points[0].x = i + k;
                        points[0].y = j + k;
                        return 1;
                    }
                }
            }
        }
    }
//正斜线搜索
    for (
            i = 5;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mW = 0;
            mE = 0;
            mQ = 0;   //用来表示白方冲四点数目
            for (
                    k = 1;
                    k < 5; k++) {
                if (Map0[i - k][j + k] == 1) {
                    mW++;
                } else if (chessMap[i - k][j + k] == EMPTY) {
                    mE++;
                }
                if (Map0[i - k][j + k] == 3) {
                    mQ++;
                }
            }
            if (mW == 1 && mE == 3 && mQ >= 2 && chessMap[i][j] == EMPTY && chessMap[i - 5][j + 5] == EMPTY) {
//未判断黑方是否有反（冲四）————待改进
                for (
                        k = 1;
                        k < 5; k++) {
                    if (Map0[i - k][j + k] == 3) {
                        points[0].x = i - k;
                        points[0].y = j + k;
                        return 1;
                    }
                }
            }
        }
    }
//搜索己方活三（3冲四点+0白子）
//竖线搜索
    for (
            i = 0;
            i < MAP_SIZE - 5; i++) {
        for (
                j = 0;
                j < MAP_SIZE; j++) {
            mW = 0;
            mE = 0;
            mQ = 0;   //用来表示白方冲四点数目
            for (
                    k = i + 1;
                    k < i + 5; k++) {
                if (Map0[k][j] == 1) {
                    mW++;
                } else if (chessMap[k][j] == EMPTY) {
                    mE++;
                }
                if (Map0[k][j] == 3) {
                    mQ++;
                }
            }
            if (mW == 0 && mE == 4 && mQ >= 3 && chessMap[i][j] == EMPTY && chessMap[i + 5][j] == EMPTY) {
//未判断黑方是否有反（冲四）————待改进
                for (
                        k = i + 1;
                        k < i + 5; k++) {
                    if (Map0[k][j] == 3) {
                        points[0].x = k;
                        points[0].y = j;
                        return 1;
                    }
                }
            }
        }
    }
//横线搜索
    for (
            i = 0;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mW = 0;
            mE = 0;
            mQ = 0;   //用来表示白方冲四点数目
            for (
                    k = j + 1;
                    k < j + 5; k++) {
                if (Map0[i][k] == 1) {
                    mW++;
                } else if (chessMap[i][k] == EMPTY) {
                    mE++;
                }
                if (Map0[i][k] == 3) {
                    mQ++;
                }
            }
            if (mW == 0 && mE == 4 && mQ >= 3 && chessMap[i][j] == EMPTY && chessMap[i][j + 5] == EMPTY) {
//未判断黑方是否有反（冲四）————待改进
                for (
                        k = i + 1;
                        k < i + 5; k++) {
                    if (Map0[i][k] == 3) {
                        points[0].x = i;
                        points[0].y = k;
                        return 1;
                    }
                }
            }
        }
    }
//反斜线搜索
    for (
            i = 0;
            i < MAP_SIZE - 5; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mW = 0;
            mE = 0;
            mQ = 0;   //用来表示白方冲四点数目
            for (
                    k = 1;
                    k < 5; k++) {
                if (Map0[i + k][j + k] == 1) {
                    mW++;
                } else if (chessMap[i + k][j + k] == EMPTY) {
                    mE++;
                }
                if (Map0[i + k][j + k] == 3) {
                    mQ++;
                }
            }
            if (mW == 0 && mE == 4 && mQ >= 3 && chessMap[i][j] == EMPTY && chessMap[i + 5][j + 5] == EMPTY) {
//未判断黑方是否有反（冲四）————待改进
                for (
                        k = 1;
                        k < 5; k++) {
                    if (Map0[i + k][j + k] == 3) {
                        points[0].x = i + k;
                        points[0].y = j + k;
                        return 1;
                    }
                }
            }
        }
    }
//正斜线搜索
    for (
            i = 5;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mW = 0;
            mE = 0;
            mQ = 0;   //用来表示白方冲四点数目
            for (
                    k = 1;
                    k < 5; k++) {
                if (Map0[i - k][j + k] == 1) {
                    mW++;
                } else if (chessMap[i - k][j + k] == EMPTY) {
                    mE++;
                }
                if (Map0[i - k][j + k] == 3) {
                    mQ++;
                }
            }
            if (mW == 0 && mE == 4 && mQ >= 3 && chessMap[i][j] == EMPTY && chessMap[i - 5][j + 5] == EMPTY) {
//未判断黑方是否有反（冲四）————待改进
                for (
                        k = 1;
                        k < 5; k++) {
                    if (Map0[i - k][j + k] == 3) {
                        points[0].x = i - k;
                        points[0].y = j + k;
                        return 1;
                    }
                }
            }
        }
    }

//应对BLACK活三

//计算A/D/S价值
    int maxA, maxD, maxS;
    int xA, yA, xD, yD, xS, yS;
    int valueA[MAP_SIZE][MAP_SIZE], valueD[MAP_SIZE][MAP_SIZE], valueS[MAP_SIZE][MAP_SIZE];
    value_A(chessMap,
            0, valueA);
    value_B(chessMap,
            0, valueD);
    maxA = -1;
    maxD = -1;
    maxS = -1;
    for (
            i = 0;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE; j++) {
            if (chessMap[i][j] != EMPTY) {
                continue;
            }
            valueS[i][j] = valueA[i][j] + valueD[i][j];
//            if (i == 4 && j == 5) {
//                printf("%d, %d, %d", valueS[i][j], valueA[i][j], valueD[i][j]);
//            }
            if (valueA[i][j] > maxA) {
                maxA = valueA[i][j];
                xA = i;
                yA = j;
            }
            if (valueD[i][j] > maxD) {
                maxD = valueD[i][j];
                xD = i;
                yD = j;
            }
            if (valueS[i][j] > maxS) {
                maxS = valueS[i][j];
                xS = i;
                yS = j;
            }
        }
    }
//竖线搜索
    for (
            i = 0;
            i < MAP_SIZE - 5; i++) {
        for (
                j = 0;
                j < MAP_SIZE; j++) {
            int x0, y0;
            mB = 0;
            mE = 0;
            for (
                    k = i + 1;
                    k < i + 5; k++) {
                if (chessMap[k][j] == BLACK) {
                    mB++;
                } else if (chessMap[k][j] == EMPTY) {
                    mE++;
                    x = k;
                    y = j;
                }
            }
            if (mB == 3 && mE == 1 && chessMap[i][j] == EMPTY && chessMap[i + 5][j] == EMPTY) {
                if (x == i + 2 || x == i + 3) {
                    points[0].x = x;
                    points[0].y = y;
                    return 1;
                } else if (x == i + 1) {
                    x0 = i + 5;
                    y0 = j;
                    if (valueD[x][y] * 2 + valueA[x][y] > valueD[x0][y0] * 2 + valueA[x0][y0]) {
                        points[0].x = x;
                        points[0].y = y;
                        return 1;
                    } else {
                        points[0].x = x0;
                        points[0].y = y0;
                        return 1;
                    }
                } else if (x == i + 4) {
                    x0 = i;
                    y0 = j;
                    if (valueD[x][y] * 2 + valueA[x][y] > valueD[x0][y0] * 2 + valueA[x0][y0]) {
                        points[0].x = x;
                        points[0].y = y;
                        return 1;
                    } else {
                        points[0].x = x0;
                        points[0].y = y0;
                        return 1;
                    }
                }
            }
        }
    }
//横线搜索
    for (
            i = 0;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            int x0, y0;
            mB = 0;
            mE = 0;
            for (
                    k = j + 1;
                    k < j + 5; k++) {
                if (chessMap[i][k] == BLACK) {
                    mB++;
                } else if (chessMap[i][k] == EMPTY) {
                    mE++;
                    x = i;
                    y = k;
                }
            }
            if (mB == 3 && mE == 1 && chessMap[i][j] == EMPTY && chessMap[i][j + 5] == EMPTY) {
                if (y == j + 2 || y == j + 3) {
                    points[0].x = x;
                    points[0].y = y;
                    return 1;
                } else if (y == j + 1) {
                    x0 = i;
                    y0 = j + 5;
                    if (valueD[x][y] * 2 + valueA[x][y] > valueD[x0][y0] * 2 + valueA[x0][y0]) {
                        points[0].x = x;
                        points[0].y = y;
                        return 1;
                    } else {
                        points[0].x = x0;
                        points[0].y = y0;
                        return 1;
                    }
                } else if (y == j + 4) {
                    x0 = i;
                    y0 = j;
                    if (valueD[x][y] * 2 + valueA[x][y] > valueD[x0][y0] * 2 + valueA[x0][y0]) {
                        points[0].x = x;
                        points[0].y = y;
                        return 1;
                    } else {
                        points[0].x = x0;
                        points[0].y = y0;
                        return 1;
                    }
                }
            }
        }
    }
//反斜线搜索
    for (
            i = 0;
            i < MAP_SIZE - 5; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            int x0, y0;
            mB = 0;
            mE = 0;
            for (
                    k = 1;
                    k < 5; k++) {
                if (chessMap[i + k][j + k] == BLACK) {
                    mB++;
                } else if (chessMap[i + k][j + k] == EMPTY) {
                    mE++;
                    x = i + k;
                    y = j + k;
                }
            }
            if (mB == 3 && mE == 1 && chessMap[i][j] == EMPTY && chessMap[i + 5][j + 5] == EMPTY) {
                if (y == j + 2 || y == j + 3) {
                    points[0].x = x;
                    points[0].y = y;
                    return 1;
                } else if (y == j + 1) {
                    x0 = i + 5;
                    y0 = j + 5;
                    if (valueD[x][y] * 2 + valueA[x][y] > valueD[x0][y0] * 2 + valueA[x0][y0]) {
                        points[0].x = x;
                        points[0].y = y;
                        return 1;
                    } else {
                        points[0].x = x0;
                        points[0].y = y0;
                        return 1;
                    }
                } else if (y == j + 4) {
                    x0 = i;
                    y0 = j;
                    if (valueD[x][y] * 2 + valueA[x][y] > valueD[x0][y0] * 2 + valueA[x0][y0]) {
                        points[0].x = x;
                        points[0].y = y;
                        return 1;
                    } else {
                        points[0].x = x0;
                        points[0].y = y0;
                        return 1;
                    }
                }
            }
        }
    }
//正斜线搜索
    for (
            i = 5;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            int x0, y0;
            mB = 0;
            mE = 0;
            for (
                    k = 1;
                    k < 5; k++) {
                if (chessMap[i - k][j + k] == BLACK) {
                    mB++;
                } else if (chessMap[i - k][j + k] == EMPTY) {
                    mE++;
                    x = i - k;
                    y = j + k;
                }
            }
            if (mB == 3 && mE == 1 && chessMap[i][j] == EMPTY && chessMap[i - 5][j + 5] == EMPTY) {
                if (y == j + 2 || y == j + 3) {
                    points[0].x = x;
                    points[0].y = y;
                    return 1;
                } else if (y == j + 1) {
                    x0 = i - 5;
                    y0 = j + 5;
                    if (valueD[x][y] * 2 + valueA[x][y] > valueD[x0][y0] * 2 + valueA[x0][y0]) {
                        points[0].x = x;
                        points[0].y = y;
                        return 1;
                    } else {
                        points[0].x = x0;
                        points[0].y = y0;
                        return 1;
                    }
                } else if (y == j + 4) {
                    x0 = i;
                    y0 = j;
                    if (valueD[x][y] * 2 + valueA[x][y] > valueD[x0][y0] * 2 + valueA[x0][y0]) {
                        points[0].x = x;
                        points[0].y = y;
                        return 1;
                    } else {
                        points[0].x = x0;
                        points[0].y = y0;
                        return 1;
                    }
                }
            }
        }
    }

//应对BLACK四四
    int map4B[MAP_SIZE][MAP_SIZE];   //To Four参数-B
    map_4(chessMap,
          2, map4B);
    for (
            i = 0;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE; j++) {
            if (map4B[i][j] > 1) {
                points[0].x = i;
                points[0].y = j;
                return 1;
            }
        }
    }


//防四三杀
//战术地图
//0-EMPTY
//1-WHITE
//2-BLACK
//3-BLACK冲四点

//地图复制
    for (
            i = 0;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE; j++) {
            if (chessMap[i][j] == EMPTY) {
                Map0[i][j] = 0;
            } else if (chessMap[i][j] == WHITE) {
                Map0[i][j] = 1;
            } else if (chessMap[i][j] == BLACK) {
                Map0[i][j] = 2;
            }
        }
    }
//搜索BLACK冲四点
//竖线搜索
    for (
            i = 0;
            i < MAP_SIZE - 4; i++) {
        for (
                j = 0;
                j < MAP_SIZE; j++) {
            mE = 0;
            mB = 0;
            for (
                    k = i;
                    k < i + 5; k++) {
                if (chessMap[k][j] == BLACK) {
                    mB++;
                } else if (chessMap[k][j] == EMPTY) {
                    mE++;
                }
            }
            if (mB == 3 && mE == 2) {
                for (
                        k = i;
                        k < i + 5; k++) {
                    if (chessMap[k][j] == EMPTY) {
                        Map0[k][j] = 3;
                    }
                }
            }
        }
    }
//横线搜索
    for (
            i = 0;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 4; j++) {
            mB = 0;
            mE = 0;
            for (
                    k = j;
                    k < j + 5; k++) {
                if (chessMap[i][k] == BLACK) {
                    mB++;
                } else if (chessMap[i][k] == EMPTY) {
                    mE++;
                }
            }
            if (mB == 3 && mE == 2) {
                for (
                        k = j;
                        k < j + 5; k++) {
                    if (chessMap[i][k] == EMPTY) {
                        Map0[i][k] = 3;
                    }
                }
            }
        }
    }
//反斜线搜索
    for (
            i = 0;
            i < MAP_SIZE - 4; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 4; j++) {
            mB = 0;
            mE = 0;
            for (
                    k = 0;
                    k < 5; k++) {
                if (chessMap[i + k][j + k] == BLACK) {
                    mB++;
                } else if (chessMap[i + k][j + k] == EMPTY) {
                    mE++;
                }
            }
            if (mB == 3 && mE == 2) {
                for (
                        k = 0;
                        k < 5; k++) {
                    if (chessMap[i + k][j + k] == EMPTY) {
                        Map0[i + k][j + k] = 3;
                    }
                }
            }
        }
    }
//正斜线搜索
    for (
            i = 4;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 4; j++) {
            mB = 0;
            mE = 0;
            for (
                    k = 0;
                    k < 5; k++) {
                if (chessMap[i - k][j + k] == BLACK) {
                    mB++;
                } else if (chessMap[i - k][j + k] == EMPTY) {
                    mE++;
                }
            }
            if (mB == 3 && mE == 2) {
                for (
                        k = 0;
                        k < 5; k++) {
                    if (chessMap[i - k][j + k] == EMPTY) {
                        Map0[i - k][j + k] = 3;
                    }
                }
            }
        }
    }
//搜索对方活三（1冲四点+2黑子）
//竖线搜索
    for (
            i = 0;
            i < MAP_SIZE - 5; i++) {
        for (
                j = 0;
                j < MAP_SIZE; j++) {
            mB = 0;
            mE = 0;
            mQ = 0;   //用来表示黑方冲四点数目
            for (
                    k = i + 1;
                    k < i + 5; k++) {
                if (Map0[k][j] == 2) {
                    mB++;
                } else if (chessMap[k][j] == EMPTY) {
                    mE++;
                }
                if (Map0[k][j] == 3) {
                    mQ++;
                }
            }
            if (mB == 2 && mE == 2 && mQ >= 1 && chessMap[i][j] == EMPTY && chessMap[i + 5][j] == EMPTY) {
//未判断白方是否有反（冲四）————待改进
                for (
                        k = i + 1;
                        k < i + 5; k++) {
                    if (Map0[k][j] == 3) {
                        points[0].x = k;
                        points[0].y = j;
                        return 1;
                    }
                }
            }
        }
    }
//横线搜索
    for (
            i = 0;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mB = 0;
            mE = 0;
            mQ = 0;   //用来表示黑方冲四点数目
            for (
                    k = j + 1;
                    k < j + 5; k++) {
                if (Map0[i][k] == 2) {
                    mB++;
                } else if (chessMap[i][k] == EMPTY) {
                    mE++;
                }
                if (Map0[i][k] == 3) {
                    mQ++;
                }
            }
            if (mB == 2 && mE == 2 && mQ >= 1 && chessMap[i][j] == EMPTY && chessMap[i][j + 5] == EMPTY) {
//未判断白方是否有反（冲四）————待改进
                for (
                        k = j + 1;
                        k < j + 5; k++) {
                    if (Map0[i][k] == 3) {
                        points[0].x = i;
                        points[0].y = k;
                        return 1;
                    }
                }
            }
        }
    }
//反斜线搜索
    for (
            i = 0;
            i < MAP_SIZE - 5; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mB = 0;
            mE = 0;
            mQ = 0;   //用来表示黑方冲四点数目
            for (
                    k = 1;
                    k < 5; k++) {
                if (Map0[i + k][j + k] == 2) {
                    mB++;
                } else if (chessMap[i + k][j + k] == EMPTY) {
                    mE++;
                }
                if (Map0[i + k][j + k] == 3) {
                    mQ++;
                }
            }
            if (mB == 2 && mE == 2 && mQ >= 1 && chessMap[i][j] == EMPTY && chessMap[i + 5][j + 5] == EMPTY) {
//未判断白方是否有反（冲四）————待改进
                for (
                        k = 1;
                        k < 5; k++) {
                    if (Map0[i + k][j + k] == 3) {
                        points[0].x = i + k;
                        points[0].y = j + k;
                        return 1;
                    }
                }
            }
        }
    }
//正斜线搜索
    for (
            i = 5;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mB = 0;
            mE = 0;
            mQ = 0;   //用来表示黑方冲四点数目
            for (
                    k = 1;
                    k < 5; k++) {
                if (Map0[i - k][j + k] == 2) {
                    mB++;
                } else if (chessMap[i - k][j + k] == EMPTY) {
                    mE++;
                }
                if (Map0[i - k][j + k] == 3) {
                    mQ++;
                }
            }
            if (mB == 2 && mE == 2 && mQ >= 1 && chessMap[i][j] == EMPTY && chessMap[i - 5][j + 5] == EMPTY) {
//未判断白方是否有反（冲四）————待改进
                for (
                        k = 1;
                        k < 5; k++) {
                    if (Map0[i - k][j + k] == 3) {
                        points[0].x = i - k;
                        points[0].y = j + k;
                        return 1;
                    }
                }
            }
        }
    }
//搜索对方活三（2冲四点+1黑子）
//竖线搜索
    for (
            i = 0;
            i < MAP_SIZE - 5; i++) {
        for (
                j = 0;
                j < MAP_SIZE; j++) {
            mB = 0;
            mE = 0;
            mQ = 0;   //用来表示黑方冲四点数目
            for (
                    k = i + 1;
                    k < i + 5; k++) {
                if (Map0[k][j] == 2) {
                    mB++;
                } else if (chessMap[k][j] == EMPTY) {
                    mE++;
                }
                if (Map0[k][j] == 3) {
                    mQ++;
                }
            }
            if (mB == 1 && mE == 3 && mQ >= 2 && chessMap[i][j] == EMPTY && chessMap[i + 5][j] == EMPTY) {
//未判断白方是否有反（冲四）————待改进
                for (
                        k = i + 1;
                        k < i + 5; k++) {
                    if (Map0[k][j] == 3) {
                        points[0].x = k;
                        points[0].y = j;
                        return 1;
                    }
                }
            }
        }
    }
//横线搜索
    for (
            i = 0;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mB = 0;
            mE = 0;
            mQ = 0;   //用来表示黑方冲四点数目
            for (
                    k = j + 1;
                    k < j + 5; k++) {
                if (Map0[i][k] == 2) {
                    mB++;
                } else if (chessMap[i][k] == EMPTY) {
                    mE++;
                }
                if (Map0[i][k] == 3) {
                    mQ++;
                }
            }
            if (mB == 1 && mE == 3 && mQ >= 2 && chessMap[i][j] == EMPTY && chessMap[i][j + 5] == EMPTY) {
//未判断白方是否有反（冲四）————待改进
                for (
                        k = i + 1;
                        k < i + 5; k++) {
                    if (Map0[i][k] == 3) {
                        points[0].x = i;
                        points[0].y = k;
                        return 1;
                    }
                }
            }
        }
    }
//反斜线搜索
    for (
            i = 0;
            i < MAP_SIZE - 5; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mB = 0;
            mE = 0;
            mQ = 0;   //用来表示黑方冲四点数目
            for (
                    k = 1;
                    k < 5; k++) {
                if (Map0[i + k][j + k] == 2) {
                    mB++;
                } else if (chessMap[i + k][j + k] == EMPTY) {
                    mE++;
                }
                if (Map0[i + k][j + k] == 3) {
                    mQ++;
                }
            }
            if (mB == 1 && mE == 3 && mQ >= 2 && chessMap[i][j] == EMPTY && chessMap[i + 5][j + 5] == EMPTY) {
//未判断白方是否有反（冲四）————待改进
                for (
                        k = 1;
                        k < 5; k++) {
                    if (Map0[i + k][j + k] == 3) {
                        points[0].x = i + k;
                        points[0].y = j + k;
                        return 1;
                    }
                }
            }
        }
    }
//正斜线搜索
    for (
            i = 5;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mB = 0;
            mE = 0;
            mQ = 0;   //用来表示黑方冲四点数目
            for (
                    k = 1;
                    k < 5; k++) {
                if (Map0[i - k][j + k] == 2) {
                    mB++;
                } else if (chessMap[i - k][j + k] == EMPTY) {
                    mE++;
                }
                if (Map0[i - k][j + k] == 3) {
                    mQ++;
                }
            }
            if (mB == 1 && mE == 3 && mQ >= 2 && chessMap[i][j] == EMPTY && chessMap[i - 5][j + 5] == EMPTY) {
//未判断白方是否有反（冲四）————待改进
                for (
                        k = 1;
                        k < 5; k++) {
                    if (Map0[i - k][j + k] == 3) {
                        points[0].x = i - k;
                        points[0].y = j + k;
                        return 1;
                    }
                }
            }
        }
    }
//搜索对方活三（3冲四点+0黑子）
//竖线搜索
    for (
            i = 0;
            i < MAP_SIZE - 5; i++) {
        for (
                j = 0;
                j < MAP_SIZE; j++) {
            mB = 0;
            mE = 0;
            mQ = 0;   //用来表示黑方冲四点数目
            for (
                    k = i + 1;
                    k < i + 5; k++) {
                if (Map0[k][j] == 2) {
                    mB++;
                } else if (chessMap[k][j] == EMPTY) {
                    mE++;
                }
                if (Map0[k][j] == 3) {
                    mQ++;
                }
            }
            if (mB == 0 && mE == 4 && mQ >= 3 && chessMap[i][j] == EMPTY && chessMap[i + 5][j] == EMPTY) {
//未判断白方是否有反（冲四）————待改进
                for (
                        k = i + 1;
                        k < i + 5; k++) {
                    if (Map0[k][j] == 3) {
                        points[0].x = k;
                        points[0].y = j;
                        return 1;
                    }
                }
            }
        }
    }
//横线搜索
    for (
            i = 0;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mB = 0;
            mE = 0;
            mQ = 0;   //用来表示黑方冲四点数目
            for (
                    k = j + 1;
                    k < j + 5; k++) {
                if (Map0[i][k] == 2) {
                    mB++;
                } else if (chessMap[i][k] == EMPTY) {
                    mE++;
                }
                if (Map0[i][k] == 3) {
                    mQ++;
                }
            }
            if (mB == 0 && mE == 4 && mQ >= 3 && chessMap[i][j] == EMPTY && chessMap[i][j + 5] == EMPTY) {
//未判断白方是否有反（冲四）————待改进
                for (
                        k = i + 1;
                        k < i + 5; k++) {
                    if (Map0[i][k] == 3) {
                        points[0].x = i;
                        points[0].y = k;
                        return 1;
                    }
                }
            }
        }
    }
//反斜线搜索
    for (
            i = 0;
            i < MAP_SIZE - 5; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mB = 0;
            mE = 0;
            mQ = 0;   //用来表示黑方冲四点数目
            for (
                    k = 1;
                    k < 5; k++) {
                if (Map0[i + k][j + k] == 2) {
                    mB++;
                } else if (chessMap[i + k][j + k] == EMPTY) {
                    mE++;
                }
                if (Map0[i + k][j + k] == 3) {
                    mQ++;
                }
            }
            if (mB == 0 && mE == 4 && mQ >= 3 && chessMap[i][j] == EMPTY && chessMap[i + 5][j + 5] == EMPTY) {
//未判断白方是否有反（冲四）————待改进
                for (
                        k = 1;
                        k < 5; k++) {
                    if (Map0[i + k][j + k] == 3) {
                        points[0].x = i + k;
                        points[0].y = j + k;
                        return 1;
                    }
                }
            }
        }
    }
//正斜线搜索
    for (
            i = 5;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE - 5; j++) {
            mB = 0;
            mE = 0;
            mQ = 0;   //用来表示黑方冲四点数目
            for (
                    k = 1;
                    k < 5; k++) {
                if (Map0[i - k][j + k] == 2) {
                    mB++;
                } else if (chessMap[i - k][j + k] == EMPTY) {
                    mE++;
                }
                if (Map0[i - k][j + k] == 3) {
                    mQ++;
                }
            }
            if (mB == 0 && mE == 4 && mQ >= 3 && chessMap[i][j] == EMPTY && chessMap[i - 5][j + 5] == EMPTY) {
//未判断白方是否有反（冲四）————待改进
                for (
                        k = 1;
                        k < 5; k++) {
                    if (Map0[i - k][j + k] == 3) {
                        points[0].x = i - k;
                        points[0].y = j + k;
                        return 1;
                    }
                }
            }
        }
    }

//搜索己方冲三点
    int map3W[MAP_SIZE][MAP_SIZE];   //To Three参数-W
    map_3(chessMap,
          1, map3W);

//双三杀
    for (
            i = 0;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE; j++) {
            if (map3W[i][j] > 1) {
                points[0].x = i;
                points[0].y = j;
                return 1;
            }
        }
    }
//防双三杀
    int map3B[MAP_SIZE][MAP_SIZE];   //To Three参数-B
    map_3(chessMap,
          2, map3B);
    for (
            i = 0;
            i < MAP_SIZE; i++) {
        for (
                j = 0;
                j < MAP_SIZE; j++) {
            if (map3B[i][j] > 1) {
                points[0].x = i;
                points[0].y = j;
                return 1;
            }
        }
    }

//白方做棋
    Point bestPoints[1000];
    int pointNum = 0;
//    if (maxD > 140) {
//        row = xD;
//        col = yD;
//        return;
//    }

    for (i = 0; i < MAP_SIZE; i++) {
        for (j = 0; j < MAP_SIZE; j++) {
            if (chessMap[i][j] != EMPTY) continue;
            bestPoints[pointNum].x = i;
            bestPoints[pointNum].y = j;
            bestPoints[pointNum].value = valueS[i][j];
//            if (bestPoints[pointNum].value > 0) {
//                printf("x: %d, y: %d, value: %d\n", i, j, bestPoints[pointNum].value);
//            }
            ++pointNum;
        }
    }
    int realNum = min(expectedLen, pointNum);

    for (i = realNum; i > 0; --i) {
        BuildMaxHeap(bestPoints, pointNum - realNum + i);
        Swap(bestPoints, pointNum - realNum + i);
    }
    for (i = pointNum - 1, j = 0; j < min(pointNum, expectedLen); ++j, --i)
    {
        points[j].x = bestPoints[i].x;
        points[j].y = bestPoints[i].y;
        points[j].value = bestPoints[i].value;
    }

    return min(expectedLen, pointNum);
}

//int main()
//{
//    int a[6] = {7, 3, 8, 5, 1, 2};
//    int len = 6;    /* 数组长度 */
//    int i;
//
//    for (i = len; i > 0; i--)
//    {
//        BuildMaxHeap(a, i);
//        Swap(a, i);
//    }
//    for (i = 0; i < len; i++)
//    {
//        printf("%d ", a[i]);
//    }
//
//    return 0;
//}

