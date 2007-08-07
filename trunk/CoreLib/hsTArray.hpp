#ifndef _HSTARRAY_H
#define _HSTARRAY_H

#include <stdlib.h>
#include <string.h>
#include "../PlasmaDefs.h"

template <typename T>
DllClass hsTArray {
private:
    unsigned short count;
    T* data;

public:
    hsTArray() : count(0) {
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
	}

    inline int getSize() { return count; }

    void setSize(int cap) {
        if (count == cap) return;

        if (cap <= 0) {
            clear();
            return;
        }
        
        T* newData = new T[cap];
        int min = (count < cap) ? count : cap;
        if (data != NULL) {
            memcpy(newData, data, min * sizeof(T));
            delete[] data;
        }
        data = newData;
        count = cap;
    }

    void setSizeNull(int cap) {
        delete[] data;
        data = new T[cap];
        memset(data, 0, cap * sizeof(T));
        count = cap;
    }

    void incSize(int num = 1) {
        setSize(getSize() + num);
    }

    void decSize(int num = 1) {
        setSize(getSize() - num);
    }

    void append(T& item) {
        incSize();
        data[count - 1] = item;
    }

    T& remove(int idx) {
        T& dItm = data[idx];
        for (int i=idx; i<count; i++)
            data[i] = data[i+1];
        decSize();
        return dItm;
    }

    T& get(int idx) { return data[idx]; }
    void set(int idx, T& item) { data[idx] = item; }

    T& operator[](int idx) { return data[idx]; }

    void push(T& item) { append(item); }
    T& pop() { return remove(count-1); }
};

#endif

