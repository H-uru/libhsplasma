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
        if (data != NULL) delete[] data;
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
        if (max < cap) {
            T* newData = new T[cap];
            if (data != NULL) {
                memcpy(newData, data, count * sizeof(T));
                delete[] data;
            }
            max = cap;
            data = newData;
        }
        count = cap;
    }

    void setSizeNull(int cap) {
        delete[] data;
        data = new T[cap];
        memset(data, 0, count * sizeof(T));
        max = count = cap;
    }

    void compact() {
        if (max == count) return;
        T* newData = new T[count];
        if (data != NULL) {
            memcpy(newData, data, count * sizeof(T));
            delete[] data;
        }
        max = count;
        data = newData;
    }

    void incSize(int num = 1) {
        setSize(getSize() + num);
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

    T& get(int idx) { return data[idx]; }
    void set(int idx, T& item) { data[idx] = item; }

    T& operator[](int idx) { return data[idx]; }

    void push(T& item) { append(item); }
    T& pop() { return remove(count-1); }
};

#endif

