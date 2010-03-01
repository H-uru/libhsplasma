#include "hsThread.h"
#include "Debug/hsExceptions.h"

enum {
    kStatePending = 0,
    kStateRunning = 0x1,
    kStateFinished = 0x2,
    kStateDeleteReady = 0x4,
    kStateCanDelete = (kStateFinished | kStateDeleteReady),
};

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
    _thread->fState = (_thread->fState & ~kStateRunning) | kStateFinished;
    if ((_thread->fState & kStateCanDelete) == kStateCanDelete)
        delete _this;
    return 0;
}

hsThread::hsThread() {
    fThreadData = (void*)(new hsThread_WIN32);
}

hsThread::~hsThread() {
    hsThread_WIN32* _this = (hsThread_WIN32*)fThreadData;
    delete _this;
}

void hsThread::start() {
    hsThread_WIN32* _this = (hsThread_WIN32*)fThreadData;
    if ((_this->fState & kStateRunning) != 0)
        throw hsBadParamException(__FILE__, __LINE__, "Thread already running!");

    _this->fState |= kStateRunning;
    _this->fThreadHandle = CreateThread(NULL, 0, &s_threadstart, this, 0, NULL);
    if (_this->fThreadHandle == NULL)
        _this->fState = (_this->fState & ~kStateRunning) | kStateFinished;
}

void hsThread::wait() {
    while (!isFinished())
        YieldThread();
}

bool hsThread::isFinished() const {
    const hsThread_WIN32* _this = (const hsThread_WIN32*)fThreadData;
    return (_this->fState & kStateFinished) != 0;
}

void hsThread::destroy() {
    hsThread_WIN32* _this = (hsThread_WIN32*)fThreadData;
    _this->fState |= kStateDeleteReady;
    if ((_this->fState & kStateCanDelete) == kStateCanDelete)
        delete this;
}

void hsThread::terminate() {
    hsThread_WIN32* _this = (hsThread_WIN32*)fThreadData;
    if ((_this->fState & kStateRunning) != 0) {
        TerminateThread(_this->fThreadHandle, 1);
        _this->fState = (_this->fState & ~kStateRunning) | kStateFinished;
    }
    destroy();
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
