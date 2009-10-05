#include "plDebug.h"
#include <cstdarg>
#include <cstdlib>

hsStream* plDebug::fDebugStream = NULL;
int plDebug::fDebugLevel = kDLWarning;
bool plDebug::fIOwnStream = false;
bool plDebug::fIsExitRegistered = false;
plString plDebug::fDebugFile;

void plDebug::Init(int level, hsStream* stream) {
    DeInit();

    fDebugLevel = level;
    if (stream == NULL) {
        fDebugStream = new hsStdioStream(true);
        fIOwnStream = true;
    } else {
        fDebugStream = stream;
        fIOwnStream = false;
    }

    // Register cleanup
    if (!fIsExitRegistered) {
        fIsExitRegistered = true;
        atexit(&plDebug::DeInit);
    }
}

void plDebug::InitFile(int level, const char* filename) {
    DeInit();

    fDebugLevel = level;
    fDebugFile = filename;

    // Register cleanup
    if (!fIsExitRegistered) {
        fIsExitRegistered = true;
        atexit(&plDebug::DeInit);
    }
}

void plDebug::DelayInit() {
    if (fDebugFile.empty()) {
        // Nobody ever called Init(), so use stderr
        Init(kDLWarning, NULL);
    } else {
        // Init to the provided filename
        fDebugStream = new hsFileStream();
        ((hsFileStream*)fDebugStream)->open(fDebugFile, fmCreate);
        fIOwnStream = true;
    }
}

void plDebug::DeInit() {
    if (fIOwnStream && (fDebugStream != NULL))
        delete fDebugStream;
    fDebugStream = NULL;
}

void plDebug::Error(const char* fmt, ...) {
    if (fDebugLevel < kDLError)
        return;
    if (fDebugStream == NULL)
        DelayInit();
    va_list aptr;
    va_start(aptr, fmt);
    WriteLn(fmt, aptr);
    va_end(aptr);
}

void plDebug::Warning(const char* fmt, ...) {
    if (fDebugLevel < kDLWarning)
        return;
    if (fDebugStream == NULL)
        DelayInit();
    va_list aptr;
    va_start(aptr, fmt);
    WriteLn(fmt, aptr);
    va_end(aptr);
}

void plDebug::Debug(const char* fmt, ...) {
    if (fDebugLevel < kDLDebug)
        return;
    if (fDebugStream == NULL)
        DelayInit();
    va_list aptr;
    va_start(aptr, fmt);
    WriteLn(fmt, aptr);
    va_end(aptr);
}

void plDebug::WriteLn(const char* fmt, va_list args) {
    fDebugStream->writeLine(plString::FormatV(fmt, args));
    fDebugStream->flush();
}
