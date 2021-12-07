
#include "search.h"

// 坐标类型
typedef struct {int x, y;} point_t;

// 棋子类型
typedef enum Stone {kStnNo, kStnAi, kStnOp} Stone;

// 全局变量 //////////////////////////////////////////////////////////////////

// 棋盘的数据结构
// 第一维是高，第二维是宽，注意是高宽而非宽高
enum Stone g_board[HEIGHT_MAX][WIDTH_MAX];

// 棋盘实际使用的尺寸及默认值
int g_width = MAP_SIZE, g_height = MAP_SIZE;

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
    minMaxSearch(map, &pt.x, &pt.y, 1);
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
            "name=\"Hei\", "
            "version=\"2022\", "
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
