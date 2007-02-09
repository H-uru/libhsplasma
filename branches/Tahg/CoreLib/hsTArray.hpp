#ifndef _HSTARRAY_H
#define _HSTARRAY_H

#include <stdlib.h>
#include "hsStream.h"

template <class T>
class hsTArray {
private:
    unsigned short max, count;
    T* data;

public:
    hsTArray() : max(0), count(0) {
        data = NULL;
    }
    ~hsTArray<T>() {
        if (data != NULL)
            delete[] data;
    }

    void clear() {
        Reset();
    }
    
    inline void Reset() {
        if (data != NULL)
            delete[] data;
        data = NULL;
        count = 0;
        max = 0;
	}

    inline int getSize() { return count; }
    int getCap() { return max; }

    void setSize(int cap) {
        if (max == cap) return;
        T* newData = new T[cap];
        for (int i=0; i<count; i++)
            newData[i] = data[i];
        if (data != NULL)
            delete[] data;
        max = count = cap;
        data = newData;
    }

    void append(T& item) {
        setSize(count+1);
        data[count++] = item;
    }

    T& remove(int idx) {
        T dItm = data[idx];
        for (int i=idx; i<count; i++)
            data[i] = data[i+1];
        data[--count] = NULL;
        return dItm;
    }

    T& operator[](int idx) {
        return data[idx];
    }
public:
	hsTArray<T>(const hsTArray<T> & rhs) 
	{
		max = count = rhs.count;
		data = (T *)malloc (count * sizeof(T));
		memcpy(data, rhs.data, count * sizeof(T));
	}
  hsTArray<T>(int);
//  hsTArray<T>::hsTArray<T>();
//  hsTArray<T>::~hsTArray<T>();
  void Expand(int);
  bool operator==(const hsTArray<T> &);
  void Swap(hsTArray<T> &);
  void Set(int, const T &);
  const T & Get(int);
//  T & hsTArray<T>::operator[](int);
  T * FirstIter();
  T * StopIter();
  int Count();
  int GetCount();
  void SetCount(int);
  void SetCountAndZero(int);
  void ExpandAndZero(int);
//  void Reset();
  void Insert(int, int, T *);
  void Insert(int, const T &);
  T * Insert(int);
  void InsertAtIndex(int, const T &);
  void Remove(int, int);
  void Remove(int);
  int RemoveItem(const T &);
  void Push(const T & item) { //578
	  IncCount(count, 1);
	  data[count-1] = item;
  }
  T * Push();
  void Append(const T &);
  T Pop();
  const T & Peek();
  int Find(const T &){return -1;}
//  T * ForEach(function  *, void *, void *);
//  T * ForEach(function  *, void *);
//  T * ForEach(function  *);
  T * DetachArray();
  T * AcquireArray();
private:
	void IncCount(int index, int count) { //799
		int newCount = this->count + count;
		if(newCount > max) {

		}
	}
  void DecCount(int, int);

};

#endif

