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
        if (data != NULL)
            delete[] data;
        data = NULL;
        count = 0;
        max = 0;
    }

    int getSize() { return count; }
    int getCap()  { return max;   }

    void setSize(int cap) {
        if (max == cap) return;
        max = cap;
        T* newData = new T[max];
        int m = (count > cap) ? cap : count;
        for (int i=0; i<m; i++)
            newData[i] = data[i];
        if (data != NULL)
            delete[] data;
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
};

#endif

