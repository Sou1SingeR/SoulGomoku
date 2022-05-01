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

// ȫ�ֱ��� //////////////////////////////////////////////////////////////////

// ���̵����ݽṹ
// ��һά�Ǹߣ��ڶ�ά�ǿ�
enum Stone g_board[HEIGHT_MAX][WIDTH_MAX];

// ����ʵ��ʹ�õĳߴ缰Ĭ��ֵ
int g_width = 20, g_height = 20;

// �Ƿ���� SUGGEST ��Ӧ
BOOL g_is_suggest = FALSE;

// ����
struct {
	int timeout_turn  ;  // ��ʱ
	int timeout_match ;  // ��ʱ
	int max_memory    ;  // �ڴ�
	int time_left     ;  // ��ʱ
	int game_type     ;  // ����
	int rule          ;  // ����
	char folder[FILENAME_MAX];  // Ŀ¼
} g_info;

// ���̲��� //////////////////////////////////////////////////////////////////

/**
 *  @brief  �����̶�ȡ����
 *  @param  pt  ����
 *  @return ��������
 */
enum Stone BoardGet(point_t pt)
{
	return g_board[pt.y][pt.x];
}

/**
 *  @brief  ��������������
 *  @param  pt  ����
 *  @param  stn ��������
 */
void BoardSet(point_t pt, enum Stone stn)
{
	g_board[pt.y][pt.x] = stn;
}

/**
 *  @brief  �������
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
 *  @brief  �������̳ߴ�
 *  @param  width   ��
 *  @param  height  ��
 *  @return �ɹ����
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
 *  @brief  �ж������Ƿ�������ʹ�÷�Χ��
 *  @param  pt  ����
 *  @return �Ƿ�����
 */
BOOL BoardHasPoint(point_t pt)
{
	return 0 <= pt.x && pt.x < g_width
	    && 0 <= pt.y && pt.y < g_height;
}

// �㷨��� //////////////////////////////////////////////////////////////////

//To Three����
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
    //��������
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
    //��������
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
    //��б������
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
    //��б������
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

//To Four����
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
    //��������
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
    //��������
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
    //��б������
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
    //��б������
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


