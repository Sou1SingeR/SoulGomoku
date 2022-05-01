#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<windows.h>
#include<iostream>
#define random(x) (rand()%x)

#define BOOL  int
#define TRUE   1
#define FALSE  0

#define WIDTH_MAX  160
#define HEIGHT_MAX  80
#define WIDTH_MIN   5
#define HEIGHT_MIN  5
#define TIME_DELAY 1000
#define MAP_SIZE 15

using namespace std;
enum ChessType{
    EMPTY=0,
    WHITE=1,
    BLACK=2
};
ChessType chessmap[MAP_SIZE][MAP_SIZE];

typedef struct {int x, y;} point_t;

enum Stone {kStnNo, kStnAi, kStnOp};

// 全局变量 //////////////////////////////////////////////////////////////////

// 棋盘的数据结构
// 第一维是高，第二维是宽
enum Stone g_board[HEIGHT_MAX][WIDTH_MAX];

// 棋盘实际使用的尺寸及默认值
int g_width = 20, g_height = 20;

// 是否采用 SUGGEST 回应
BOOL g_is_suggest = FALSE;

// 配置
struct {
	int timeout_turn  ;  // 步时
	int timeout_match ;  // 局时
	int max_memory    ;  // 内存
	int time_left     ;  // 余时
	int game_type     ;  // 类型
	int rule          ;  // 规则
	char folder[FILENAME_MAX];  // 目录
} g_info;

// 棋盘操作 //////////////////////////////////////////////////////////////////

/**
 *  @brief  从棋盘读取棋子
 *  @param  pt  坐标
 *  @return 棋子类型
 */
enum Stone BoardGet(point_t pt)
{
	return g_board[pt.y][pt.x];
}

/**
 *  @brief  向棋盘设置棋子
 *  @param  pt  坐标
 *  @param  stn 棋子类型
 */
void BoardSet(point_t pt, enum Stone stn)
{
	g_board[pt.y][pt.x] = stn;
}

/**
 *  @brief  清空棋盘
 */
void BoardReset(void)
{
	int i, j;

	for (i = 0; i < HEIGHT_MAX; ++i) {
		for (j = 0; j < WIDTH_MAX; ++j) {
			g_board[i][j] = kStnNo;
		}
	}
}

/**
 *  @brief  更改棋盘尺寸
 *  @param  width   宽
 *  @param  height  高
 *  @return 成功与否
 */
BOOL BoardResize(int width, int height)
{
	if (WIDTH_MIN < width && width < WIDTH_MAX
	 && HEIGHT_MIN < height && height < HEIGHT_MAX)
	{
		g_width = width;
		g_height = height;
		return TRUE;
	}

	return FALSE;
}

/**
 *  @brief  判断坐标是否在棋盘使用范围内
 *  @param  pt  坐标
 *  @return 是否在内
 */
BOOL BoardHasPoint(point_t pt)
{
	return 0 <= pt.x && pt.x < g_width
	    && 0 <= pt.y && pt.y < g_height;
}

// 算法相关 //////////////////////////////////////////////////////////////////

//To Three参数
int MAP3(ChessType chessMap[15][15],int x,int map3[15][15])
{
    int i,j,k,i1,j1,k1,i2,j2,k2;
    int i0,j0,max=0;
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            map3[i][j]=0;
        }
    }
    //竖线搜索
    i0=1;
    j0=0;
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            if(chessMap[i][j]!=EMPTY)
            {
                continue;
            }
            for(i1=i-i0*3,j1=j-j0*3,k1=0;k1<4;i1+=i0,j1+=j0,k1++)
            {
                int mE=0,mX=0,f=0;
                for(i2=i1,j2=j1,k2=0;k2<4;i2+=i0,j2+=j0,k2++)
                {
                    if(i2<1||j2<1||i2>13||j2>13)
                    {
                        f=1;
                        break;
                    }
                    if(chessMap[i2][j2]==EMPTY)
                    {
                        mE++;
                    }
                    else if(chessMap[i2][j2]==x)
                    {
                        mX++;
                    }
                }
                if(f==1)
                {
                    continue;
                }
                if(mE==2&&mX==2&&chessMap[i1-i0][j1-j0]==EMPTY&&chessMap[i1+i0*4][j1+j0*4]==EMPTY)
                {
                    map3[i][j]++;
                    break;
                }
            }
        }
    }
    //横线搜索
    i0=0;
    j0=1;
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            if(chessMap[i][j]!=EMPTY)
            {
                continue;
            }
            for(i1=i-i0*3,j1=j-j0*3,k1=0;k1<4;i1+=i0,j1+=j0,k1++)
            {
                int mE=0,mX=0,f=0;
                for(i2=i1,j2=j1,k2=0;k2<4;i2+=i0,j2+=j0,k2++)
                {
                    if(i2<1||j2<1||i2>13||j2>13)
                    {
                        f=1;
                        break;
                    }
                    if(chessMap[i2][j2]==EMPTY)
                    {
                        mE++;
                    }
                    else if(chessMap[i2][j2]==x)
                    {
                        mX++;
                    }
                }
                if(f==1)
                {
                    continue;
                }
                if(mE==2&&mX==2&&chessMap[i1-i0][j1-j0]==EMPTY&&chessMap[i1+i0*4][j1+j0*4]==EMPTY)
                {
                    map3[i][j]++;
                    break;
                }
            }
        }
    }
    //反斜线搜索
    i0=1;
    j0=1;
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            if(chessMap[i][j]!=EMPTY)
            {
                continue;
            }
            for(i1=i-i0*3,j1=j-j0*3,k1=0;k1<4;i1+=i0,j1+=j0,k1++)
            {
                int mE=0,mX=0,f=0;
                for(i2=i1,j2=j1,k2=0;k2<4;i2+=i0,j2+=j0,k2++)
                {
                    if(i2<1||j2<1||i2>13||j2>13)
                    {
                        f=1;
                        break;
                    }
                    if(chessMap[i2][j2]==EMPTY)
                    {
                        mE++;
                    }
                    else if(chessMap[i2][j2]==x)
                    {
                        mX++;
                    }
                }
                if(f==1)
                {
                    continue;
                }
                if(mE==2&&mX==2&&chessMap[i1-i0][j1-j0]==EMPTY&&chessMap[i1+i0*4][j1+j0*4]==EMPTY)
                {
                    map3[i][j]++;
                    break;
                }
            }
        }
    }
    //正斜线搜索
    i0=-1;
    j0=1;
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            if(chessMap[i][j]!=EMPTY)
            {
                continue;
            }
            for(i1=i-i0*3,j1=j-j0*3,k1=0;k1<4;i1+=i0,j1+=j0,k1++)
            {
                int mE=0,mX=0,f=0;
                for(i2=i1,j2=j1,k2=0;k2<4;i2+=i0,j2+=j0,k2++)
                {
                    if(i2<1||j2<1||i2>13||j2>13)
                    {
                        f=1;
                        break;
                    }
                    if(chessMap[i2][j2]==EMPTY)
                    {
                        mE++;
                    }
                    else if(chessMap[i2][j2]==x)
                    {
                        mX++;
                    }
                }
                if(f==1)
                {
                    continue;
                }
                if(mE==2&&mX==2&&chessMap[i1-i0][j1-j0]==EMPTY&&chessMap[i1+i0*4][j1+j0*4]==EMPTY)
                {
                    map3[i][j]++;
                    break;
                }
            }
        }
    }
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            if(map3[i][j]>max)
            {
                max=map3[i][j];
            }
        }
    }
    return max;
}

//To Four参数
int MAP4(ChessType chessMap[15][15],int x,int map4[15][15])
{
    int i,j,k,i1,j1,k1,i2,j2,k2;
    int i0,j0,max=0;
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            map4[i][j]=0;
        }
    }
    //竖线搜索
    i0=1;
    j0=0;
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            if(chessMap[i][j]!=EMPTY)
            {
                continue;
            }
            for(i1=i-i0*4,j1=j-j0*4,k1=0;k1<5;i1+=i0,j1+=j0,k1++)
            {
                int mE=0,mX=0;
                for(i2=i1,j2=j1,k2=0;k2<5;i2+=i0,j2+=j0,k2++)
                {
                    if(i2<0||j2<0||i2>14||j2>14)
                    {
                        break;
                    }
                    if(chessMap[i2][j2]==EMPTY)
                    {
                        mE++;
                    }
                    else if(chessMap[i2][j2]==x)
                    {
                        mX++;
                    }
                }
                if(mE==2&&mX==3)
                {
                    map4[i][j]++;
                    break;
                }
            }
        }
    }
    //横线搜索
    i0=0;
    j0=1;
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            if(chessMap[i][j]!=EMPTY)
            {
                continue;
            }
            for(i1=i-i0*4,j1=j-j0*4,k1=0;k1<5;i1+=i0,j1+=j0,k1++)
            {
                int mE=0,mX=0;
                for(i2=i1,j2=j1,k2=0;k2<5;i2+=i0,j2+=j0,k2++)
                {
                    if(i2<0||j2<0||i2>14||j2>14)
                    {
                        break;
                    }
                    if(chessMap[i2][j2]==EMPTY)
                    {
                        mE++;
                    }
                    else if(chessMap[i2][j2]==x)
                    {
                        mX++;
                    }
                }
                if(mE==2&&mX==3)
                {
                    map4[i][j]++;
                    break;
                }
            }
        }
    }
    //反斜线搜索
    i0=1;
    j0=1;
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            if(chessMap[i][j]!=EMPTY)
            {
                continue;
            }
            for(i1=i-i0*4,j1=j-j0*4,k1=0;k1<5;i1+=i0,j1+=j0,k1++)
            {
                int mE=0,mX=0;
                for(i2=i1,j2=j1,k2=0;k2<5;i2+=i0,j2+=j0,k2++)
                {
                    if(i2<0||j2<0||i2>14||j2>14)
                    {
                        break;
                    }
                    if(chessMap[i2][j2]==EMPTY)
                    {
                        mE++;
                    }
                    else if(chessMap[i2][j2]==x)
                    {
                        mX++;
                    }
                }
                if(mE==2&&mX==3)
                {
                    map4[i][j]++;
                    break;
                }
            }
        }
    }
    //正斜线搜索
    i0=-1;
    j0=1;
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            if(chessMap[i][j]!=EMPTY)
            {
                continue;
            }
            for(i1=i-i0*4,j1=j-j0*4,k1=0;k1<5;i1+=i0,j1+=j0,k1++)
            {
                int mE=0,mX=0;
                for(i2=i1,j2=j1,k2=0;k2<5;i2+=i0,j2+=j0,k2++)
                {
                    if(i2<0||j2<0||i2>14||j2>14)
                    {
                        break;
                    }
                    if(chessMap[i2][j2]==EMPTY)
                    {
                        mE++;
                    }
                    else if(chessMap[i2][j2]==x)
                    {
                        mX++;
                    }
                }
                if(mE==2&&mX==3)
                {
                    map4[i][j]++;
                    break;
                }
            }
        }
    }
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            if(map4[i][j]>max)
            {
                max=map4[i][j];
            }
        }
    }
    return max;
}


