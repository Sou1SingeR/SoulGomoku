
#ifndef SOULGOMOKU_GOMOCUP_H
#define SOULGOMOKU_GOMOCUP_H

#include "search.h"

#endif //SOULGOMOKU_GOMOCUP_H


void PrintCmd(const char *cmd, const char *fmt, va_list va);

void Print(const char *fmt, ...);

void PrintUnknown(const char *fmt, ...);

void PrintError(const char *fmt, ...);

void PrintMessage(const char *fmt, ...);

void PrintDebug(const char *fmt, ...);

void PrintSuggest(int x, int y);

int IsCmd(const char *buf, const char *cmd);

void CmdStart(char *buf);

void CmdTurn(char *buf);

void CmdBegin(char *buf);

void CmdBoard(char *buf);

void CmdInfo(char *buf);

void CmdAbout(char *buf);

void CmdRectStart(char *buf);

void CmdRestart(char *buf);

void CmdTakeback(char *buf);

void CmdPlay(char *buf);

int gomocup(void);
