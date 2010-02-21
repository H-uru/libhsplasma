#include "hsThread.h"
#include "Debug/hsExceptions.h"
#include <pthread.h>
#include <list>

enum { kStatePending, kStateRunning, kStateFinished };

struct hsThread_POSIX {
    pthread_t fThreadHandle;
    int fState;

    hsThread_POSIX() : fState(kStatePending) { }

    ~hsThread_POSIX() { }
};


struct hsMutex_POSIX {
    pthread_mutex_t fMutex;
    pthread_t fOwner;
    bool fLocked;

    hsMutex_POSIX() {
        pthread_mutex_init(&fMutex, NULL);
    }

    ~hsMutex_POSIX() {
        pthread_mutex_destroy(&fMutex);
    }
};

static std::list<hsMutex*> s_allMutexes;
static hsMutex s_allMutexLock;

/* hsThread */
void* hsThread::s_threadstart(void* self) {
    hsThread* _this = (hsThread*)self;
    hsThread_POSIX* _thread = (hsThread_POSIX*)_this->fThreadData;

    _this->run();
    _thread->fState = kStateFinished;
    return NULL;
}

hsThread::hsThread() {
    fThreadData = (void*)(new hsThread_POSIX);
}

hsThread::~hsThread() {
    hsThread_POSIX* _this = (hsThread_POSIX*)fThreadData;

    // Deleting a thread kills it!
    if (!isFinished()) {
        pthread_cancel(_this->fThreadHandle);

        // Clean up mutexes that were in use by the thread
        s_allMutexLock.lock();
        std::list<hsMutex*>::iterator it;
        for (it = s_allMutexes.begin(); it != s_allMutexes.end(); it++) {
            hsMutex_POSIX* _mutex = (hsMutex_POSIX*)(*it)->fMutexData;
            if (_mutex->fLocked && pthread_equal(_mutex->fOwner, _this->fThreadHandle))
                (*it)->unlock();
        }
        s_allMutexLock.unlock();
    }

    delete _this;
}

void hsThread::start() {
    hsThread_POSIX* _this = (hsThread_POSIX*)fThreadData;
    if (_this->fState == kStateRunning)
        throw hsBadParamException(__FILE__, __LINE__, "Thread already running!");

    _this->fState = kStateRunning;
    if (pthread_create(&_this->fThreadHandle, NULL, &s_threadstart, this) != 0) {
        // If the thread didn't get started, we don't need to mutex-protect this
        _this->fState = kStateFinished;
    }
}

void hsThread::wait() {
    while (!isFinished())
        YieldThread();
}

bool hsThread::isFinished() const {
    const hsThread_POSIX* _this = (const hsThread_POSIX*)fThreadData;
    return (_this->fState == kStateFinished);
}

void hsThread::YieldThread() {
    pthread_yield();
}


/* hsMutex */
hsMutex::hsMutex() {
    fMutexData = (void*)(new hsMutex_POSIX);
    s_allMutexLock.lock();
    s_allMutexes.push_back(this);
    s_allMutexLock.unlock();
}

hsMutex::~hsMutex() {
    s_allMutexLock.lock();
    std::list<hsMutex*>::iterator it;
    for (it = s_allMutexes.begin(); it != s_allMutexes.end(); it++) {
        if (*it == this) {
            s_allMutexes.erase(it);
            break;
        }
    }
    s_allMutexLock.unlock();
    delete (hsMutex_POSIX*)fMutexData;
}

void hsMutex::lock() {
    hsMutex_POSIX* _this = (hsMutex_POSIX*)fMutexData;
    pthread_mutex_lock(&_this->fMutex);
    _this->fOwner = pthread_self();
    _this->fLocked = true;
}

void hsMutex::unlock() {
    hsMutex_POSIX* _this = (hsMutex_POSIX*)fMutexData;
    _this->fLocked = false;
    pthread_mutex_unlock(&_this->fMutex);
}