//valueD表
int table_B(ChessType str[4],int x){
    if(x==0){
        if(str[0]==BLACK && str[1]==BLACK && str[2]==BLACK)//BBB-100
            return 100;
        if(str[0]==BLACK && str[1]==BLACK && str[2]==EMPTY && str[3]==BLACK)//BBEB-100
            return 100;
        if(str[0]==BLACK && str[1]==EMPTY && str[2]==BLACK && str[3]==BLACK)//BEBB-100
            return 100;
        if(str[0]==EMPTY && str[1]==BLACK && str[2]==BLACK && str[3]==BLACK)//EBBB-100
            return 100;
        if(str[0]==BLACK && str[1]==BLACK && str[2]==EMPTY)//BBE-100
            return 100;
        if(str[0]==BLACK && str[1]==EMPTY && str[2]==BLACK && str[3]==EMPTY)//BEBE-90
            return 90;
        if(str[0]==EMPTY && str[1]==BLACK && str[2]==BLACK && str[3]==EMPTY)//EBBE-55
            return 55;
        if(str[0]==EMPTY && str[1]==BLACK && str[2]==BLACK && str[3]==WHITE)//EBBW-30
            return 30;
        if(str[0]==BLACK && str[1]==EMPTY && str[2]==BLACK && str[3]==WHITE)//BEBW-30
            return 30;
        if(str[0]==BLACK && str[1]==EMPTY)//BE-20
            return 20;
        if(str[0]==EMPTY && str[1]==BLACK && str[2]==EMPTY)//EBE-10
            return 10;
    }
    if(x==1){
        if(str[0]==WHITE && str[1]==WHITE && str[2]==WHITE)//WWW-100
            return 100;
        if(str[0]==WHITE && str[1]==WHITE && str[2]==EMPTY && str[3]==WHITE)//WWEW-100
            return 100;
        if(str[0]==WHITE && str[1]==EMPTY && str[2]==WHITE && str[3]==WHITE)//WEWW-100
            return 100;
        if(str[0]==EMPTY && str[1]==WHITE && str[2]==WHITE && str[3]==WHITE)//EWWW-100
            return 100;
        if(str[0]==WHITE && str[1]==WHITE && str[2]==EMPTY)//WWE-100
            return 100;
        if(str[0]==WHITE && str[1]==EMPTY && str[2]==WHITE && str[3]==EMPTY)//WEWE-90
            return 90;
        if(str[0]==EMPTY && str[1]==WHITE && str[2]==WHITE && str[3]==EMPTY)//EWWE-55
            return 55;
        if(str[0]==EMPTY && str[1]==WHITE && str[2]==WHITE && str[3]==BLACK)//EWWB-30
            return 30;
        if(str[0]==WHITE && str[1]==EMPTY && str[2]==WHITE && str[3]==BLACK)//WEWB-30
            return 30;
        if(str[0]==WHITE && str[1]==EMPTY)//WE-20
            return 20;
        if(str[0]==EMPTY && str[1]==WHITE && str[2]==EMPTY)//EWE-10
            return 10;
    }
    return 0;
}
//valueA表
int table_A(ChessType str[4],int x){
    if(x==0){
        if(str[0]==EMPTY && str[1]==WHITE && str[2]==WHITE && str[3]==BLACK)//EWWB-100
            return 100;
        if(str[0]==WHITE && str[1]==EMPTY && str[2]==WHITE && str[3]==BLACK)//WEWB-100
            return 100;
        if(str[0]==WHITE && str[1]==WHITE && str[2]==EMPTY)//WWE-100
            return 100;
        if(str[0]==WHITE && str[1]==EMPTY && str[2]==WHITE && str[3]==EMPTY)//WEWE-90
            return 90;
        if(str[0]==EMPTY && str[1]==WHITE && str[2]==WHITE && str[3]==EMPTY)//EWWE-90
            return 90;
        if(str[0]==WHITE && str[1]==EMPTY)//WE-80
            return 80;
        if(str[0]==EMPTY && str[1]==WHITE && str[2]==EMPTY)//EWE-85
            return 85;
        if(str[0]==EMPTY && str[1]==EMPTY && str[2]==WHITE && str[3]==EMPTY)//EEWE-75
            return 75;
    }
    if(x==1){
        if(str[0]==EMPTY && str[1]==BLACK && str[2]==BLACK && str[3]==WHITE)//EBBW-100
            return 100;
        if(str[0]==BLACK && str[1]==EMPTY && str[2]==BLACK && str[3]==WHITE)//BEBW-100
            return 100;
        if(str[0]==BLACK && str[1]==BLACK && str[2]==EMPTY)//BBE-100
            return 100;
        if(str[0]==BLACK && str[1]==EMPTY && str[2]==BLACK && str[3]==EMPTY)//BEBE-90
            return 90;
        if(str[0]==EMPTY && str[1]==BLACK && str[2]==BLACK && str[3]==EMPTY)//EBBE-90
            return 90;
        if(str[0]==BLACK && str[1]==EMPTY)//BE-80
            return 80;
        if(str[0]==EMPTY && str[1]==BLACK && str[2]==EMPTY)//EBE-85
            return 85;
        if(str[0]==EMPTY && str[1]==EMPTY && str[2]==BLACK && str[3]==EMPTY)//EEBE-75
            return 75;
    }
    return 0;

}
//valueD计算
void value_B(ChessType chessMap[15][15],int x,int valueMap[15][15]){
    int p;
    memset(valueMap,0,sizeof(int)*225);
    ChessType str[4]={EMPTY};
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            if(i-1>=0){
                if(j-1>=0 && chessMap[i-1][j-1]!=EMPTY){//存在1点并一点不为空
                    for(p=0;p<4;p++){
                        if((i-1-p)<0 || (j-1-p)<0)break;
                        str[p]=chessMap[i-1-p][j-1-p];
                    }
                    valueMap[i][j]+=table_B(str,x);//累计叠加防守值
                    memset(str,EMPTY,sizeof(str));
                }
                if(chessMap[i-1][j]!=EMPTY){//2点存在并不为空
                    for(p=0;p<4;p++){
                        if((i-1-p)<0)break;
                        str[p]=chessMap[i-1-p][j];
                    }
                    valueMap[i][j]+=table_B(str,x);//累计叠加防守值
                    memset(str,EMPTY,sizeof(str));
                }
                if(j+1<15 && chessMap[i-1][j+1]!=EMPTY){//3点存在并不为空
                    for(p=0;p<4;p++){
                        if((i-1-p)<0 || (j+1+p)>14)break;
                        str[p]=chessMap[i-1-p][j+1+p];
                    }
                    valueMap[i][j]+=table_B(str,x);//累计叠加防守值
                    memset(str,EMPTY,sizeof(str));
                }
            }
            if(j+1<15){
                if(chessMap[i][j+1]!=EMPTY){//4点存在并不为空
                    for(p=0;p<4;p++){
                        if((j+1+p)>14)break;
                        str[p]=chessMap[i][j+1+p];
                    }
                    valueMap[i][j]+=table_B(str,x);//累计叠加防守值
                    memset(str,EMPTY,sizeof(str));
                }
                if(i+1<15 && chessMap[i+1][j+1]!=EMPTY){//5点存在并不为空
                    for(p=0;p<4;p++){
                        if((i+1+p)>14 || (j+1+p)>14)break;
                        str[p]=chessMap[i+1+p][j+1+p];
                    }
                    valueMap[i][j]+=table_B(str,x);//累计叠加防守值
                    memset(str,EMPTY,sizeof(str));
                }
            }
            if(i+1<15){
                if(chessMap[i+1][j]!=EMPTY){//6点存在并不为空
                    for(p=0;p<4;p++){
                        if((i+1+p)>14)break;
                        str[p]=chessMap[i+1+p][j];
                    }
                    valueMap[i][j]+=table_B(str,x);//累计叠加防守值
                    memset(str,EMPTY,sizeof(str));
                }
                if(j-1>=0 && chessMap[i+1][j-1]!=EMPTY){//7点存在并不为空
                    for(p=0;p<4;p++){
                        if((j-1-p)<0 || (i+1+p)>14)break;
                        str[p]=chessMap[i+1+p][j-1-p];
                    }
                    valueMap[i][j]+=table_B(str,x);//累计叠加防守值
                    memset(str,EMPTY,sizeof(str));
                }
            }
            if(j-1>=0 && chessMap[i][j-1]!=EMPTY){
                for(p=0;p<4;p++){//反向探索
                    if((j-1-p)<0)break;
                    str[p]=chessMap[i][j-1-p];
                }
                valueMap[i][j]+=table_B(str,x);//累计叠加防守值
                memset(str,EMPTY,sizeof(str));
            }
        }
    }
}
//valueA计算
void value_A(ChessType chessMap[15][15],int x,int valueMap[15][15]){
    int p;
    memset(valueMap,0,sizeof(int)*225);
    ChessType str[4]={EMPTY};
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            if(i-1>=0){
                if(j-1>=0 && chessMap[i-1][j-1]==EMPTY){//存在1点并一点为空
                    for(p=0;p<4;p++){//反向探索
                        if((i+1+p)>14 || (j+1+p)>14)break;
                        str[p]=chessMap[i+1+p][j+1+p];
                    }
                    valueMap[i][j]+=table_A(str,x);//累计叠加攻击值
                    memset(str,EMPTY,sizeof(str));
                }
                if(chessMap[i-1][j]==EMPTY){//2点存在并为空
                    for(p=0;p<4;p++){//反向探索
                        if((i+1+p)>14)break;
                        str[p]=chessMap[i+1+p][j];
                    }
                    valueMap[i][j]+=table_A(str,x);//累计叠加攻击值
                    memset(str,EMPTY,sizeof(str));
                }
                if(j+1<15 && chessMap[i-1][j+1]==EMPTY){//3点存在并为空
                    for(p=0;p<4;p++){//反向探索
                        if((i+1+p)>14 || (j-1-p)<0)break;
                        str[p]=chessMap[i+1+p][j-1-p];
                    }
                    valueMap[i][j]+=table_A(str,x);//累计叠加攻击值
                    memset(str,EMPTY,sizeof(str));
                }
            }
            if(j+1<15){
                if(chessMap[i][j+1]==EMPTY){//4点存在并为空
                    for(p=0;p<4;p++){//反向探索
                        if((j-1-p)<0)break;
                        str[p]=chessMap[i][j-1-p];
                    }
                    valueMap[i][j]+=table_A(str,x);//累计叠加攻击值
                    memset(str,EMPTY,sizeof(str));
                }
                if(i+1<15 && chessMap[i+1][j+1]==EMPTY){//5点存在并为空
                    for(p=0;p<4;p++){//反向探索
                        if((i-1-p)<0 || (j-1-p)<0)break;
                        str[p]=chessMap[i-1-p][j-1-p];
                    }
                    valueMap[i][j]+=table_A(str,x);//累计叠加攻击值
                    memset(str,EMPTY,sizeof(str));
                }
            }
            if(i+1<15){
                if(chessMap[i+1][j]==EMPTY){//6点存在并为空
                    for(p=0;p<4;p++){//反向探索
                        if((i-1-p)<0)break;
                        str[p]=chessMap[i-1-p][j];
                    }
                    valueMap[i][j]+=table_A(str,x);//累计叠加攻击值
                    memset(str,EMPTY,sizeof(str));
                }
                if(j-1>=0 && chessMap[i+1][j-1]==EMPTY){//7点存在并为空
                    for(p=0;p<4;p++){//反向探索
                        if((i-1-p)<0 || (j+1+p)>14)break;
                        str[p]=chessMap[i-1-p][j+1+p];
                    }
                    valueMap[i][j]+=table_A(str,x);//累计叠加攻击值
                    memset(str,EMPTY,sizeof(str));
                }
            }
            if(j-1>=0 && chessMap[i][j-1]==EMPTY){
                for(p=0;p<4;p++){//反向探索
                    if((j+1+p)>14)break;
                    str[p]=chessMap[i][j+1+p];
                }
                valueMap[i][j]+=table_A(str,x);//累计叠加攻击值
                memset(str,EMPTY,sizeof(str));
            }
        }
    }
}



