#ifndef _PLDEBUG_H
#define _PLDEBUG_H

#include "hsStdioStream.h"

DllClass plDebug {
public:
    enum DebugLevel { kDLNone, kDLError, kDLWarning, kDLDebug, kDLAll };

private:
    static hsStream* fDebugStream;
    static int fDebugLevel;
    static bool fIOwnStream;

public:
    static void Init(int level = kDLWarning, hsStream* stream = NULL);
    static void InitFile(int level = kDLWarning, const char* filename = "libPlasma.log");

    static void Error(const char* fmt, ...);
    static void Warning(const char* fmt, ...);
    static void Debug(const char* fmt, ...);

private:
    static void DeInit();
    static void WriteLn(const char* fmt, va_list args);
};

#endif
