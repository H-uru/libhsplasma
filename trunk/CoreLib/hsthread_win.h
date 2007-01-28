class hsMutex {
protected:
    void * fMutexH;

public:
    hsMutex(const class hsMutex &);
    hsMutex::hsMutex();
    hsMutex::~hsMutex();
    void hsMutex::Lock();
    int hsMutex::TryLock();
    void hsMutex::Unlock();
};
