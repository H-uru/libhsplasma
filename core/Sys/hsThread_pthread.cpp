#include "hsThread.h"
#include "Debug/hsExceptions.h"
#include <pthread.h>

/* hsThread */
enum { kStatePending, kStateRunning, kStateFinished };

struct hsThread_POSIX {
    pthread_t fThreadHandle;
    pthread_mutex_t fMetaMutex;
    unsigned int fRefs;
    int fState;

    hsThread_POSIX()
    : fThreadHandle((pthread_t)-1), fRefs(1), fState(kStatePending) { }

    /* Don't ever call this directly...  Use unref or kill */
    ~hsThread_POSIX() { }

    /* This should only ever be called from within a mutex lock */
    void ref() { fRefs++; }

    void unref() {
        pthread_mutex_lock(&fMetaMutex);
        if (--fRefs == 0) {
            pthread_mutex_unlock(&fMetaMutex);
            pthread_mutex_destroy(&fMetaMutex);
            delete this;
            return;
        }
        pthread_mutex_unlock(&fMetaMutex);
    }

    void kill() {
        pthread_mutex_lock(&fMetaMutex);
        if ((((int)fThreadHandle > 0) && (fState != kStateFinished))) {
            pthread_cancel(fThreadHandle);
            if (--fRefs == 0) {
                pthread_mutex_unlock(&fMetaMutex);
                pthread_mutex_destroy(&fMetaMutex);
                delete this;
                return;
            }
        }
        pthread_mutex_unlock(&fMetaMutex);
    }

    bool isFinished() {
        pthread_mutex_lock(&fMetaMutex);
        bool finished = (fState == kStateFinished);
        pthread_mutex_unlock(&fMetaMutex);
        return finished;
    }
};

#define TSELF       ((hsThread*)self)
#define THREAD      ((hsThread_POSIX*)TSELF->fThreadData)
#define TDATA       ((hsThread_POSIX*)fThreadData)
#define TDATAinit   ((hsThread_POSIX*)init.fThreadData)

void* hsThread::s_threadstart(void* self) {
    TSELF->run();

    pthread_mutex_lock(&THREAD->fMetaMutex);
    THREAD->fState = kStateFinished;
    pthread_mutex_unlock(&THREAD->fMetaMutex);

    return NULL;
}

hsThread::hsThread()
        : fThreadData((void*)(new hsThread_POSIX)) { }

hsThread::hsThread(const hsThread& init) {
    // This whole operation needs to be atomic, so we don't delete the
    // thread before we've finished copying it
    pthread_mutex_lock(&TDATAinit->fMetaMutex);
    fThreadData = init.fThreadData;
    TDATA->ref();
    pthread_mutex_unlock(&TDATAinit->fMetaMutex);
}

hsThread::~hsThread() { TDATA->unref(); }

void hsThread::start() {
    if (TDATA->fState == kStateRunning)
        throw hsBadParamException(__FILE__, __LINE__, "Thread already running!");

    TDATA->fState = kStateRunning;
    if (pthread_create(&TDATA->fThreadHandle, NULL, &s_threadstart, this) != 0) {
        // If the thread didn't get started, we don't need to mutex-protect this
        TDATA->fState = kStateFinished;
    }
}

void hsThread::wait() {
    while (!isFinished())
        Yield();
}

void hsThread::finish() {
    pthread_mutex_lock(&TDATA->fMetaMutex);
    TDATA->fState = kStateFinished;
    pthread_mutex_unlock(&TDATA->fMetaMutex);
}

bool hsThread::isFinished() {
    pthread_mutex_lock(&TDATA->fMetaMutex);
    bool result = (TDATA->fState == kStateFinished);
    pthread_mutex_unlock(&TDATA->fMetaMutex);
    return result;
}

void hsThread::Yield() {
    pthread_yield();
}


/* hsMutex */
struct hsMutex_POSIX {
    pthread_mutex_t fMutex;
    unsigned int fRefs;

    hsMutex_POSIX() : fRefs(1) {
        pthread_mutex_init(&fMutex, NULL);
    }

    /* Use unref() */
    ~hsMutex_POSIX() { }

    /* This should only ever be called while the mutex is locked */
    void ref() { fRefs++; }

    void unref() {
        pthread_mutex_lock(&fMutex);
        if (--fRefs == 0) {
            pthread_mutex_unlock(&fMutex);
            pthread_mutex_destroy(&fMutex);
            delete this;
        } else {
            pthread_mutex_unlock(&fMutex);
        }
    }
};

#define MDATA       ((hsMutex_POSIX*)fMutexData)
#define MDATAinit   ((hsMutex_POSIX*)init.fMutexData)

hsMutex::hsMutex()
       : fMutexData((void*)(new hsMutex_POSIX)) { }

hsMutex::hsMutex(const hsMutex& init) {
    // This whole operation needs to be atomic, so we don't delete the
    // mutex before we've finished copying it
    pthread_mutex_lock(&MDATAinit->fMutex);
    fMutexData = init.fMutexData;
    MDATA->ref();
    pthread_mutex_unlock(&MDATAinit->fMutex);
}

hsMutex::~hsMutex() { MDATA->unref(); }

void hsMutex::lock() { pthread_mutex_lock(&MDATA->fMutex); }
void hsMutex::unlock() { pthread_mutex_unlock(&MDATA->fMutex); }
