#ifndef _PLDEBUG_H
#define _PLDEBUG_H

#include "hsStdioStream.h"

DllClass plDebug {
public:
    enum DebugLevel { kDLNone, kDLError, kDLDebug, kDLAll };

private:
    static hsStream* fDebugStream;
    static int fDebugLevel;
    static bool fIOwnStream;

public:
    static void Init(int level = kDLNone, hsStream* stream = NULL);
    static void DeInit();

    static void Error(const char* fmt, ...);
    static void Debug(const char* fmt, ...);

private:
    static void WriteLn(const char* fmt, va_list args);
};

#endif
