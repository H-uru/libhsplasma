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

    inline size_t getSize() { return count; }

    void setSize(size_t cap) {
        if (count == cap) return;

        if (cap <= 0) {
            clear();
            return;
        }
        
        T* newData = new T[cap];
        size_t min = (count < cap) ? count : cap;
        if (data != NULL) {
            memcpy(newData, data, min * sizeof(T));
            delete[] data;
        }
        data = newData;
        count = cap;
    }

    void setSizeNull(size_t cap) {
        delete[] data;
        data = new T[cap];
        memset(data, 0, cap * sizeof(T));
        count = cap;
    }

    void incSize(size_t num = 1) {
        setSize(getSize() + num);
    }

    void decSize(size_t num = 1) {
        setSize(getSize() - num);
    }

    void append(const T& item) {
        incSize();
        data[count - 1] = item;
    }

    T& remove(size_t idx) {
        T& dItm = data[idx];
        for (size_t i=idx; i<count; i++)
            data[i] = data[i+1];
        decSize();
        return dItm;
    }

    T& get(size_t idx) { return data[idx]; }
    void set(size_t idx, const T& item) { data[idx] = item; }

    T& operator[](size_t idx) { return data[idx]; }

    void push(const T& item) { append(item); }
    T& pop() { return remove(count-1); }
};

#endif