// 下一步落子位置
void nextMove(ChessType chessMap[MAP_SIZE][MAP_SIZE],int& row,int &col){
    int i,j,k;
    int n=1;
    int mW,mE,mB;  //白子数，黑子数和空格数
    int mQ;
    int x,y;
    int Map0[15][15];   //战术地图
    //计算当前手数
    for(i=0;i<MAP_SIZE;i++)
    {
        for(j=0;j<MAP_SIZE;j++)
        {
            if(chessMap[i][j]!=EMPTY)
            {
                n++;
            }
        }
    }

    /*
    if(n==1)
    {
        row=7;
        col=7;
        return;
    }
    if(n==3)
    {
        row=6;
        col=6;
        return;
    }
    if(n==5)
    {
        row=6;
        col=8;
        return;
    }*/

    //开局定式
    if(n==1)
    {
        row=7;
        col=7;
        return;
    }
    if(n==3)
    {
        int x1,y1,x2,y2,x0,y0,x,y,flag;
        int rand0,randx[3],randy[3];  //备选项
        x1=7;
        y1=7;
        //寻找第二手位置
        flag=0;
        for(i=0;i<MAP_SIZE;i++)
        {
            for(j=0;j<MAP_SIZE;j++)
            {
                if(chessMap[i][j]==BLACK)
                {
                    x2=i;
                    y2=j;
                    flag=1;
                    break;
                }
            }
            if(flag==1)
            {
                break;
            }
        }
        //阴防应对
        if(x2==6 && y2==6 || x2==8 && y2==8)
        {
            randx[0]=6;
            randy[0]=8;
            randx[1]=8;
            randy[1]=6;
            rand0=random(2);
            row=randx[rand0];
            col=randy[rand0];
            return;
        }
        if(x2==6 && y2==8 || x2==8 && y2==6)
        {
            randx[0]=6;
            randy[0]=6;
            randx[1]=8;
            randy[1]=8;
            rand0=random(2);
            row=randx[rand0];
            col=randy[rand0];
            return;
        }
        //阳防应对
        if(x2==7 && y2==6)
        {
            randx[0]=6;
            randy[0]=8;
            randx[1]=8;
            randy[1]=8;
            rand0=random(2);
            row=randx[rand0];
            col=randy[rand0];
            return;
        }
        if(x2==8 && y2==7)
        {
            randx[0]=6;
            randy[0]=6;
            randx[1]=6;
            randy[1]=8;
            rand0=random(2);
            row=randx[rand0];
            col=randy[rand0];
            return;
        }
        if(x2==7 && y2==8)
        {
            randx[0]=6;
            randy[0]=6;
            randx[1]=8;
            randy[1]=6;
            rand0=random(2);
            row=randx[rand0];
            col=randy[rand0];
            return;
        }
        if(x2==6 && y2==7)
        {
            randx[0]=8;
            randy[0]=6;
            randx[1]=8;
            randy[1]=8;
            rand0=random(2);
            row=randx[rand0];
            col=randy[rand0];
            return;
        }
        x0=x1-x2;
        y0=y1-y2;
        if(x0>=0)
        {
            x=1;
        }
        else
        {
            x=-1;
        }
        if(y0>=0)
        {
            y=1;
        }
        else
        {
            y=-1;
        }
        row=7+x;
        col=7+y;
        return;
    }
    //己方冲四搜索
    //竖线搜索
    for(i=0;i<11;i++)
    {
        for(j=0;j<15;j++)
        {
            mW=0;
            mE=0;
            for(k=i;k<i+5;k++)
            {
                if(chessMap[k][j]==WHITE)
                {
                    mW++;
                }
                else if(chessMap[k][j]==EMPTY)
                {
                    mE++;
                    x=k;
                    y=j;
                }
            }
            if(mW==4 && mE==1)
            {
                row=x;
                col=y;
                return;
            }
        }
    }
    //横线搜索
    for(i=0;i<15;i++)
    {
        for(j=0;j<11;j++)
        {
            mW=0;
            mE=0;
            for(k=j;k<j+5;k++)
            {
                if(chessMap[i][k]==WHITE)
                {
                    mW++;
                }
                else if(chessMap[i][k]==EMPTY)
                {
                    mE++;
                    x=i;
                    y=k;
                }
            }
            if(mW==4 && mE==1)
            {
                row=x;
                col=y;
                return;
            }
        }
    }
    //反斜线搜索
    for(i=0;i<11;i++)
    {
        for(j=0;j<11;j++)
        {
            mW=0;
            mE=0;
            for(k=0;k<5;k++)
            {
                if(chessMap[i+k][j+k]==WHITE)
                {
                    mW++;
                }
                else if(chessMap[i+k][j+k]==EMPTY)
                {
                    mE++;
                    x=i+k;
                    y=j+k;
                }
            }
            if(mW==4 && mE==1)
            {
                row=x;
                col=y;
                return;
            }
        }
    }
    //正斜线搜索
    for(i=4;i<15;i++)
    {
        for(j=0;j<11;j++)
        {
            mW=0;
            mE=0;
            for(k=0;k<5;k++)
            {
                if(chessMap[i-k][j+k]==WHITE)
                {
                    mW++;
                }
                else if(chessMap[i-k][j+k]==EMPTY)
                {
                    mE++;
                    x=i-k;
                    y=j+k;
                }
            }
            if(mW==4 && mE==1)
            {
                row=x;
                col=y;
                return;
            }
        }
    }
    //对方冲四搜索
    //竖线搜索
    for(i=0;i<11;i++)
    {
        for(j=0;j<15;j++)
        {
            mB=0;
            mE=0;
            for(k=i;k<i+5;k++)
            {
                if(chessMap[k][j]==BLACK)
                {
                    mB++;
                }
                else if(chessMap[k][j]==EMPTY)
                {
                    mE++;
                    x=k;
                    y=j;
                }
            }
            if(mB==4 && mE==1)
            {
                row=x;
                col=y;
                return;
            }
        }
    }
    //横线搜索
    for(i=0;i<15;i++)
    {
        for(j=0;j<11;j++)
        {
            mB=0;
            mE=0;
            for(k=j;k<j+5;k++)
            {
                if(chessMap[i][k]==BLACK)
                {
                    mB++;
                }
                else if(chessMap[i][k]==EMPTY)
                {
                    mE++;
                    x=i;
                    y=k;
                }
            }
            if(mB==4 && mE==1)
            {
                row=x;
                col=y;
                return;
            }
        }
    }
    //反斜线搜索
    for(i=0;i<11;i++)
    {
        for(j=0;j<11;j++)
        {
            mB=0;
            mE=0;
            for(k=0;k<5;k++)
            {
                if(chessMap[i+k][j+k]==BLACK)
                {
                    mB++;
                }
                else if(chessMap[i+k][j+k]==EMPTY)
                {
                    mE++;
                    x=i+k;
                    y=j+k;
                }
            }
            if(mB==4 && mE==1)
            {
                row=x;
                col=y;
                return;
            }
        }
    }
    //正斜线搜索
    for(i=4;i<15;i++)
    {
        for(j=0;j<11;j++)
        {
            mB=0;
            mE=0;
            for(k=0;k<5;k++)
            {
                if(chessMap[i-k][j+k]==BLACK)
                {
                    mB++;
                }
                else if(chessMap[i-k][j+k]==EMPTY)
                {
                    mE++;
                    x=i-k;
                    y=j+k;
                }
            }
            if(mB==4 && mE==1)
            {
                row=x;
                col=y;
                return;
            }
        }
    }
    //己方活三搜索
    //竖线搜索
    for(i=0;i<10;i++)
    {
        for(j=0;j<15;j++)
        {
            mW=0;
            mE=0;
            for(k=i+1;k<i+5;k++)
            {
                if(chessMap[k][j]==WHITE)
                {
                    mW++;
                }
                else if(chessMap[k][j]==EMPTY)
                {
                    mE++;
                    x=k;
                    y=j;
                }
            }
            if(mW==3 && mE==1 && chessMap[i][j]==EMPTY && chessMap[i+5][j]==EMPTY)
            {
                row=x;
                col=y;
                return;
            }
        }
    }
    //横线搜索
    for(i=0;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            for(k=j+1;k<j+5;k++)
            {
                if(chessMap[i][k]==WHITE)
                {
                    mW++;
                }
                else if(chessMap[i][k]==EMPTY)
                {
                    mE++;
                    x=i;
                    y=k;
                }
            }
            if(mW==3 && mE==1 && chessMap[i][j]==EMPTY && chessMap[i][j+5]==EMPTY)
            {
                row=x;
                col=y;
                return;
            }
        }
    }
    //反斜线搜索
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            for(k=1;k<5;k++)
            {
                if(chessMap[i+k][j+k]==WHITE)
                {
                    mW++;
                }
                else if(chessMap[i+k][j+k]==EMPTY)
                {
                    mE++;
                    x=i+k;
                    y=j+k;
                }
            }
            if(mW==3 && mE==1 && chessMap[i][j]==EMPTY && chessMap[i+5][j+5]==EMPTY)
            {
                row=x;
                col=y;
                return;
            }
        }
    }
    //正斜线搜索
    for(i=5;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            for(k=1;k<5;k++)
            {
                if(chessMap[i-k][j+k]==WHITE)
                {
                    mW++;
                }
                else if(chessMap[i-k][j+k]==EMPTY)
                {
                    mE++;
                    x=i-k;
                    y=j+k;
                }
            }
            if(mW==3 && mE==1 && chessMap[i][j]==EMPTY && chessMap[i-5][j+5]==EMPTY)
            {
                row=x;
                col=y;
                return;
            }
        }
    }

    int map4W[15][15];   //To Four参数-W
    MAP4(chessMap,1,map4W);
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            if(map4W[i][j]>1)
            {
                row=i;
                col=j;
                return;
            }
        }
    }




    //战术地图
    //0-EMPTY
    //1-WHITE
    //2-BLACK
    //3-WHITE冲四点

    //地图复制
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            if(chessMap[i][j]==EMPTY)
            {
                Map0[i][j]=0;
            }
            else if(chessMap[i][j]==WHITE)
            {
                Map0[i][j]=1;
            }
            else if(chessMap[i][j]==BLACK)
            {
                Map0[i][j]=2;
            }
        }
    }
    //搜索WHITE冲四点
    //竖线搜索
    for(i=0;i<11;i++)
    {
        for(j=0;j<15;j++)
        {
            mW=0;
            mE=0;
            for(k=i;k<i+5;k++)
            {
                if(chessMap[k][j]==WHITE)
                {
                    mW++;
                }
                else if(chessMap[k][j]==EMPTY)
                {
                    mE++;
                }
            }
            if(mW==3 && mE==2)
            {
                for(k=i;k<i+5;k++)
                {
                    if(chessMap[k][j]==EMPTY)
                    {
                        Map0[k][j]=3;
                    }
                }
            }
        }
    }
    //横线搜索
    for(i=0;i<15;i++)
    {
        for(j=0;j<11;j++)
        {
            mW=0;
            mE=0;
            for(k=j;k<j+5;k++)
            {
                if(chessMap[i][k]==WHITE)
                {
                    mW++;
                }
                else if(chessMap[i][k]==EMPTY)
                {
                    mE++;
                }
            }
            if(mW==3 && mE==2)
            {
                for(k=j;k<j+5;k++)
                {
                    if(chessMap[i][k]==EMPTY)
                    {
                        Map0[i][k]=3;
                    }
                }
            }
        }
    }
    //反斜线搜索
    for(i=0;i<11;i++)
    {
        for(j=0;j<11;j++)
        {
            mW=0;
            mE=0;
            for(k=0;k<5;k++)
            {
                if(chessMap[i+k][j+k]==WHITE)
                {
                    mW++;
                }
                else if(chessMap[i+k][j+k]==EMPTY)
                {
                    mE++;
                }
            }
            if(mW==3 && mE==2)
            {
                for(k=0;k<5;k++)
                {
                    if(chessMap[i+k][j+k]==EMPTY)
                    {
                        Map0[i+k][j+k]=3;
                    }
                }
            }
        }
    }
    //正斜线搜索
    for(i=4;i<15;i++)
    {
        for(j=0;j<11;j++)
        {
            mW=0;
            mE=0;
            for(k=0;k<5;k++)
            {
                if(chessMap[i-k][j+k]==WHITE)
                {
                    mW++;
                }
                else if(chessMap[i-k][j+k]==EMPTY)
                {
                    mE++;
                }
            }
            if(mW==3 && mE==2)
            {
                for(k=0;k<5;k++)
                {
                    if(chessMap[i-k][j+k]==EMPTY)
                    {
                        Map0[i-k][j+k]=3;
                    }
                }
            }
        }
    }

    //搜索己方活三（1冲四点+2白子）
    //竖线搜索
    for(i=0;i<10;i++)
    {
        for(j=0;j<15;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //用来表示白方冲四点数目
            for(k=i+1;k<i+5;k++)
            {
                if(Map0[k][j]==1)
                {
                    mW++;
                }
                else if(chessMap[k][j]==EMPTY)
                {
                    mE++;
                }
                if(Map0[k][j]==3)
                {
                    mQ++;
                }
            }
            if(mW==2 && mE==2 && mQ>=1 && chessMap[i][j]==EMPTY && chessMap[i+5][j]==EMPTY)
            {
                //未判断黑方是否有反（冲四）————待改进
                for(k=i+1;k<i+5;k++)
                {
                    if(Map0[k][j]==3)
                    {
                        row=k;
                        col=j;
                        return;
                    }
                }
            }
        }
    }
    //横线搜索
    for(i=0;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //用来表示白方冲四点数目
            for(k=j+1;k<j+5;k++)
            {
                if(Map0[i][k]==1)
                {
                    mW++;
                }
                else if(chessMap[i][k]==EMPTY)
                {
                    mE++;
                }
                if(Map0[i][k]==3)
                {
                    mQ++;
                }
            }
            if(mW==2 && mE==2 && mQ>=1 && chessMap[i][j]==EMPTY && chessMap[i][j+5]==EMPTY)
            {
                //未判断黑方是否有反（冲四）————待改进
                for(k=j+1;k<j+5;k++)
                {
                    if(Map0[i][k]==3)
                    {
                        row=i;
                        col=k;
                        return;
                    }
                }
            }
        }
    }
    //反斜线搜索
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //用来表示白方冲四点数目
            for(k=1;k<5;k++)
            {
                if(Map0[i+k][j+k]==1)
                {
                    mW++;
                }
                else if(chessMap[i+k][j+k]==EMPTY)
                {
                    mE++;
                }
                if(Map0[i+k][j+k]==3)
                {
                    mQ++;
                }
            }
            if(mW==2 && mE==2 && mQ>=1 && chessMap[i][j]==EMPTY && chessMap[i+5][j+5]==EMPTY)
            {
                //未判断黑方是否有反（冲四）————待改进
                for(k=1;k<5;k++)
                {
                    if(Map0[i+k][j+k]==3)
                    {
                        row=i+k;
                        col=j+k;
                        return;
                    }
                }
            }
        }
    }
    //正斜线搜索
    for(i=5;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //用来表示白方冲四点数目
            for(k=1;k<5;k++)
            {
                if(Map0[i-k][j+k]==1)
                {
                    mW++;
                }
                else if(chessMap[i-k][j+k]==EMPTY)
                {
                    mE++;
                }
                if(Map0[i-k][j+k]==3)
                {
                    mQ++;
                }
            }
            if(mW==2 && mE==2 && mQ>=1 && chessMap[i][j]==EMPTY && chessMap[i-5][j+5]==EMPTY)
            {
                //未判断黑方是否有反（冲四）————待改进
                for(k=1;k<5;k++)
                {
                    if(Map0[i-k][j+k]==3)
                    {
                        row=i-k;
                        col=j+k;
                        return;
                    }
                }
            }
        }
    }
    //搜索己方活三（2冲四点+1白子）
    //竖线搜索
    for(i=0;i<10;i++)
    {
        for(j=0;j<15;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //用来表示白方冲四点数目
            for(k=i+1;k<i+5;k++)
            {
                if(Map0[k][j]==1)
                {
                    mW++;
                }
                else if(chessMap[k][j]==EMPTY)
                {
                    mE++;
                }
                if(Map0[k][j]==3)
                {
                    mQ++;
                }
            }
            if(mW==1 && mE==3 && mQ>=2 && chessMap[i][j]==EMPTY && chessMap[i+5][j]==EMPTY)
            {
                //未判断黑方是否有反（冲四）————待改进
                for(k=i+1;k<i+5;k++)
                {
                    if(Map0[k][j]==3)
                    {
                        row=k;
                        col=j;
                        return;
                    }
                }
            }
        }
    }
    //横线搜索
    for(i=0;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //用来表示白方冲四点数目
            for(k=j+1;k<j+5;k++)
            {
                if(Map0[i][k]==1)
                {
                    mW++;
                }
                else if(chessMap[i][k]==EMPTY)
                {
                    mE++;
                }
                if(Map0[i][k]==3)
                {
                    mQ++;
                }
            }
            if(mW==1 && mE==3 && mQ>=2 && chessMap[i][j]==EMPTY && chessMap[i][j+5]==EMPTY)
            {
                //未判断黑方是否有反（冲四）————待改进
                for(k=i+1;k<i+5;k++)
                {
                    if(Map0[i][k]==3)
                    {
                        row=i;
                        col=k;
                        return;
                    }
                }
            }
        }
    }
    //反斜线搜索
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //用来表示白方冲四点数目
            for(k=1;k<5;k++)
            {
                if(Map0[i+k][j+k]==1)
                {
                    mW++;
                }
                else if(chessMap[i+k][j+k]==EMPTY)
                {
                    mE++;
                }
                if(Map0[i+k][j+k]==3)
                {
                    mQ++;
                }
            }
            if(mW==1 && mE==3 && mQ>=2 && chessMap[i][j]==EMPTY && chessMap[i+5][j+5]==EMPTY)
            {
                //未判断黑方是否有反（冲四）————待改进
                for(k=1;k<5;k++)
                {
                    if(Map0[i+k][j+k]==3)
                    {
                        row=i+k;
                        col=j+k;
                        return;
                    }
                }
            }
        }
    }
    //正斜线搜索
    for(i=5;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //用来表示白方冲四点数目
            for(k=1;k<5;k++)
            {
                if(Map0[i-k][j+k]==1)
                {
                    mW++;
                }
                else if(chessMap[i-k][j+k]==EMPTY)
                {
                    mE++;
                }
                if(Map0[i-k][j+k]==3)
                {
                    mQ++;
                }
            }
            if(mW==1 && mE==3 && mQ>=2 && chessMap[i][j]==EMPTY && chessMap[i-5][j+5]==EMPTY)
            {
                //未判断黑方是否有反（冲四）————待改进
                for(k=1;k<5;k++)
                {
                    if(Map0[i-k][j+k]==3)
                    {
                        row=i-k;
                        col=j+k;
                        return;
                    }
                }
            }
        }
    }
    //搜索己方活三（3冲四点+0白子）
    //竖线搜索
    for(i=0;i<10;i++)
    {
        for(j=0;j<15;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //用来表示白方冲四点数目
            for(k=i+1;k<i+5;k++)
            {
                if(Map0[k][j]==1)
                {
                    mW++;
                }
                else if(chessMap[k][j]==EMPTY)
                {
                    mE++;
                }
                if(Map0[k][j]==3)
                {
                    mQ++;
                }
            }
            if(mW==0 && mE==4 && mQ>=3 && chessMap[i][j]==EMPTY && chessMap[i+5][j]==EMPTY)
            {
                //未判断黑方是否有反（冲四）————待改进
                for(k=i+1;k<i+5;k++)
                {
                    if(Map0[k][j]==3)
                    {
                        row=k;
                        col=j;
                        return;
                    }
                }
            }
        }
    }
    //横线搜索
    for(i=0;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //用来表示白方冲四点数目
            for(k=j+1;k<j+5;k++)
            {
                if(Map0[i][k]==1)
                {
                    mW++;
                }
                else if(chessMap[i][k]==EMPTY)
                {
                    mE++;
                }
                if(Map0[i][k]==3)
                {
                    mQ++;
                }
            }
            if(mW==0 && mE==4 && mQ>=3 && chessMap[i][j]==EMPTY && chessMap[i][j+5]==EMPTY)
            {
                //未判断黑方是否有反（冲四）————待改进
                for(k=i+1;k<i+5;k++)
                {
                    if(Map0[i][k]==3)
                    {
                        row=i;
                        col=k;
                        return;
                    }
                }
            }
        }
    }
    //反斜线搜索
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //用来表示白方冲四点数目
            for(k=1;k<5;k++)
            {
                if(Map0[i+k][j+k]==1)
                {
                    mW++;
                }
                else if(chessMap[i+k][j+k]==EMPTY)
                {
                    mE++;
                }
                if(Map0[i+k][j+k]==3)
                {
                    mQ++;
                }
            }
            if(mW==0 && mE==4 && mQ>=3 && chessMap[i][j]==EMPTY && chessMap[i+5][j+5]==EMPTY)
            {
                //未判断黑方是否有反（冲四）————待改进
                for(k=1;k<5;k++)
                {
                    if(Map0[i+k][j+k]==3)
                    {
                        row=i+k;
                        col=j+k;
                        return;
                    }
                }
            }
        }
    }
    //正斜线搜索
    for(i=5;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //用来表示白方冲四点数目
            for(k=1;k<5;k++)
            {
                if(Map0[i-k][j+k]==1)
                {
                    mW++;
                }
                else if(chessMap[i-k][j+k]==EMPTY)
                {
                    mE++;
                }
                if(Map0[i-k][j+k]==3)
                {
                    mQ++;
                }
            }
            if(mW==0 && mE==4 && mQ>=3 && chessMap[i][j]==EMPTY && chessMap[i-5][j+5]==EMPTY)
            {
                //未判断黑方是否有反（冲四）————待改进
                for(k=1;k<5;k++)
                {
                    if(Map0[i-k][j+k]==3)
                    {
                        row=i-k;
                        col=j+k;
                        return;
                    }
                }
            }
        }
    }

    //应对BLACK活三

    //计算A/D/S价值
    int maxA,maxD,maxS;
    int xA,yA,xD,yD,xS,yS;
    int valueA[15][15],valueD[15][15],valueS[15][15];
    value_A(chessMap,0,valueA);
    value_B(chessMap,0,valueD);
    maxA=-1;
    maxD=-1;
    maxS=-1;
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            if(chessMap[i][j]!=EMPTY)
            {
                continue;
            }
            valueS[i][j]=valueA[i][j]+valueD[i][j];
            if(valueA[i][j]>maxA)
            {
                maxA=valueA[i][j];
                xA=i;
                yA=j;
            }
            if(valueD[i][j]>maxD)
            {
                maxD=valueD[i][j];
                xD=i;
                yD=j;
            }
            if(valueS[i][j]>maxS)
            {
                maxS=valueS[i][j];
                xS=i;
                yS=j;
            }
        }
    }
    //竖线搜索
    for(i=0;i<10;i++)
    {
        for(j=0;j<15;j++)
        {
            int x0,y0;
            mB=0;
            mE=0;
            for(k=i+1;k<i+5;k++)
            {
                if(chessMap[k][j]==BLACK)
                {
                    mB++;
                }
                else if(chessMap[k][j]==EMPTY)
                {
                    mE++;
                    x=k;
                    y=j;
                }
            }
            if(mB==3&&mE==1&&chessMap[i][j]==EMPTY&&chessMap[i+5][j]==EMPTY)
            {
                if(x==i+2||x==i+3)
                {
                    row=x;
                    col=y;
                    return;
                }
                else if(x==i+1)
                {
                    x0=i+5;
                    y0=j;
                    if(valueD[x][y]*2+valueA[x][y]>valueD[x0][y0]*2+valueA[x0][y0])
                    {
                        row=x;
                        col=y;
                        return;
                    }
                    else
                    {
                        row=x0;
                        col=y0;
                        return;
                    }
                }
                else if(x==i+4)
                {
                    x0=i;
                    y0=j;
                    if(valueD[x][y]*2+valueA[x][y]>valueD[x0][y0]*2+valueA[x0][y0])
                    {
                        row=x;
                        col=y;
                        return;
                    }
                    else
                    {
                        row=x0;
                        col=y0;
                        return;
                    }
                }
            }
        }
    }
    //横线搜索
    for(i=0;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            int x0,y0;
            mB=0;
            mE=0;
            for(k=j+1;k<j+5;k++)
            {
                if(chessMap[i][k]==BLACK)
                {
                    mB++;
                }
                else if(chessMap[i][k]==EMPTY)
                {
                    mE++;
                    x=i;
                    y=k;
                }
            }
            if(mB==3&&mE==1&&chessMap[i][j]==EMPTY&&chessMap[i][j+5]==EMPTY)
            {
                if(y==j+2||y==j+3)
                {
                    row=x;
                    col=y;
                    return;
                }
                else if(y==j+1)
                {
                    x0=i;
                    y0=j+5;
                    if(valueD[x][y]*2+valueA[x][y]>valueD[x0][y0]*2+valueA[x0][y0])
                    {
                        row=x;
                        col=y;
                        return;
                    }
                    else
                    {
                        row=x0;
                        col=y0;
                        return;
                    }
                }
                else if(y==j+4)
                {
                    x0=i;
                    y0=j;
                    if(valueD[x][y]*2+valueA[x][y]>valueD[x0][y0]*2+valueA[x0][y0])
                    {
                        row=x;
                        col=y;
                        return;
                    }
                    else
                    {
                        row=x0;
                        col=y0;
                        return;
                    }
                }
            }
        }
    }
    //反斜线搜索
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            int x0,y0;
            mB=0;
            mE=0;
            for(k=1;k<5;k++)
            {
                if(chessMap[i+k][j+k]==BLACK)
                {
                    mB++;
                }
                else if(chessMap[i+k][j+k]==EMPTY)
                {
                    mE++;
                    x=i+k;
                    y=j+k;
                }
            }
            if(mB==3&&mE==1&&chessMap[i][j]==EMPTY&&chessMap[i+5][j+5]==EMPTY)
            {
                if(y==j+2||y==j+3)
                {
                    row=x;
                    col=y;
                    return;
                }
                else if(y==j+1)
                {
                    x0=i+5;
                    y0=j+5;
                    if(valueD[x][y]*2+valueA[x][y]>valueD[x0][y0]*2+valueA[x0][y0])
                    {
                        row=x;
                        col=y;
                        return;
                    }
                    else
                    {
                        row=x0;
                        col=y0;
                        return;
                    }
                }
                else if(y==j+4)
                {
                    x0=i;
                    y0=j;
                    if(valueD[x][y]*2+valueA[x][y]>valueD[x0][y0]*2+valueA[x0][y0])
                    {
                        row=x;
                        col=y;
                        return;
                    }
                    else
                    {
                        row=x0;
                        col=y0;
                        return;
                    }
                }
            }
        }
    }
    //正斜线搜索
    for(i=5;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            int x0,y0;
            mB=0;
            mE=0;
            for(k=1;k<5;k++)
            {
                if(chessMap[i-k][j+k]==BLACK)
                {
                    mB++;
                }
                else if(chessMap[i-k][j+k]==EMPTY)
                {
                    mE++;
                    x=i-k;
                    y=j+k;
                }
            }
            if(mB==3&&mE==1&&chessMap[i][j]==EMPTY&&chessMap[i-5][j+5]==EMPTY)
            {
                if(y==j+2||y==j+3)
                {
                    row=x;
                    col=y;
                    return;
                }
                else if(y==j+1)
                {
                    x0=i-5;
                    y0=j+5;
                    if(valueD[x][y]*2+valueA[x][y]>valueD[x0][y0]*2+valueA[x0][y0])
                    {
                        row=x;
                        col=y;
                        return;
                    }
                    else
                    {
                        row=x0;
                        col=y0;
                        return;
                    }
                }
                else if(y==j+4)
                {
                    x0=i;
                    y0=j;
                    if(valueD[x][y]*2+valueA[x][y]>valueD[x0][y0]*2+valueA[x0][y0])
                    {
                        row=x;
                        col=y;
                        return;
                    }
                    else
                    {
                        row=x0;
                        col=y0;
                        return;
                    }
                }
            }
        }
    }

    //应对BLACK四四
    int map4B[15][15];   //To Four参数-B
    MAP4(chessMap,2,map4B);
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            if(map4B[i][j]>1)
            {
                row=i;
                col=j;
                return;
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
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            if(chessMap[i][j]==EMPTY)
            {
                Map0[i][j]=0;
            }
            else if(chessMap[i][j]==WHITE)
            {
                Map0[i][j]=1;
            }
            else if(chessMap[i][j]==BLACK)
            {
                Map0[i][j]=2;
            }
        }
    }
    //搜索BLACK冲四点
    //竖线搜索
    for(i=0;i<11;i++)
    {
        for(j=0;j<15;j++)
        {
            mE=0;
            mB=0;
            for(k=i;k<i+5;k++)
            {
                if(chessMap[k][j]==BLACK)
                {
                    mB++;
                }
                else if(chessMap[k][j]==EMPTY)
                {
                    mE++;
                }
            }
            if(mB==3 && mE==2)
            {
                for(k=i;k<i+5;k++)
                {
                    if(chessMap[k][j]==EMPTY)
                    {
                        Map0[k][j]=3;
                    }
                }
            }
        }
    }
    //横线搜索
    for(i=0;i<15;i++)
    {
        for(j=0;j<11;j++)
        {
            mB=0;
            mE=0;
            for(k=j;k<j+5;k++)
            {
                if(chessMap[i][k]==BLACK)
                {
                    mB++;
                }
                else if(chessMap[i][k]==EMPTY)
                {
                    mE++;
                }
            }
            if(mB==3 && mE==2)
            {
                for(k=j;k<j+5;k++)
                {
                    if(chessMap[i][k]==EMPTY)
                    {
                        Map0[i][k]=3;
                    }
                }
            }
        }
    }
    //反斜线搜索
    for(i=0;i<11;i++)
    {
        for(j=0;j<11;j++)
        {
            mB=0;
            mE=0;
            for(k=0;k<5;k++)
            {
                if(chessMap[i+k][j+k]==BLACK)
                {
                    mB++;
                }
                else if(chessMap[i+k][j+k]==EMPTY)
                {
                    mE++;
                }
            }
            if(mB==3 && mE==2)
            {
                for(k=0;k<5;k++)
                {
                    if(chessMap[i+k][j+k]==EMPTY)
                    {
                        Map0[i+k][j+k]=3;
                    }
                }
            }
        }
    }
    //正斜线搜索
    for(i=4;i<15;i++)
    {
        for(j=0;j<11;j++)
        {
            mB=0;
            mE=0;
            for(k=0;k<5;k++)
            {
                if(chessMap[i-k][j+k]==BLACK)
                {
                    mB++;
                }
                else if(chessMap[i-k][j+k]==EMPTY)
                {
                    mE++;
                }
            }
            if(mB==3 && mE==2)
            {
                for(k=0;k<5;k++)
                {
                    if(chessMap[i-k][j+k]==EMPTY)
                    {
                        Map0[i-k][j+k]=3;
                    }
                }
            }
        }
    }
    //搜索对方活三（1冲四点+2黑子）
    //竖线搜索
    for(i=0;i<10;i++)
    {
        for(j=0;j<15;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //用来表示黑方冲四点数目
            for(k=i+1;k<i+5;k++)
            {
                if(Map0[k][j]==2)
                {
                    mB++;
                }
                else if(chessMap[k][j]==EMPTY)
                {
                    mE++;
                }
                if(Map0[k][j]==3)
                {
                    mQ++;
                }
            }
            if(mB==2 && mE==2 && mQ>=1 && chessMap[i][j]==EMPTY && chessMap[i+5][j]==EMPTY)
            {
                //未判断白方是否有反（冲四）————待改进
                for(k=i+1;k<i+5;k++)
                {
                    if(Map0[k][j]==3)
                    {
                        row=k;
                        col=j;
                        return;
                    }
                }
            }
        }
    }
    //横线搜索
    for(i=0;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //用来表示黑方冲四点数目
            for(k=j+1;k<j+5;k++)
            {
                if(Map0[i][k]==2)
                {
                    mB++;
                }
                else if(chessMap[i][k]==EMPTY)
                {
                    mE++;
                }
                if(Map0[i][k]==3)
                {
                    mQ++;
                }
            }
            if(mB==2 && mE==2 && mQ>=1 && chessMap[i][j]==EMPTY && chessMap[i][j+5]==EMPTY)
            {
                //未判断白方是否有反（冲四）————待改进
                for(k=j+1;k<j+5;k++)
                {
                    if(Map0[i][k]==3)
                    {
                        row=i;
                        col=k;
                        return;
                    }
                }
            }
        }
    }
    //反斜线搜索
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //用来表示黑方冲四点数目
            for(k=1;k<5;k++)
            {
                if(Map0[i+k][j+k]==2)
                {
                    mB++;
                }
                else if(chessMap[i+k][j+k]==EMPTY)
                {
                    mE++;
                }
                if(Map0[i+k][j+k]==3)
                {
                    mQ++;
                }
            }
            if(mB==2 && mE==2 && mQ>=1 && chessMap[i][j]==EMPTY && chessMap[i+5][j+5]==EMPTY)
            {
                //未判断白方是否有反（冲四）————待改进
                for(k=1;k<5;k++)
                {
                    if(Map0[i+k][j+k]==3)
                    {
                        row=i+k;
                        col=j+k;
                        return;
                    }
                }
            }
        }
    }
    //正斜线搜索
    for(i=5;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //用来表示黑方冲四点数目
            for(k=1;k<5;k++)
            {
                if(Map0[i-k][j+k]==2)
                {
                    mB++;
                }
                else if(chessMap[i-k][j+k]==EMPTY)
                {
                    mE++;
                }
                if(Map0[i-k][j+k]==3)
                {
                    mQ++;
                }
            }
            if(mB==2 && mE==2 && mQ>=1 && chessMap[i][j]==EMPTY && chessMap[i-5][j+5]==EMPTY)
            {
                //未判断白方是否有反（冲四）————待改进
                for(k=1;k<5;k++)
                {
                    if(Map0[i-k][j+k]==3)
                    {
                        row=i-k;
                        col=j+k;
                        return;
                    }
                }
            }
        }
    }
    //搜索对方活三（2冲四点+1黑子）
    //竖线搜索
    for(i=0;i<10;i++)
    {
        for(j=0;j<15;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //用来表示黑方冲四点数目
            for(k=i+1;k<i+5;k++)
            {
                if(Map0[k][j]==2)
                {
                    mB++;
                }
                else if(chessMap[k][j]==EMPTY)
                {
                    mE++;
                }
                if(Map0[k][j]==3)
                {
                    mQ++;
                }
            }
            if(mB==1 && mE==3 && mQ>=2 && chessMap[i][j]==EMPTY && chessMap[i+5][j]==EMPTY)
            {
                //未判断白方是否有反（冲四）————待改进
                for(k=i+1;k<i+5;k++)
                {
                    if(Map0[k][j]==3)
                    {
                        row=k;
                        col=j;
                        return;
                    }
                }
            }
        }
    }
    //横线搜索
    for(i=0;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //用来表示黑方冲四点数目
            for(k=j+1;k<j+5;k++)
            {
                if(Map0[i][k]==2)
                {
                    mB++;
                }
                else if(chessMap[i][k]==EMPTY)
                {
                    mE++;
                }
                if(Map0[i][k]==3)
                {
                    mQ++;
                }
            }
            if(mB==1 && mE==3 && mQ>=2 && chessMap[i][j]==EMPTY && chessMap[i][j+5]==EMPTY)
            {
                //未判断白方是否有反（冲四）————待改进
                for(k=i+1;k<i+5;k++)
                {
                    if(Map0[i][k]==3)
                    {
                        row=i;
                        col=k;
                        return;
                    }
                }
            }
        }
    }
    //反斜线搜索
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //用来表示黑方冲四点数目
            for(k=1;k<5;k++)
            {
                if(Map0[i+k][j+k]==2)
                {
                    mB++;
                }
                else if(chessMap[i+k][j+k]==EMPTY)
                {
                    mE++;
                }
                if(Map0[i+k][j+k]==3)
                {
                    mQ++;
                }
            }
            if(mB==1 && mE==3 && mQ>=2 && chessMap[i][j]==EMPTY && chessMap[i+5][j+5]==EMPTY)
            {
                //未判断白方是否有反（冲四）————待改进
                for(k=1;k<5;k++)
                {
                    if(Map0[i+k][j+k]==3)
                    {
                        row=i+k;
                        col=j+k;
                        return;
                    }
                }
            }
        }
    }
    //正斜线搜索
    for(i=5;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //用来表示黑方冲四点数目
            for(k=1;k<5;k++)
            {
                if(Map0[i-k][j+k]==2)
                {
                    mB++;
                }
                else if(chessMap[i-k][j+k]==EMPTY)
                {
                    mE++;
                }
                if(Map0[i-k][j+k]==3)
                {
                    mQ++;
                }
            }
            if(mB==1 && mE==3 && mQ>=2 && chessMap[i][j]==EMPTY && chessMap[i-5][j+5]==EMPTY)
            {
                //未判断白方是否有反（冲四）————待改进
                for(k=1;k<5;k++)
                {
                    if(Map0[i-k][j+k]==3)
                    {
                        row=i-k;
                        col=j+k;
                        return;
                    }
                }
            }
        }
    }
    //搜索对方活三（3冲四点+0黑子）
    //竖线搜索
    for(i=0;i<10;i++)
    {
        for(j=0;j<15;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //用来表示黑方冲四点数目
            for(k=i+1;k<i+5;k++)
            {
                if(Map0[k][j]==2)
                {
                    mB++;
                }
                else if(chessMap[k][j]==EMPTY)
                {
                    mE++;
                }
                if(Map0[k][j]==3)
                {
                    mQ++;
                }
            }
            if(mB==0 && mE==4 && mQ>=3 && chessMap[i][j]==EMPTY && chessMap[i+5][j]==EMPTY)
            {
                //未判断白方是否有反（冲四）————待改进
                for(k=i+1;k<i+5;k++)
                {
                    if(Map0[k][j]==3)
                    {
                        row=k;
                        col=j;
                        return;
                    }
                }
            }
        }
    }
    //横线搜索
    for(i=0;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //用来表示黑方冲四点数目
            for(k=j+1;k<j+5;k++)
            {
                if(Map0[i][k]==2)
                {
                    mB++;
                }
                else if(chessMap[i][k]==EMPTY)
                {
                    mE++;
                }
                if(Map0[i][k]==3)
                {
                    mQ++;
                }
            }
            if(mB==0 && mE==4 && mQ>=3 && chessMap[i][j]==EMPTY && chessMap[i][j+5]==EMPTY)
            {
                //未判断白方是否有反（冲四）————待改进
                for(k=i+1;k<i+5;k++)
                {
                    if(Map0[i][k]==3)
                    {
                        row=i;
                        col=k;
                        return;
                    }
                }
            }
        }
    }
    //反斜线搜索
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //用来表示黑方冲四点数目
            for(k=1;k<5;k++)
            {
                if(Map0[i+k][j+k]==2)
                {
                    mB++;
                }
                else if(chessMap[i+k][j+k]==EMPTY)
                {
                    mE++;
                }
                if(Map0[i+k][j+k]==3)
                {
                    mQ++;
                }
            }
            if(mB==0 && mE==4 && mQ>=3 && chessMap[i][j]==EMPTY && chessMap[i+5][j+5]==EMPTY)
            {
                //未判断白方是否有反（冲四）————待改进
                for(k=1;k<5;k++)
                {
                    if(Map0[i+k][j+k]==3)
                    {
                        row=i+k;
                        col=j+k;
                        return;
                    }
                }
            }
        }
    }
    //正斜线搜索
    for(i=5;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //用来表示黑方冲四点数目
            for(k=1;k<5;k++)
            {
                if(Map0[i-k][j+k]==2)
                {
                    mB++;
                }
                else if(chessMap[i-k][j+k]==EMPTY)
                {
                    mE++;
                }
                if(Map0[i-k][j+k]==3)
                {
                    mQ++;
                }
            }
            if(mB==0 && mE==4 && mQ>=3 && chessMap[i][j]==EMPTY && chessMap[i-5][j+5]==EMPTY)
            {
                //未判断白方是否有反（冲四）————待改进
                for(k=1;k<5;k++)
                {
                    if(Map0[i-k][j+k]==3)
                    {
                        row=i-k;
                        col=j+k;
                        return;
                    }
                }
            }
        }
    }

    //搜索己方冲三点
    int map3W[15][15];   //To Three参数-W
    MAP3(chessMap,1,map3W);

    //双三杀
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            if(map3W[i][j]>1)
            {
                row=i;
                col=j;
                return;
            }
        }
    }
    //防双三杀
    int map3B[15][15];   //To Three参数-B
    MAP3(chessMap,2,map3B);
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            if(map3B[i][j]>1)
            {
                row=i;
                col=j;
                return;
            }
        }
    }

    //白方做棋

    if(maxD>140)
    {
        row=xD;
        col=yD;
        return;
    }

    while(1)
    {
        int rand0=random(100);
        for(i=0;i<15;i++)
        {
            for(j=0;j<15;j++)
            {
                if(chessMap[i][j]==EMPTY && valueS[i][j]>=maxS)
                {
                    rand0--;
                    if(rand0==0)
                    {
                        row=i;
                        col=j;
                        return;
                    }
                }
            }
        }
    }

    //
    while(1){
        int i = random(MAP_SIZE);
        int j = random(MAP_SIZE);
        if(chessMap[i][j] == EMPTY){
            row = i;
            col = j;
            break;
        }
    }
    //



}

