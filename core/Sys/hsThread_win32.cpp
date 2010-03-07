#include "hsThread.h"
#include "Debug/hsExceptions.h"

enum {
    kStatePending = 0,
    kStateRunning = 0x1,
    kStateFinished = 0x2,
};

struct hsThread_WIN32 {
    HANDLE fThreadHandle;
    hsMutex fMutex;
    int fState;

    hsThread_WIN32()
    : fThreadHandle(NULL), fState(kStatePending) { }

    ~hsThread_WIN32() {
        if (fThreadHandle != NULL)
            CloseHandle(fThreadHandle);
    }
};

struct hsCondition_WIN32 {
    HANDLE fCondition;
    hsMutex fMutex;
    int fWaiters;

    hsCondition_WIN32() : fWaiters(0) {
        fCondition = CreateEvent(NULL, FALSE, FALSE, NULL);
    }

    ~hsCondition_WIN32() {
        CloseHandle(fCondition);
    }
};


/* hsThreadCondition */
hsThreadCondition::hsThreadCondition() {
    fConditionData = (void*)(new hsCondition_WIN32);
}

hsThreadCondition::~hsThreadCondition() {
    delete (hsCondition_WIN32*)fConditionData;
}

void hsThreadCondition::wait() {
    hsCondition_WIN32* _this = (hsCondition_WIN32*)fConditionData;

    _this->fMutex.lock();
    _this->fWaiters++;
    _this->fMutex.unlock();
    WaitForSingleObject(_this->fCondition, INFINITE);
}

void hsThreadCondition::signal() {
    hsCondition_WIN32* _this = (hsCondition_WIN32*)fConditionData;

    _this->fMutex.lock();
    for (int i=0; i<_this->fWaiters; i++)
        SetEvent(_this->fCondition);
    _this->fWaiters = 0;
    _this->fMutex.unlock();
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


/* hsThread */
DWORD WINAPI hsThread::s_threadstart(LPVOID self) {
    hsThread* _this = (hsThread*)self;
    hsThread_WIN32* _thread = (hsThread_WIN32*)_this->fThreadData;

    _this->run();
    _thread->fMutex.lock();
    _thread->fState = (_thread->fState & ~kStateRunning) | kStateFinished;
    _this->fFinishCondition.signal();
    _thread->fMutex.unlock();
    return 0;
}

hsThread::hsThread() {
    fThreadData = (void*)(new hsThread_WIN32);
}

hsThread::~hsThread() {
    hsThread_WIN32* _this = (hsThread_WIN32*)fThreadData;
    wait();
    destroy();
    delete _this;
}

void hsThread::destroy() { }

void hsThread::start() {
    hsThread_WIN32* _this = (hsThread_WIN32*)fThreadData;

    _this->fMutex.lock();
    if ((_this->fState & kStateRunning) != 0) {
        _this->fMutex.unlock();
        throw hsBadParamException(__FILE__, __LINE__, "Thread already running!");
    }

    _this->fState |= kStateRunning;
    _this->fThreadHandle = CreateThread(NULL, 0, &s_threadstart, this, 0, NULL);
    if (_this->fThreadHandle == NULL) {
        _this->fState = (_this->fState & ~kStateRunning) | kStateFinished;
        fFinishCondition.signal();
    }
    _this->fMutex.unlock();
}

void hsThread::wait() {
    if (!isFinished())
        fFinishCondition.wait();
}

bool hsThread::isFinished() const {
    hsThread_WIN32* _this = (hsThread_WIN32*)fThreadData;

    _this->fMutex.lock();
    bool state = ((_this->fState & kStateFinished) != 0);
    _this->fMutex.unlock();
    return state;
}

void hsThread::terminate() {
    hsThread_WIN32* _this = (hsThread_WIN32*)fThreadData;

    _this->fMutex.lock();
    if ((_this->fState & kStateRunning) != 0) {
        TerminateThread(_this->fThreadHandle, 1);
        _this->fState = (_this->fState & ~kStateRunning) | kStateFinished;
        fFinishCondition.signal();
    }
    _this->fMutex.unlock();
}
