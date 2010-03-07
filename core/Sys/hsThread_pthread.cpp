#include "hsThread.h"
#include "Debug/hsExceptions.h"
#include <pthread.h>
#include <cstdlib>
#include <list>

enum {
    kStatePending = 0,
    kStateRunning = 0x1,
    kStateFinished = 0x2,
};

static pthread_mutexattr_t s_mutexattr;

void delMutexAttr() {
    pthread_mutexattr_destroy(&s_mutexattr);
}

void setupMutexAttr() {
    pthread_mutexattr_init(&s_mutexattr);
    pthread_mutexattr_settype(&s_mutexattr, PTHREAD_MUTEX_RECURSIVE);
    atexit(&delMutexAttr);
}

struct hsThread_POSIX {
    pthread_t fThreadHandle;
    hsMutex fMutex;
    int fState;

    hsThread_POSIX() : fState(kStatePending) { }
    ~hsThread_POSIX() { }
};

struct hsCondition_POSIX {
    pthread_cond_t fCondition;
    pthread_mutex_t fMutex;
    int fWaiters;

    hsCondition_POSIX() : fWaiters(0) {
        pthread_mutex_init(&fMutex, NULL);
        pthread_cond_init(&fCondition, NULL);
    }

    ~hsCondition_POSIX() {
        pthread_cond_destroy(&fCondition);
        pthread_mutex_destroy(&fMutex);
    }
};


/* hsThreadCondition */
hsThreadCondition::hsThreadCondition() {
    fConditionData = (void*)(new hsCondition_POSIX);
}

hsThreadCondition::~hsThreadCondition() {
    delete (hsCondition_POSIX*)fConditionData;
}

void hsThreadCondition::wait() {
    hsCondition_POSIX* _this = (hsCondition_POSIX*)fConditionData;

    pthread_mutex_lock(&_this->fMutex);
    _this->fWaiters++;
    pthread_cond_wait(&_this->fCondition, &_this->fMutex);
    pthread_mutex_unlock(&_this->fMutex);
}

void hsThreadCondition::signal() {
    hsCondition_POSIX* _this = (hsCondition_POSIX*)fConditionData;

    pthread_mutex_lock(&_this->fMutex);
    if (_this->fWaiters == 1)
        pthread_cond_signal(&_this->fCondition);
    else if (_this->fWaiters > 1)
        pthread_cond_broadcast(&_this->fCondition);
    _this->fWaiters = 0;
    pthread_mutex_unlock(&_this->fMutex);
}


/* hsMutex */
hsMutex::hsMutex() {
    fMutexData = (void*)(new pthread_mutex_t);
    pthread_mutex_init((pthread_mutex_t*)fMutexData, &s_mutexattr);
}

hsMutex::~hsMutex() {
    pthread_mutex_destroy((pthread_mutex_t*)fMutexData);
    delete (pthread_mutex_t*)fMutexData;
}

void hsMutex::lock() {
    pthread_mutex_lock((pthread_mutex_t*)fMutexData);
}

void hsMutex::unlock() {
    pthread_mutex_unlock((pthread_mutex_t*)fMutexData);
}


/* hsThread */
void* hsThread::s_threadstart(void* self) {
    hsThread* _this = (hsThread*)self;
    hsThread_POSIX* _thread = (hsThread_POSIX*)_this->fThreadData;

    _this->run();
    _thread->fMutex.lock();
    _thread->fState = (_thread->fState & ~kStateRunning) | kStateFinished;
    _this->fFinishCondition.signal();
    _thread->fMutex.unlock();
    return NULL;
}

hsThread::hsThread() {
    fThreadData = (void*)(new hsThread_POSIX);
}

hsThread::~hsThread() {
    hsThread_POSIX* _this = (hsThread_POSIX*)fThreadData;
    wait();
    destroy();
    delete _this;
}

void hsThread::destroy() { }

void hsThread::start() {
    hsThread_POSIX* _this = (hsThread_POSIX*)fThreadData;

    _this->fMutex.lock();
    if ((_this->fState & kStateRunning) != 0) {
        _this->fMutex.unlock();
        throw hsBadParamException(__FILE__, __LINE__, "Thread already running!");
    }

    _this->fState |= kStateRunning;
    if (pthread_create(&_this->fThreadHandle, NULL, &s_threadstart, this) != 0) {
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
    hsThread_POSIX* _this = (hsThread_POSIX*)fThreadData;

    _this->fMutex.lock();
    bool state = ((_this->fState & kStateFinished) != 0);
    _this->fMutex.unlock();
    return state;
}

void hsThread::terminate() {
    hsThread_POSIX* _this = (hsThread_POSIX*)fThreadData;

    _this->fMutex.lock();
    if ((_this->fState & kStateRunning) != 0) {
        pthread_cancel(_this->fThreadHandle);
        _this->fState = (_this->fState & ~kStateRunning) | kStateFinished;
        fFinishCondition.signal();
    }
    _this->fMutex.unlock();
}
