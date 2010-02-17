#ifndef _HSTHREAD_H
#define _HSTHREAD_H

#include "../PlasmaDefs.h"

#ifdef WIN32
#  define S_THREADSTART int s_threadstart()
#else
#  define S_THREADSTART void* s_threadstart(void*)
#endif

DllClass hsThread {
private:
    void* fThreadData;

public:
    hsThread();
    hsThread(const hsThread& init);
    ~hsThread();

    void start();
    void wait();
    void finish();
    bool isFinished();

    static void Yield();

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
    hsMutex(const hsMutex& init);
    ~hsMutex();

    void lock();
    void unlock();
};

#endif