//valueD��
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
//valueA��
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
//valueD����
void value_B(ChessType chessMap[15][15],int x,int valueMap[15][15]){
    int p;
    memset(valueMap,0,sizeof(int)*225);
    ChessType str[4]={EMPTY};
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            if(i-1>=0){
                if(j-1>=0 && chessMap[i-1][j-1]!=EMPTY){//����1�㲢һ�㲻Ϊ��
                    for(p=0;p<4;p++){
                        if((i-1-p)<0 || (j-1-p)<0)break;
                        str[p]=chessMap[i-1-p][j-1-p];
                    }
                    valueMap[i][j]+=table_B(str,x);//�ۼƵ��ӷ���ֵ
                    memset(str,EMPTY,sizeof(str));
                }
                if(chessMap[i-1][j]!=EMPTY){//2����ڲ���Ϊ��
                    for(p=0;p<4;p++){
                        if((i-1-p)<0)break;
                        str[p]=chessMap[i-1-p][j];
                    }
                    valueMap[i][j]+=table_B(str,x);//�ۼƵ��ӷ���ֵ
                    memset(str,EMPTY,sizeof(str));
                }
                if(j+1<15 && chessMap[i-1][j+1]!=EMPTY){//3����ڲ���Ϊ��
                    for(p=0;p<4;p++){
                        if((i-1-p)<0 || (j+1+p)>14)break;
                        str[p]=chessMap[i-1-p][j+1+p];
                    }
                    valueMap[i][j]+=table_B(str,x);//�ۼƵ��ӷ���ֵ
                    memset(str,EMPTY,sizeof(str));
                }
            }
            if(j+1<15){
                if(chessMap[i][j+1]!=EMPTY){//4����ڲ���Ϊ��
                    for(p=0;p<4;p++){
                        if((j+1+p)>14)break;
                        str[p]=chessMap[i][j+1+p];
                    }
                    valueMap[i][j]+=table_B(str,x);//�ۼƵ��ӷ���ֵ
                    memset(str,EMPTY,sizeof(str));
                }
                if(i+1<15 && chessMap[i+1][j+1]!=EMPTY){//5����ڲ���Ϊ��
                    for(p=0;p<4;p++){
                        if((i+1+p)>14 || (j+1+p)>14)break;
                        str[p]=chessMap[i+1+p][j+1+p];
                    }
                    valueMap[i][j]+=table_B(str,x);//�ۼƵ��ӷ���ֵ
                    memset(str,EMPTY,sizeof(str));
                }
            }
            if(i+1<15){
                if(chessMap[i+1][j]!=EMPTY){//6����ڲ���Ϊ��
                    for(p=0;p<4;p++){
                        if((i+1+p)>14)break;
                        str[p]=chessMap[i+1+p][j];
                    }
                    valueMap[i][j]+=table_B(str,x);//�ۼƵ��ӷ���ֵ
                    memset(str,EMPTY,sizeof(str));
                }
                if(j-1>=0 && chessMap[i+1][j-1]!=EMPTY){//7����ڲ���Ϊ��
                    for(p=0;p<4;p++){
                        if((j-1-p)<0 || (i+1+p)>14)break;
                        str[p]=chessMap[i+1+p][j-1-p];
                    }
                    valueMap[i][j]+=table_B(str,x);//�ۼƵ��ӷ���ֵ
                    memset(str,EMPTY,sizeof(str));
                }
            }
            if(j-1>=0 && chessMap[i][j-1]!=EMPTY){
                for(p=0;p<4;p++){//����̽��
                    if((j-1-p)<0)break;
                    str[p]=chessMap[i][j-1-p];
                }
                valueMap[i][j]+=table_B(str,x);//�ۼƵ��ӷ���ֵ
                memset(str,EMPTY,sizeof(str));
            }
        }
    }
}
//valueA����
void value_A(ChessType chessMap[15][15],int x,int valueMap[15][15]){
    int p;
    memset(valueMap,0,sizeof(int)*225);
    ChessType str[4]={EMPTY};
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            if(i-1>=0){
                if(j-1>=0 && chessMap[i-1][j-1]==EMPTY){//����1�㲢һ��Ϊ��
                    for(p=0;p<4;p++){//����̽��
                        if((i+1+p)>14 || (j+1+p)>14)break;
                        str[p]=chessMap[i+1+p][j+1+p];
                    }
                    valueMap[i][j]+=table_A(str,x);//�ۼƵ��ӹ���ֵ
                    memset(str,EMPTY,sizeof(str));
                }
                if(chessMap[i-1][j]==EMPTY){//2����ڲ�Ϊ��
                    for(p=0;p<4;p++){//����̽��
                        if((i+1+p)>14)break;
                        str[p]=chessMap[i+1+p][j];
                    }
                    valueMap[i][j]+=table_A(str,x);//�ۼƵ��ӹ���ֵ
                    memset(str,EMPTY,sizeof(str));
                }
                if(j+1<15 && chessMap[i-1][j+1]==EMPTY){//3����ڲ�Ϊ��
                    for(p=0;p<4;p++){//����̽��
                        if((i+1+p)>14 || (j-1-p)<0)break;
                        str[p]=chessMap[i+1+p][j-1-p];
                    }
                    valueMap[i][j]+=table_A(str,x);//�ۼƵ��ӹ���ֵ
                    memset(str,EMPTY,sizeof(str));
                }
            }
            if(j+1<15){
                if(chessMap[i][j+1]==EMPTY){//4����ڲ�Ϊ��
                    for(p=0;p<4;p++){//����̽��
                        if((j-1-p)<0)break;
                        str[p]=chessMap[i][j-1-p];
                    }
                    valueMap[i][j]+=table_A(str,x);//�ۼƵ��ӹ���ֵ
                    memset(str,EMPTY,sizeof(str));
                }
                if(i+1<15 && chessMap[i+1][j+1]==EMPTY){//5����ڲ�Ϊ��
                    for(p=0;p<4;p++){//����̽��
                        if((i-1-p)<0 || (j-1-p)<0)break;
                        str[p]=chessMap[i-1-p][j-1-p];
                    }
                    valueMap[i][j]+=table_A(str,x);//�ۼƵ��ӹ���ֵ
                    memset(str,EMPTY,sizeof(str));
                }
            }
            if(i+1<15){
                if(chessMap[i+1][j]==EMPTY){//6����ڲ�Ϊ��
                    for(p=0;p<4;p++){//����̽��
                        if((i-1-p)<0)break;
                        str[p]=chessMap[i-1-p][j];
                    }
                    valueMap[i][j]+=table_A(str,x);//�ۼƵ��ӹ���ֵ
                    memset(str,EMPTY,sizeof(str));
                }
                if(j-1>=0 && chessMap[i+1][j-1]==EMPTY){//7����ڲ�Ϊ��
                    for(p=0;p<4;p++){//����̽��
                        if((i-1-p)<0 || (j+1+p)>14)break;
                        str[p]=chessMap[i-1-p][j+1+p];
                    }
                    valueMap[i][j]+=table_A(str,x);//�ۼƵ��ӹ���ֵ
                    memset(str,EMPTY,sizeof(str));
                }
            }
            if(j-1>=0 && chessMap[i][j-1]==EMPTY){
                for(p=0;p<4;p++){//����̽��
                    if((j+1+p)>14)break;
                    str[p]=chessMap[i][j+1+p];
                }
                valueMap[i][j]+=table_A(str,x);//�ۼƵ��ӹ���ֵ
                memset(str,EMPTY,sizeof(str));
            }
        }
    }
}



