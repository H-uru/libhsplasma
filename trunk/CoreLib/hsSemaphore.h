#ifndef _HSSEMAPHORE_H
#define _HSSEMAPHORE_H

#include "../PlasmaDefs.h"
#include "hsExceptions.h"

#ifdef WIN32
  #include <windows.h>
#else
  #include <sys/ipc.h>
  #include <sys/sem.h>
#endif

DllClass hsSemaphore {
private:
    #ifdef WIN32
    HANDLE fSemaH;
    #else
    int fSemaID;
    #endif

public:
    hsSemaphore(int initialValue, const char* name = "");
    ~hsSemaphore();

    bool wait();
    bool signal();
};

DllClass hsSemaphoreException : public hsException {
public:
    hsSemaphoreException(const char* file, unsigned long line) throw();
};

#endif