/**
 *  @brief  计算指定坐标处的价值
 *  @param  pt  坐标
 *  @return 价值
 *  这里方案是由指定处的“米”字范围的子计算出来
 */
int CalcPointValue(point_t pt)
{
	// “米”字，每个元素表示与中心坐标的偏移
	static const point_t d[8][3] = {
		{{-1, 0}, {-2, 0}, {-3, 0}}, {{+1, 0}, {+2, 0}, {+3, 0}},
		{{ 0,-1}, { 0,-2}, { 0,-3}}, {{ 0,+1}, { 0,+2}, { 0,+3}},
		{{+1,-1}, {+2,-2}, {+3,-3}}, {{-1,-1}, {-2,-2}, {-3,-3}},
		{{+1,+1}, {+2,+2}, {+3,+3}}, {{-1,+1}, {-2,+2}, {-3,+3}}};

	int i, j;
	int sum = 0;

	// 这个估值的想法是：
	// 从起点向外走，同色时价值翻番，异色时停止
	// 汇总八个方向的所有的偏移坐标计算出价值和
	for (i = 0; i < sizeof(d) / sizeof(d[0]); ++i) {
		enum Stone stn = kStnNo;
		int value = 1;

		for (j = 0; j < sizeof(d[0]) / sizeof(d[0][0]); ++j) {
			point_t o;
			o.x = pt.x + d[i][j].x, o.y = pt.y + d[i][j].y;

			if (!BoardHasPoint(o)) {
				break;
			} else if (stn == kStnNo) {
				stn = BoardGet(o);
			} else if (stn == BoardGet(o)) {
				value *= 2;
			} else {
				break;
			}
		}

		sum += value;
	}

	return sum;
}


