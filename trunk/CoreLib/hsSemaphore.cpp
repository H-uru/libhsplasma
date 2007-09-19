#include "hsSemaphore.h"

#ifdef WIN32

hsSemaphore::hsSemaphore(int initialValue, const char* name) {
    fSemaH = CreateSemaphore(NULL, initialValue, 0x7FFFFFFF, name);
    if (fSemaH == NULL)
        throw "Failed to create a semaphore";
}

hsSemaphore::~hsSemaphore() {
    CloseHandle(fSemaH);
}

bool hsSemaphore::wait() {
    unsigned int result = WaitForSingleObject(fSemaH, 0xFFFFFFFF);
    if (result == WAIT_OBJECT_0)
        return true;
    else if (result == WAIT_TIMEOUT)
        return false;
    else
        throw "Semaphore wait broke";
}

bool hsSemaphore::signal() {
    ReleaseSemaphore(fSemaH, 1, NULL);
    return true;
}

#else

hsSemaphore::hsSemaphore(int initialValue, const char* name) {
    fSemaID = semget(IPC_PRIVATE, 1, IPC_CREAT | 0660);
    int setres = semctl(fSemaID, 0, SETVAL, initialValue);
    if (fSemaID == -1 || setres == -1)
        throw "Failed to create a semaphore";
}

hsSemaphore::~hsSemaphore() {
    semctl(fSemaID, 0, IPC_RMID);
}

bool hsSemaphore::wait() {
    static sembuf op[1] = { 0, -1, 0 };
    if (semop(fSemaID, op, 1) == 0)
        return true;
    else
        return false;
}

void hsSemaphore::signal() {
    static sembuf op[1] = { 0, 1, 0 };
    if (semop(fSemaID, op, 1) == 0)
        return true;
    else
        return false;
}

#endif
