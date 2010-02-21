#include "hsThread.h"
#include "Debug/hsExceptions.h"

enum { kStatePending, kStateRunning, kStateFinished };

struct hsThread_WIN32 {
    HANDLE fThreadHandle;
    int fState;

    hsThread_WIN32()
    : fThreadHandle(NULL), fState(kStatePending) { }

    ~hsThread_WIN32() {
        if (fThreadHandle != NULL)
            CloseHandle(fThreadHandle);
    }
};


/* hsThread */
DWORD WINAPI hsThread::s_threadstart(LPVOID self) {
    hsThread* _this = (hsThread*)self;
    hsThread_WIN32* _thread = (hsThread_WIN32*)_this->fThreadData;

    _this->run();
    _thread->fState = kStateFinished;
    return 0;
}

hsThread::hsThread() {
    fThreadData = (void*)(new hsThread_WIN32);
}

hsThread::~hsThread() {
    hsThread_WIN32* _this = (hsThread_WIN32*)fThreadData;

    // Deleting a thread kills it!
    if (!isFinished())
        TerminateThread(_this->fThreadHandle, 1);
    
    delete _this;
}

void hsThread::start() {
    hsThread_WIN32* _this = (hsThread_WIN32*)fThreadData;
    if (_this->fState == kStateRunning)
        throw hsBadParamException(__FILE__, __LINE__, "Thread already running!");

    _this->fState = kStateRunning;
    _this->fThreadHandle = CreateThread(NULL, 0, &s_threadstart, this, 0, NULL);
    if (_this->fThreadHandle == NULL)
        _this->fState = kStateFinished;
}

void hsThread::wait() {
    while (!isFinished())
        YieldThread();
}

bool hsThread::isFinished() const {
    const hsThread_WIN32* _this = (const hsThread_WIN32*)fThreadData;
    return (_this->fState == kStateFinished);
}

void hsThread::YieldThread() {
    SwitchToThread();
}


/* hsMutex */
hsMutex::hsMutex() {
    fMutexData = (void*)CreateMutex(NULL, FALSE, NULL);
}

hsMutex::~hsMutex() {
    CloseHandle((HANDLE)fMutexData);
}

void hsMutex::lock() {
    WaitForSingleObject((HANDLE)fMutexData, INFINITE);
}

void hsMutex::unlock() {
    ReleaseMutex((HANDLE)fMutexData);
}