/**
 *  @brief  搜索最佳点
 *  @return 位置坐标
 */
point_t SearchBestPoint(void)
{
	ChessType map[MAP_SIZE][MAP_SIZE]={EMPTY};
	int row=0, col=0;
	point_t pt;
	Stone stn;
	for(int i=0;i<MAP_SIZE;++i)
	{
	    for(int j=0;j<MAP_SIZE;++j)
	    {
	        pt.x = j;
	        pt.y = i;
	        stn = BoardGet(pt);
	        //enum Stone {kStnNo, kStnAi, kStnOp};
	        if(stn == kStnNo)
	        {
	            map[i][j]=EMPTY;
	        }
	        else if(stn == kStnAi)
	        {
	            map[i][j]=WHITE;
	        }
	        else if(stn == kStnOp)
	        {
	            map[i][j]=BLACK;
	        }
	        else
	        {
	            map[i][j]=EMPTY;
	        }
	    }
	}
	nextMove(map,row,col);
	pt.x = col;
	pt.y = row;
	return pt;
}

// 输出命令 //////////////////////////////////////////////////////////////////

/**
 *  @brief  输出一行命令
 *  @param  cmd 命令
 *  @param  fmt 格式
 *  @param  va  变参
 *  @note   串中换行会被空格取代，串尾会附加一个换行
 */
