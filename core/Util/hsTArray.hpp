/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _HSTARRAY_H
#define _HSTARRAY_H

#ifdef _MSC_VER
#pragma warning(disable: 4251)
#endif

#include <stdlib.h>
#include <string.h>
#include "Debug/hsExceptions.h"

template <class T>
class hsTArray {
private:
    size_t count;
    T* data;

public:
    hsTArray() : count(0), data(NULL) { }

    hsTArray(const hsTArray& init) : count(init.count) {
        data = new T[count];
        for (size_t i=0; i<count; i++)
            data[i] = init.data[i];
    }

    ~hsTArray<T>() {
        delete[] data;
    }

    hsTArray<T>& operator=(const hsTArray& cpy) {
        if (&cpy == this)
            return *this;

        clear();
        count = cpy.count;
        data = new T[count];
        for (size_t i=0; i<count; i++)
            data[i] = cpy.data[i];
        return *this;
    }

    void clear() {
        delete[] data;
        data = NULL;
        count = 0;
    }

    size_t getSize() const { return count; }
    bool empty() const { return count == 0; }

    void setSize(size_t cap) {
        if (count == cap) return;

        if (cap == 0) {
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
        count = cap;
    }

    void setSizeNull(size_t cap) {
        if (cap == 0) {
            clear();
            return;
        }

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

    void append(const hsTArray<T>& items) {
        size_t ins = getSize();
        incSize(items.getSize());
        for (size_t i=0; i<items.getSize(); i++)
            data[ins + i] = items.get(i);
    }

    void remove(size_t idx) {
        if (idx >= count)
            throw hsOutOfBoundsException(__FILE__, __LINE__);

        for (size_t i=idx; i<(count-1); i++)
            data[i] = data[i+1];
        decSize();
    }

    const T& get(size_t idx) const {
        if (idx >= count)
            throw hsOutOfBoundsException(__FILE__, __LINE__);
        return data[idx];
    }

    void set(size_t idx, const T& item) {
        if (idx >= count)
            throw hsOutOfBoundsException(__FILE__, __LINE__);
        data[idx] = item;
    }

    T& operator[](size_t idx) {
        if (idx >= count)
            throw hsOutOfBoundsException(__FILE__, __LINE__);
        return data[idx];
    }

    const T& operator[](size_t idx) const {
        return get(idx);
    }

    void push(const T& item) { append(item); }
    T& pop() { return remove(count-1); }

    size_t find(const T& item) const {
        for (size_t i=0; i<count; i++) {
            if (data[i] == item)
                return i;
        }
        return (size_t)-1;
    }
};

#endif

