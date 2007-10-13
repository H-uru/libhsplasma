#ifndef _HSTARRAY_H
#define _HSTARRAY_H

#include <stdlib.h>
#include <string.h>
#include "hsExceptions.h"

template <typename T>
DllClass hsTArray {
private:
    unsigned short count;
    T* data;

public:
    hsTArray() : count(0), data(NULL) { }

    ~hsTArray<T>() {
        if (data != NULL) delete[] data;
    }

    void clear() {
        if (data != NULL)
            delete[] data;
        data = NULL;
        count = 0;
    }
    
    size_t getSize() { return count; }
    bool empty() { return count == 0; }

    void setSize(size_t cap) {
        if (count == cap) return;

        if (cap <= 0) {
            clear();
            return;
        }
        
        T* newData = new T[cap];
        size_t min = (count < cap) ? count : cap;
        if (data != NULL) {
            for (size_t i=0; i<min; i++)
                newData[i] = data[i];
            //memcpy(newData, data, min * sizeof(T));
            delete[] data;
        }
        data = newData;
        count = (unsigned short)cap;
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

    void remove(size_t idx) {
        if (idx >= count)
            throw hsOutOfBoundsException(__FILE__, __LINE__);

        for (size_t i=idx; i<count; i++)
            data[i] = data[i+1];
        decSize();
    }

    T& get(size_t idx) {
        if (idx >= count)
            throw hsOutOfBoundsException(__FILE__, __LINE__);
        return data[idx];
    }

    void set(size_t idx, const T& item) {
        if (idx >= count)
            throw hsOutOfBoundsException(__FILE__, __LINE__);
        data[idx] = item;
    }

    T& operator[](size_t idx) { return get(idx); }

    void push(const T& item) { append(item); }
    T& pop() { return remove(count-1); }
};

#endif

