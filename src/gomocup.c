
#include "gomocup.h"

// 全局变量 //////////////////////////////////////////////////////////////////

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
int IsCmd(const char *buf, const char *cmd)
{
    char src[21], dst[21];
    int i, n;

    // 从缓冲读取源命令
    if (sscanf(buf, "%20s", src) != 1) {
        return 0;
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
    int newSize;

    // 获取参数
    if (sscanf(buf, "%*s%d", &newSize) != 1) {
        PrintError("bad START parameter");
        return;
    }

    size = newSize;
    init();
    resetBoard(gBoard);
    Print("OK");  // 成功回应
}

/**
 *  @brief  处理 TURN 命令
 *  @param  buf 命令行缓冲
 */
void CmdTurn(char *buf)
{
    int x, y;

    // 获取参数
    if (sscanf(buf, "%*s%d,%d", &x, &y) != 2) {
        PrintError("bad TURN parameters");
        return;
    }

    // 检查对手落子位置
    if (!inBoard(x, y) || gBoard[x][y] != EM) {
        PrintError("bad coordinates");
        return;
    }
    gBoard[x][y] = OP;
    // 计算对应并返回
    minMaxSearch(gBoard, &x, &y, 6, 6, 8, 0, 0);
    gBoard[x][y] = SELF;
    Print("%d,%d", x, y);  // 回应坐标
}

/**
 *  @brief  处理 BEGIN 命令
 *  @param  buf 命令行缓冲
 */
void CmdBegin(char *buf)
{
    int x = size / 2, y = size / 2;
    gBoard[x][y] = SELF;
    Print("%d,%d", x, y);  // 回应坐标
}

/**
 *  @brief  处理 BOARD 命令
 *  @param  buf 命令行缓冲
 */
void CmdBoard(char *buf)
{
    // 读取棋谱直至DONE
    while (gets(buf), !IsCmd(buf, "DONE")) {
        int x, y, field = 0;

        sscanf(buf, "%d,%d,%d", &x, &y, &field);

        // 检查布子位置
        if (inBoard(x, y)) {
            // 布子
            if (field == 1) {
                gBoard[x][y] = SELF;
            } else if (field == 2) {
                gBoard[x][y] = OP;
            }
        }
    }

    // 计算对应并返回
    int x, y;
    minMaxSearch(gBoard, &x, &y, 8, 8, 10, 0, 0);
    gBoard[x][y] = SELF;
    Print("%d,%d", x, y);  // 回应坐标
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
            "name=\"Zhou Mian\", "
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
//    int width, height;
//
//    // 获取参数
//    if (sscanf(buf, "%*s%d%d", &width, &height) != 2) {
//        PrintError("bad RECTSTART parameters");
//        return;
//    }
//
//    // 重设大小
//    if (!BoardResize(width, height)) {
//        PrintError("%d < width < %d  %d < height < %d",
//                   WIDTH_MIN, WIDTH_MAX, HEIGHT_MIN, HEIGHT_MAX);
//        return;
//    }
//
//    BoardReset();  // 清空复位
//    Print("OK");  // 成功回应
}

/**
 *  @brief  处理 RESTART 命令
 *  @param  buf 命令行缓冲
 */
void CmdRestart(char *buf)
{
    resetBoard(gBoard);
    Print("OK");  // 成功回应
}

/**
 *  @brief  处理 TAKEBACK 命令
 *  @param  buf 命令行缓冲
 */
void CmdTakeback(char *buf)
{
//    int x, y;
//    point_t pt;
//
//    // 获取参数
//    if (sscanf(buf, "%*s%d,%d", &x, &y) != 2) {
//        PrintError("bad TAKEBACK parameters");
//        return;
//    }
//
//    pt.x = x, pt.y = y;
//
//    // 检查提子位置
//    if (!BoardHasPoint(pt)) {
//        PrintError("bad coordinates");
//        return;
//    }
//
//    BoardSet(pt, kStnNo);  // 提子
//    Print("OK");  // 成功回应
}

/**
 *  @brief  处理 PLAY 命令
 *  @param  buf 命令行缓冲
 */
void CmdPlay(char *buf)
{
//    int x, y;
//    point_t pt;
//
//    // 获取参数
//    if (sscanf(buf, "%*s%d,%d", &x, &y) != 2) {
//        PrintError("bad PLAY parameters");
//        return;
//    }
//
//    pt.x = x, pt.y = y;
//
//    // 检查本方落子位置
//    if (!BoardHasPoint(pt) || BoardGet(pt) != kStnNo) {
//        PrintError("bad coordinates");
//        return;
//    }
//
//    BoardSet(pt, kStnAi);  // 本方落子
//    Print("%d,%d", pt.x, pt.y);  // 回应坐标
}

// 通信交互 //////////////////////////////////////////////////////////////////

/**
 *  @brief  主函数
 *  @return 程序执行结果
 */
int gomocup(void)
{
    if (1) {  // TODO: 判断程序是由Piskvork调用还是直接运行
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
//            	else if (IsCmd(buf, "RECTSTART")) { CmdRectStart(buf); }  // 可选
        else if (IsCmd(buf, "RESTART"  )) { CmdRestart  (buf); }  // 可选
        else if (IsCmd(buf, "TAKEBACK" )) { CmdTakeback (buf); }  // 可选
        else if (IsCmd(buf, "PLAY"     )) { CmdPlay     (buf); }  // 可选
        else { PrintUnknown("%s", buf); }  // 未知命令
    }

    return 0;
}
