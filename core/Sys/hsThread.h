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

DllClass hsThreadCondition {
protected:
    void* fConditionData;

public:
    hsThreadCondition();
    ~hsThreadCondition();

    void wait();
    void signal();
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

DllClass hsThread {
private:
    void* fThreadData;
    hsThreadCondition fFinishCondition;

public:
    hsThread();
    virtual ~hsThread();
    virtual void destroy();

    void start();
    void wait();
    bool isFinished() const;
    void terminate();

protected:
    virtual void run() = 0;

private:
    static S_THREADSTART;
};

#endif