void PrintCmd(const char *cmd, const char *fmt, va_list va)
{
	char buf[4 * 1024];  // 缓冲

	// 前缀命令，中间空格，后继为格式化输出
	strcpy(buf, cmd);
	strcat(buf, buf[0] == '\0' ? "" : " ");
	vsprintf(&buf[strlen(buf)], fmt, va);

	// 替换串中所有回车换行符
	while (1) {
		char *p = strpbrk(buf, "\r\n");

		if (p != NULL) {
			*p = ' ';  // 换为空格
		} else {
			break;  // 完毕跳出
		}
	}

	// 打印到标准输出
	puts(buf);  // 输出并换行
	fflush(stdout);  // 注意防止输出缓存
}

/**
 *  @brief  输出一行
 *  @param  fmt 格式
 */
void Print(const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	PrintCmd("", fmt, va);
	va_end(va);
}

/**
 *  @brief  输出 UNKNOWN 命令
 *  @param  fmt 格式
 */
void PrintUnknown(const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	PrintCmd("UNKNOWN", fmt, va);
	va_end(va);
}

/**
 *  @brief  输出 ERROR 命令
 *  @param  fmt 格式
 */
void PrintError(const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	PrintCmd("ERROR", fmt, va);
	va_end(va);
}

/**
 *  @brief  输出 MESSAGE 命令
 *  @param  fmt 格式
 */
