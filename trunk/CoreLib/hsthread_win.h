class hsMutex {
  void * fMutexH; //this+0x4

public:
  hsMutex(const class hsMutex &);
  hsMutex::hsMutex();
  hsMutex::~hsMutex();
  void hsMutex::Lock();
  int hsMutex::TryLock();
  void hsMutex::Unlock();

private:

protected:
};
