#ifndef _HSTHREAD_H
#define _HSTHREAD_H

#include "../PlasmaDefs.h"

#ifdef WIN32
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#  define S_THREADSTART DWORD WINAPI s_threadstart(LPVOID)
#else
#  define S_THREADSTART void* s_threadstart(void*)
#endif

DllClass hsThread {
private:
    void* fThreadData;

public:
    hsThread();
    ~hsThread();

    void start();
    void wait();
    bool isFinished() const;

    static void YieldThread();

protected:
    virtual void run() = 0;

private:
    static S_THREADSTART;
};

DllClass hsMutex {
protected:
    void* fMutexData;

public:
    hsMutex();
    ~hsMutex();

    void lock();
    void unlock();

private:
    friend class hsThread;
};

#endif