void PrintMessage(const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	PrintCmd("MESSAGE", fmt, va);
	va_end(va);
}

/**
 *  @brief  输出 DEBUG 命令
 *  @param  fmt 格式
 */
void PrintDebug(const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	PrintCmd("DEBUG", fmt, va);
	va_end(va);
}

/**
 *  @brief  输出 SUGGEST 命令
 *  @param  x   Ｘ坐标
 *  @param  y   Ｙ坐标
 */
void PrintSuggest(int x, int y)
{
	Print("SUGGEST %d,%d", x, y);
}

// 命令处理 //////////////////////////////////////////////////////////////////

/**
 *  @brief  判断缓冲中是否为指定命令
 *  @param  buf 缓冲
 *  @param  cmd 命令，20字符为限
 *  @return 是否
 */
BOOL IsCmd(const char *buf, const char *cmd)
{
	char src[21], dst[21];
	int i, n;

	// 从缓冲读取源命令
	if (sscanf(buf, "%20s", src) != 1) {
		return FALSE;
	}

	// 将源命令转为大写
	for (n = strlen(src), i = 0; i < n; ++i) {
		src[i] = toupper(src[i]);
	}

	// 获取目标大写字符
	for (n = strlen(cmd), i = 0; i < n; ++i) {
		dst[i] = toupper(cmd[i]);
	}

	dst[n] = '\0';  // 尾零

	// 两个命令是否相等
	return strcmp(src, dst) == 0;
}

