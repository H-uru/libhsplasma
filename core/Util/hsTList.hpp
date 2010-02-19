#ifndef _HSTLIST_H
#define _HSTLIST_H

#include "Debug/hsExceptions.h"

template<typename T>
class hsTList {
private:
    struct Link {
        T item;
        Link* next;
        Link* prev;
    };

    size_t count;
    Link* first;
    Link* last;
    mutable Link* iter; // Don't shoot me :P

public:
    hsTList() : count(0), first(NULL), last(NULL), iter(NULL) { }

    hsTList(const hsTList<T>& init)
           : count(0), first(NULL), last(NULL), iter(NULL) {
        if (init.count > 0) {
            rpush(init.iBegin());
            while (!init.iAtEnd())
                rpush(init.next());
        }
    }

    ~hsTList<T>() {
        clear();
    }

    hsTList<T>& operator=(const hsTList<T>& cpy) {
        if (&cpy == this)
            return *this;

        clear();
        if (cpy.count > 0) {
            rpush(cpy.iBegin());
            while (!cpy.iAtEnd())
                rpush(cpy.next());
        }
        return *this;
    }

    void clear() {
        while (first != NULL)
            pop();
        iter = NULL;
    }

    size_t getSize() const { return count; }
    bool empty() const { return count == 0; }

    void push(const T& item) {
        Link* top = new Link;
        top->item = item;
        top->next = first;
        top->prev = NULL;
        if (first != NULL)
            first->prev = top;
        first = top;

        if (count == 0)
            last = first;
        count++;
    }

    void rpush(const T& item) {
        Link* bottom = new Link;
        bottom->item = item;
        bottom->next = NULL;
        bottom->prev = last;
        if (last != NULL)
            last->next = bottom;
        last = bottom;

        if (count == 0)
            first = last;
        count++;
    }

    T pop() {
        if (count == 0)
            throw hsOutOfBoundsException(__FILE__, __LINE__);

        T top = first->item;
        Link* next = first->next;
        delete first;
        if (next != NULL)
            next->prev = NULL;
        first = next;

        count--;
        if (count == 0)
            last = NULL;

        return top;
    }

    T rpop() {
        if (count == 0)
            throw hsOutOfBoundsException(__FILE__, __LINE__);

        T bottom = last->item;
        Link* prev = last->prev;
        delete last;
        if (prev != NULL)
            prev->next = NULL;
        last = prev;

        count--;
        if (count == 0)
            first = NULL;

        return bottom;
    }

    const T& get(size_t idx) const {
        if (idx >= count)
            throw hsOutOfBoundsException(__FILE__, __LINE__);
        Link* pos = first;
        for (size_t i=0; i<idx; i++)
            pos = pos->next;
        return pos->item;
    }

    void set(size_t idx, const T& item) {
        if (idx >= count)
            throw hsOutOfBoundsException(__FILE__, __LINE__);
        Link* pos = first;
        for (size_t i=0; i<idx; i++)
            pos = pos->next;
        pos->item = item;
    }

    T& top() { return first->item; }
    T& bottom() { return last->item; }

    T& operator[](size_t idx) {
        if (idx >= count)
            throw hsOutOfBoundsException(__FILE__, __LINE__);
        Link* pos = first;
        for (size_t i=0; i<idx; i++)
            pos = pos->next;
        return pos->item;
    }

    // For linear iteration:
    T& iBegin() const {
        iter = first;
        return iter->item;
    }

    T& iEnd() const {
        iter = last;
        return iter->item;
    }

    bool iAtBegin() const { return iter == first; }
    bool iAtEnd() const { return iter == last; }

    T& next() const {
        if (iter == NULL)
            return iBegin();
        if (!iAtEnd())
            iter = iter->next;
        return iter->item;
    }

    T& prev() const {
        if (iter == NULL)
            return iEnd();
        if (!iAtBegin())
            iter = iter->prev;
        return iter->item;
    }

    T& icur() const { return iter->item; }
};

#endif
