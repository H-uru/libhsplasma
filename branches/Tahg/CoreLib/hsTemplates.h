#ifndef HSTEMPLATES_H
#define HSTEMPLATES_H


class hsLargeArrayBase {
  unsigned long fUseCount; //this+0x0
  unsigned long fTotalCount; //this+0x4

public:
  unsigned long GetNumAlloc(){}

protected:
  void hsLargeArrayBase::GrowArraySize(unsigned long){}
  hsLargeArrayBase::hsLargeArrayBase(){}
};

template <class T>
class hsLargeArray : public hsLargeArrayBase {
  T * fArray; //this+0x8

public:
  hsLargeArray<T>(const hsLargeArray<T> &){}
  hsLargeArray<T>(int){}
  hsLargeArray<T>(){}
  ~hsLargeArray<T>(){}
  void Expand(int){}
  void Swap(hsLargeArray<T> &){}
  void Set(int, const T &){}
  const T & Get(int){}
  T & operator[](int){}
  T * FirstIter(){}
  T * StopIter(){}
  int Count(){}
  int GetCount(){}
  void SetCount(int){}
  void SetCountAndZero(int){}
  void ExpandAndZero(int){}
  void Reset(){}
  void Insert(int, int, T *){}
  void Insert(int, const T &){}
  T * Insert(int){}
  void InsertAtIndex(int, const T &){}
  void Remove(int, int){}
  void Remove(int){}
  int RemoveItem(const T &){}
  void Push(const T &){}
  T * Push(){}
  void Append(const T &){}
  T Pop(){}
  const T & Peek(){}
  int Find(const T &){}
//  T * ForEach(*(int (T&, void*, void*)), void *, void *){}
//  T * ForEach(*(int (T&, void*)), void *){}
//  T * ForEach(*(int (T&))){}
  T * DetachArray(){}
  T * AcquireArray(){}

private:
  void IncCount(int, int){}
  void DecCount(int, int){}
};

#endif