// ��һ������λ��
void nextMove(ChessType chessMap[MAP_SIZE][MAP_SIZE],int& row,int &col){
    int i,j,k;
    int n=1;
    int mW,mE,mB;  //���������������Ϳո���
    int mQ;
    int x,y;
    int Map0[15][15];   //ս����ͼ
    //���㵱ǰ����
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

    //���ֶ�ʽ
    if(n==1)
    {
        row=7;
        col=7;
        return;
    }
    if(n==3)
    {
        int x1,y1,x2,y2,x0,y0,x,y,flag;
        int rand0,randx[3],randy[3];  //��ѡ��
        x1=7;
        y1=7;
        //Ѱ�ҵڶ���λ��
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
        //����Ӧ��
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
        //����Ӧ��
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
    //������������
    //��������
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
    //��������
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
    //��б������
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
    //��б������
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
    //�Է���������
    //��������
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
    //��������
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
    //��б������
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
    //��б������
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
    //������������
    //��������
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
    //��������
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
    //��б������
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
    //��б������
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

    int map4W[15][15];   //To Four����-W
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




    //ս����ͼ
    //0-EMPTY
    //1-WHITE
    //2-BLACK
    //3-WHITE���ĵ�

    //��ͼ����
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
    //����WHITE���ĵ�
    //��������
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
    //��������
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
    //��б������
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
    //��б������
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

    //��������������1���ĵ�+2���ӣ�
    //��������
    for(i=0;i<10;i++)
    {
        for(j=0;j<15;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //������ʾ�׷����ĵ���Ŀ
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
                //δ�жϺڷ��Ƿ��з������ģ������������Ľ�
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
    //��������
    for(i=0;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //������ʾ�׷����ĵ���Ŀ
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
                //δ�жϺڷ��Ƿ��з������ģ������������Ľ�
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
    //��б������
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //������ʾ�׷����ĵ���Ŀ
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
                //δ�жϺڷ��Ƿ��з������ģ������������Ľ�
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
    //��б������
    for(i=5;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //������ʾ�׷����ĵ���Ŀ
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
                //δ�жϺڷ��Ƿ��з������ģ������������Ľ�
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
    //��������������2���ĵ�+1���ӣ�
    //��������
    for(i=0;i<10;i++)
    {
        for(j=0;j<15;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //������ʾ�׷����ĵ���Ŀ
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
                //δ�жϺڷ��Ƿ��з������ģ������������Ľ�
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
    //��������
    for(i=0;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //������ʾ�׷����ĵ���Ŀ
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
                //δ�жϺڷ��Ƿ��з������ģ������������Ľ�
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
    //��б������
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //������ʾ�׷����ĵ���Ŀ
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
                //δ�жϺڷ��Ƿ��з������ģ������������Ľ�
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
    //��б������
    for(i=5;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //������ʾ�׷����ĵ���Ŀ
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
                //δ�жϺڷ��Ƿ��з������ģ������������Ľ�
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
    //��������������3���ĵ�+0���ӣ�
    //��������
    for(i=0;i<10;i++)
    {
        for(j=0;j<15;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //������ʾ�׷����ĵ���Ŀ
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
                //δ�жϺڷ��Ƿ��з������ģ������������Ľ�
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
    //��������
    for(i=0;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //������ʾ�׷����ĵ���Ŀ
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
                //δ�жϺڷ��Ƿ��з������ģ������������Ľ�
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
    //��б������
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //������ʾ�׷����ĵ���Ŀ
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
                //δ�жϺڷ��Ƿ��з������ģ������������Ľ�
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
    //��б������
    for(i=5;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mW=0;
            mE=0;
            mQ=0;   //������ʾ�׷����ĵ���Ŀ
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
                //δ�жϺڷ��Ƿ��з������ģ������������Ľ�
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

    //Ӧ��BLACK����

    //����A/D/S��ֵ
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
    //��������
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
    //��������
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
    //��б������
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
    //��б������
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

    //Ӧ��BLACK����
    int map4B[15][15];   //To Four����-B
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


    //������ɱ
    //ս����ͼ
    //0-EMPTY
    //1-WHITE
    //2-BLACK
    //3-BLACK���ĵ�

    //��ͼ����
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
    //����BLACK���ĵ�
    //��������
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
    //��������
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
    //��б������
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
    //��б������
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
    //�����Է�������1���ĵ�+2���ӣ�
    //��������
    for(i=0;i<10;i++)
    {
        for(j=0;j<15;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //������ʾ�ڷ����ĵ���Ŀ
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
                //δ�жϰ׷��Ƿ��з������ģ������������Ľ�
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
    //��������
    for(i=0;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //������ʾ�ڷ����ĵ���Ŀ
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
                //δ�жϰ׷��Ƿ��з������ģ������������Ľ�
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
    //��б������
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //������ʾ�ڷ����ĵ���Ŀ
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
                //δ�жϰ׷��Ƿ��з������ģ������������Ľ�
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
    //��б������
    for(i=5;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //������ʾ�ڷ����ĵ���Ŀ
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
                //δ�жϰ׷��Ƿ��з������ģ������������Ľ�
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
    //�����Է�������2���ĵ�+1���ӣ�
    //��������
    for(i=0;i<10;i++)
    {
        for(j=0;j<15;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //������ʾ�ڷ����ĵ���Ŀ
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
                //δ�жϰ׷��Ƿ��з������ģ������������Ľ�
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
    //��������
    for(i=0;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //������ʾ�ڷ����ĵ���Ŀ
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
                //δ�жϰ׷��Ƿ��з������ģ������������Ľ�
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
    //��б������
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //������ʾ�ڷ����ĵ���Ŀ
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
                //δ�жϰ׷��Ƿ��з������ģ������������Ľ�
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
    //��б������
    for(i=5;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //������ʾ�ڷ����ĵ���Ŀ
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
                //δ�жϰ׷��Ƿ��з������ģ������������Ľ�
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
    //�����Է�������3���ĵ�+0���ӣ�
    //��������
    for(i=0;i<10;i++)
    {
        for(j=0;j<15;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //������ʾ�ڷ����ĵ���Ŀ
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
                //δ�жϰ׷��Ƿ��з������ģ������������Ľ�
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
    //��������
    for(i=0;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //������ʾ�ڷ����ĵ���Ŀ
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
                //δ�жϰ׷��Ƿ��з������ģ������������Ľ�
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
    //��б������
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //������ʾ�ڷ����ĵ���Ŀ
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
                //δ�жϰ׷��Ƿ��з������ģ������������Ľ�
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
    //��б������
    for(i=5;i<15;i++)
    {
        for(j=0;j<10;j++)
        {
            mB=0;
            mE=0;
            mQ=0;   //������ʾ�ڷ����ĵ���Ŀ
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
                //δ�жϰ׷��Ƿ��з������ģ������������Ľ�
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

    //��������������
    int map3W[15][15];   //To Three����-W
    MAP3(chessMap,1,map3W);

    //˫��ɱ
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
    //��˫��ɱ
    int map3B[15][15];   //To Three����-B
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

    //�׷�����

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
 *  @brief  ����ָ�����괦�ļ�ֵ
 *  @param  pt  ����
 *  @return ��ֵ
 *  ���﷽������ָ�����ġ��ס��ַ�Χ���Ӽ������
 */
int CalcPointValue(point_t pt)
{
	// ���ס��֣�ÿ��Ԫ�ر�ʾ�����������ƫ��
	static const point_t d[8][3] = {
		{{-1, 0}, {-2, 0}, {-3, 0}}, {{+1, 0}, {+2, 0}, {+3, 0}},
		{{ 0,-1}, { 0,-2}, { 0,-3}}, {{ 0,+1}, { 0,+2}, { 0,+3}},
		{{+1,-1}, {+2,-2}, {+3,-3}}, {{-1,-1}, {-2,-2}, {-3,-3}},
		{{+1,+1}, {+2,+2}, {+3,+3}}, {{-1,+1}, {-2,+2}, {-3,+3}}};

	int i, j;
	int sum = 0;

	// �����ֵ���뷨�ǣ�
	// ����������ߣ�ͬɫʱ��ֵ��������ɫʱֹͣ
	// ���ܰ˸���������е�ƫ������������ֵ��
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
 *  @brief  ������ѵ�
 *  @return λ������
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

// ������� //////////////////////////////////////////////////////////////////

/**
 *  @brief  ���һ������
 *  @param  cmd ����
 *  @param  fmt ��ʽ
 *  @param  va  ���
 *  @note   ���л��лᱻ�ո�ȡ������β�ḽ��һ������
 */
void PrintCmd(const char *cmd, const char *fmt, va_list va)
{
	char buf[4 * 1024];  // ����

	// ǰ׺����м�ո񣬺��Ϊ��ʽ�����
	strcpy(buf, cmd);
	strcat(buf, buf[0] == '\0' ? "" : " ");
	vsprintf(&buf[strlen(buf)], fmt, va);

	// �滻�������лس����з�
	while (1) {
		char *p = strpbrk(buf, "\r\n");

		if (p != NULL) {
			*p = ' ';  // ��Ϊ�ո�
		} else {
			break;  // �������
		}
	}

	// ��ӡ����׼���
	puts(buf);  // ���������
	fflush(stdout);  // ע���ֹ�������
}

/**
 *  @brief  ���һ��
 *  @param  fmt ��ʽ
 */
void Print(const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	PrintCmd("", fmt, va);
	va_end(va);
}

/**
 *  @brief  ��� UNKNOWN ����
 *  @param  fmt ��ʽ
 */
void PrintUnknown(const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	PrintCmd("UNKNOWN", fmt, va);
	va_end(va);
}

/**
 *  @brief  ��� ERROR ����
 *  @param  fmt ��ʽ
 */
void PrintError(const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	PrintCmd("ERROR", fmt, va);
	va_end(va);
}

/**
 *  @brief  ��� MESSAGE ����
 *  @param  fmt ��ʽ
 */
void PrintMessage(const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	PrintCmd("MESSAGE", fmt, va);
	va_end(va);
}

/**
 *  @brief  ��� DEBUG ����
 *  @param  fmt ��ʽ
 */
void PrintDebug(const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	PrintCmd("DEBUG", fmt, va);
	va_end(va);
}

/**
 *  @brief  ��� SUGGEST ����
 *  @param  x   ������
 *  @param  y   ������
 */
void PrintSuggest(int x, int y)
{
	Print("SUGGEST %d,%d", x, y);
}

// ����� //////////////////////////////////////////////////////////////////

/**
 *  @brief  �жϻ������Ƿ�Ϊָ������
 *  @param  buf ����
 *  @param  cmd ���20�ַ�Ϊ��
 *  @return �Ƿ�
 */
BOOL IsCmd(const char *buf, const char *cmd)
{
	char src[21], dst[21];
	int i, n;

	// �ӻ����ȡԴ����
	if (sscanf(buf, "%20s", src) != 1) {
		return FALSE;
	}

	// ��Դ����תΪ��д
	for (n = strlen(src), i = 0; i < n; ++i) {
		src[i] = toupper(src[i]);
	}

	// ��ȡĿ���д�ַ�
	for (n = strlen(cmd), i = 0; i < n; ++i) {
		dst[i] = toupper(cmd[i]);
	}

	dst[n] = '\0';  // β��

	// ���������Ƿ����
	return strcmp(src, dst) == 0;
}

/**
 *  @brief  ���� STRAT ����
 *  @param  buf �����л���
 */
void CmdStart(char *buf)
{
	int size;

	// ��ȡ����
	if (sscanf(buf, "%*s%d", &size) != 1) {
		PrintError("bad START parameter");
		return;
	}

	// �����С
	if (!BoardResize(size, size)) {
		PrintError("%d < width < %d  %d < height < %d",
			WIDTH_MIN, WIDTH_MAX, HEIGHT_MIN, HEIGHT_MAX);
		return;
	}

	BoardReset();  // ��ո�λ
	Print("OK");  // �ɹ���Ӧ
}

/**
 *  @brief  ���� TURN ����
 *  @param  buf �����л���
 */
void CmdTurn(char *buf)
{
	int x, y;
	point_t pt;

	// ��ȡ����
	if (sscanf(buf, "%*s%d,%d", &x, &y) != 2) {
		PrintError("bad TURN parameters");
		return;
	}

	pt.x = x, pt.y = y;

	// ����������λ��
	if (!BoardHasPoint(pt) || BoardGet(pt) != kStnNo) {
		PrintError("bad coordinates");
		return;
	}

	// �����Ӧ������
	BoardSet(pt, kStnOp);  // ��������

	pt = SearchBestPoint();  // �����ŷ�

	if (g_is_suggest) {
		PrintSuggest(pt.x, pt.y);  // ��Ӧ����
	} else {
		BoardSet(pt, kStnAi);  // ��������
		Print("%d,%d", pt.x, pt.y);  // ��Ӧ����
	}
}

/**
 *  @brief  ���� BEGIN ����
 *  @param  buf �����л���
 */
void CmdBegin(char *buf)
{
	point_t pt = SearchBestPoint();  // �����ŷ�
	BoardSet(pt, kStnAi);  // ��������
	Print("%d,%d", pt.x, pt.y);  // ��Ӧ����
}

/**
 *  @brief  ���� BOARD ����
 *  @param  buf �����л���
 */
void CmdBoard(char *buf)
{
	point_t pt;

	// ��ȡ����ֱ��DONE
	while (gets(buf), !IsCmd(buf, "DONE")) {
		int x, y, field = 0;

		sscanf(buf, "%d,%d,%d", &x, &y, &field);
		pt.x = x, pt.y = y;

		// ��鲼��λ��
		if (BoardHasPoint(pt)) {
			// ����
			switch (field) {
			case 1: BoardSet(pt, kStnAi); break;
			case 2: BoardSet(pt, kStnOp); break;
			default: break;
			}
		}
	}

	// �����Ӧ������
	pt = SearchBestPoint();  // �����ŷ�
	BoardSet(pt, kStnAi);  // ��������
	Print("%d,%d", pt.x, pt.y);  // ��Ӧ����
}

/**
 *  @brief  ���� INFO ����
 *  @param  buf �����л���
 */
void CmdInfo(char *buf)
{
	char *key, *val;

	// ���ո�ָ����ֵ��
	strtok(buf, " ");
	key = strtok(NULL, " ");
	val = strtok(NULL, " ");

	// ��������
	if (key == NULL || val == NULL) {}  // �޲�����������
	else if (IsCmd(key, "timeout_turn" )) { g_info.timeout_turn  = atoi(val); }
	else if (IsCmd(key, "timeout_match")) { g_info.timeout_match = atoi(val); }
	else if (IsCmd(key, "max_memory"   )) { g_info.max_memory    = atoi(val); }
	else if (IsCmd(key, "time_left"    )) { g_info.time_left     = atoi(val); }
	else if (IsCmd(key, "game_type"    )) { g_info.game_type     = atoi(val); }
	else if (IsCmd(key, "rule"         )) { g_info.rule          = atoi(val); }
	else if (IsCmd(key, "folder"       )) { strcpy(g_info.folder, val); }

	// �����Ӧ
}

/**
 *  @brief  ���� ABOUT ����
 *  @param  buf �����л���
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
 *  @brief  ���� RECTSTART ����
 *  @param  buf �����л���
 */
void CmdRectStart(char *buf)
{
	int width, height;

	// ��ȡ����
	if (sscanf(buf, "%*s%d%d", &width, &height) != 2) {
		PrintError("bad RECTSTART parameters");
		return;
	}

	// �����С
	if (!BoardResize(width, height)) {
		PrintError("%d < width < %d  %d < height < %d",
			WIDTH_MIN, WIDTH_MAX, HEIGHT_MIN, HEIGHT_MAX);
		return;
	}

	BoardReset();  // ��ո�λ
	Print("OK");  // �ɹ���Ӧ
}

/**
 *  @brief  ���� RESTART ����
 *  @param  buf �����л���
 */
void CmdRestart(char *buf)
{
	BoardReset();  // ��ո�λ
	Print("OK");  // �ɹ���Ӧ
}

/**
 *  @brief  ���� TAKEBACK ����
 *  @param  buf �����л���
 */
void CmdTakeback(char *buf)
{
	int x, y;
	point_t pt;

	// ��ȡ����
	if (sscanf(buf, "%*s%d,%d", &x, &y) != 2) {
		PrintError("bad TAKEBACK parameters");
		return;
	}

	pt.x = x, pt.y = y;

	// �������λ��
	if (!BoardHasPoint(pt)) {
		PrintError("bad coordinates");
		return;
	}

	BoardSet(pt, kStnNo);  // ����
	Print("OK");  // �ɹ���Ӧ
}

/**
 *  @brief  ���� PLAY ����
 *  @param  buf �����л���
 */
void CmdPlay(char *buf)
{
	int x, y;
	point_t pt;

	// ��ȡ����
	if (sscanf(buf, "%*s%d,%d", &x, &y) != 2) {
		PrintError("bad PLAY parameters");
		return;
	}

	pt.x = x, pt.y = y;

	// ��鱾������λ��
	if (!BoardHasPoint(pt) || BoardGet(pt) != kStnNo) {
		PrintError("bad coordinates");
		return;
	}

	BoardSet(pt, kStnAi);  // ��������
	Print("%d,%d", pt.x, pt.y);  // ��Ӧ����
}

// ͨ�Ž��� //////////////////////////////////////////////////////////////////

/**
 *  @brief  ������
 *  @return ����ִ�н��
 */
int main(void)
{
	if (TRUE) {  // TODO: �жϳ�������Piskvork���û���ֱ������
		// ��ʾ��Ϣ
		PrintMessage(
			"Gomoku AI should not be started directly. "
			"Please install gomoku manager "
			"(http://sourceforge.net/projects/piskvork). "
			"Then enter path to this exe file in players settings.");
	}

	// ���̾��Ǹ�������������
	while (1) {
		char buf[1024];  // �л���
		gets(buf);  // �ӱ�׼�������һ��

		// ���ݲ�ͬ��������в�ͬ�Ĵ���
		if (IsCmd(buf, "END")) { break; }  // ������ת
		else if (IsCmd(buf, "START"    )) { CmdStart    (buf); }  // �ر�
		else if (IsCmd(buf, "TURN"     )) { CmdTurn     (buf); }  // �ر�
		else if (IsCmd(buf, "BEGIN"    )) { CmdBegin    (buf); }  // �ر�
		else if (IsCmd(buf, "BOARD"    )) { CmdBoard    (buf); }  // �ر�
		else if (IsCmd(buf, "INFO"     )) { CmdInfo     (buf); }  // �ر�
		else if (IsCmd(buf, "ABOUT"    )) { CmdAbout    (buf); }  // �ر�
	//	else if (IsCmd(buf, "RECTSTART")) { CmdRectStart(buf); }  // ��ѡ
		else if (IsCmd(buf, "RESTART"  )) { CmdRestart  (buf); }  // ��ѡ
		else if (IsCmd(buf, "TAKEBACK" )) { CmdTakeback (buf); }  // ��ѡ
		else if (IsCmd(buf, "PLAY"     )) { CmdPlay     (buf); }  // ��ѡ
		else { PrintUnknown("%s", buf); }  // δ֪����
	}

	return 0;
}