/**
 *  @brief  处理 STRAT 命令
 *  @param  buf 命令行缓冲
 */
void CmdStart(char *buf)
{
	int size;

	// 获取参数
	if (sscanf(buf, "%*s%d", &size) != 1) {
		PrintError("bad START parameter");
		return;
	}

	// 重设大小
	if (!BoardResize(size, size)) {
		PrintError("%d < width < %d  %d < height < %d",
			WIDTH_MIN, WIDTH_MAX, HEIGHT_MIN, HEIGHT_MAX);
		return;
	}

	BoardReset();  // 清空复位
	Print("OK");  // 成功回应
}

/**
 *  @brief  处理 TURN 命令
 *  @param  buf 命令行缓冲
 */
void CmdTurn(char *buf)
{
	int x, y;
	point_t pt;

	// 获取参数
	if (sscanf(buf, "%*s%d,%d", &x, &y) != 2) {
		PrintError("bad TURN parameters");
		return;
	}

	pt.x = x, pt.y = y;

	// 检查对手落子位置
	if (!BoardHasPoint(pt) || BoardGet(pt) != kStnNo) {
		PrintError("bad coordinates");
		return;
	}

	// 计算对应并返回
	BoardSet(pt, kStnOp);  // 对手落子

	pt = SearchBestPoint();  // 本方着法

	if (g_is_suggest) {
		PrintSuggest(pt.x, pt.y);  // 回应坐标
	} else {
		BoardSet(pt, kStnAi);  // 本方落子
		Print("%d,%d", pt.x, pt.y);  // 回应坐标
	}
}

/**
 *  @brief  处理 BEGIN 命令
 *  @param  buf 命令行缓冲
 */
void CmdBegin(char *buf)
{
	point_t pt = SearchBestPoint();  // 本方着法
	BoardSet(pt, kStnAi);  // 本方落子
	Print("%d,%d", pt.x, pt.y);  // 回应坐标
}

/**
 *  @brief  处理 BOARD 命令
 *  @param  buf 命令行缓冲
 */
void CmdBoard(char *buf)
{
	point_t pt;

	// 读取棋谱直至DONE
	while (gets(buf), !IsCmd(buf, "DONE")) {
		int x, y, field = 0;

		sscanf(buf, "%d,%d,%d", &x, &y, &field);
		pt.x = x, pt.y = y;

		// 检查布子位置
		if (BoardHasPoint(pt)) {
			// 布子
			switch (field) {
			case 1: BoardSet(pt, kStnAi); break;
			case 2: BoardSet(pt, kStnOp); break;
			default: break;
			}
		}
	}

	// 计算对应并返回
	pt = SearchBestPoint();  // 本方着法
	BoardSet(pt, kStnAi);  // 本方落子
	Print("%d,%d", pt.x, pt.y);  // 回应坐标
}

/**
 *  @brief  处理 INFO 命令
 *  @param  buf 命令行缓冲
 */
void CmdInfo(char *buf)
{
	char *key, *val;

	// 按空格分割出键值对
	strtok(buf, " ");
	key = strtok(NULL, " ");
	val = strtok(NULL, " ");

	// 保存配置
	if (key == NULL || val == NULL) {}  // 无参数不作处理
	else if (IsCmd(key, "timeout_turn" )) { g_info.timeout_turn  = atoi(val); }
	else if (IsCmd(key, "timeout_match")) { g_info.timeout_match = atoi(val); }
	else if (IsCmd(key, "max_memory"   )) { g_info.max_memory    = atoi(val); }
	else if (IsCmd(key, "time_left"    )) { g_info.time_left     = atoi(val); }
	else if (IsCmd(key, "game_type"    )) { g_info.game_type     = atoi(val); }
	else if (IsCmd(key, "rule"         )) { g_info.rule          = atoi(val); }
	else if (IsCmd(key, "folder"       )) { strcpy(g_info.folder, val); }

	// 无需回应
}

/**
 *  @brief  处理 ABOUT 命令
 *  @param  buf 命令行缓冲
 */
void CmdAbout(char *buf)
{
	Print(
		"name=\"SLSNGR\", "
		"version=\"1.0.1\", "
		"author=\"ssr\", "
		"country=\"China\", "
		"email=\"602359470@qq.com\""
	);
}

/**
 *  @brief  处理 RECTSTART 命令
 *  @param  buf 命令行缓冲
 */
void CmdRectStart(char *buf)
{
	int width, height;

	// 获取参数
	if (sscanf(buf, "%*s%d%d", &width, &height) != 2) {
		PrintError("bad RECTSTART parameters");
		return;
	}

	// 重设大小
	if (!BoardResize(width, height)) {
		PrintError("%d < width < %d  %d < height < %d",
			WIDTH_MIN, WIDTH_MAX, HEIGHT_MIN, HEIGHT_MAX);
		return;
	}

	BoardReset();  // 清空复位
	Print("OK");  // 成功回应
}

/**
 *  @brief  处理 RESTART 命令
 *  @param  buf 命令行缓冲
 */
void CmdRestart(char *buf)
{
	BoardReset();  // 清空复位
	Print("OK");  // 成功回应
}

/**
 *  @brief  处理 TAKEBACK 命令
 *  @param  buf 命令行缓冲
 */
void CmdTakeback(char *buf)
{
	int x, y;
	point_t pt;

	// 获取参数
	if (sscanf(buf, "%*s%d,%d", &x, &y) != 2) {
		PrintError("bad TAKEBACK parameters");
		return;
	}

	pt.x = x, pt.y = y;

	// 检查提子位置
	if (!BoardHasPoint(pt)) {
		PrintError("bad coordinates");
		return;
	}

	BoardSet(pt, kStnNo);  // 提子
	Print("OK");  // 成功回应
}

/**
 *  @brief  处理 PLAY 命令
 *  @param  buf 命令行缓冲
 */
void CmdPlay(char *buf)
{
	int x, y;
	point_t pt;

	// 获取参数
	if (sscanf(buf, "%*s%d,%d", &x, &y) != 2) {
		PrintError("bad PLAY parameters");
		return;
	}

	pt.x = x, pt.y = y;

	// 检查本方落子位置
	if (!BoardHasPoint(pt) || BoardGet(pt) != kStnNo) {
		PrintError("bad coordinates");
		return;
	}

	BoardSet(pt, kStnAi);  // 本方落子
	Print("%d,%d", pt.x, pt.y);  // 回应坐标
}

// 通信交互 //////////////////////////////////////////////////////////////////

/**
 *  @brief  主函数
 *  @return 程序执行结果
 */
int main(void)
{
	if (TRUE) {  // TODO: 判断程序是由Piskvork调用还是直接运行
		// 提示信息
		PrintMessage(
			"Gomoku AI should not be started directly. "
			"Please install gomoku manager "
			"(http://sourceforge.net/projects/piskvork). "
			"Then enter path to this exe file in players settings.");
	}

	// 过程就是根据输入进行输出
	while (1) {
		char buf[1024];  // 行缓冲
		gets(buf);  // 从标准输入读入一行

		// 根据不同的命令进行不同的处理
		if (IsCmd(buf, "END")) { break; }  // 结束周转
		else if (IsCmd(buf, "START"    )) { CmdStart    (buf); }  // 必备
		else if (IsCmd(buf, "TURN"     )) { CmdTurn     (buf); }  // 必备
		else if (IsCmd(buf, "BEGIN"    )) { CmdBegin    (buf); }  // 必备
		else if (IsCmd(buf, "BOARD"    )) { CmdBoard    (buf); }  // 必备
		else if (IsCmd(buf, "INFO"     )) { CmdInfo     (buf); }  // 必备
		else if (IsCmd(buf, "ABOUT"    )) { CmdAbout    (buf); }  // 必备
	//	else if (IsCmd(buf, "RECTSTART")) { CmdRectStart(buf); }  // 可选
		else if (IsCmd(buf, "RESTART"  )) { CmdRestart  (buf); }  // 可选
		else if (IsCmd(buf, "TAKEBACK" )) { CmdTakeback (buf); }  // 可选
		else if (IsCmd(buf, "PLAY"     )) { CmdPlay     (buf); }  // 可选
		else { PrintUnknown("%s", buf); }  // 未知命令
	}

	return 0;
}
