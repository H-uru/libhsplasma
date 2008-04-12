#ifndef _HSTLIST_H
#define _HSTLIST_H

#include "hsExceptions.h"

template<typename T>
class hsTList {
private:
    struct Link {
        T item;
        Link* next;
        Link* prev;
    };

    unsigned long count;
    Link* first;
    Link* last;
    Link* iter;

public:
    hsTList() : count(0), first(NULL), last(NULL) { }

    ~hsTList<T>() {
        clear();
    }

    void clear() {
        while (first != NULL) pop();
    }

    size_t getSize() { return count; }
    bool empty() { return count == 0; }

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

    T& get(size_t idx) {
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

    T& operator[](size_t idx) { return get(idx); }

    // For linear iteration:
    T& iBegin() {
        iter = first;
        return iter->item;
    }

    T& iEnd() {
        iter = last;
        return iter->item;
    }

    bool iAtBegin() { return iter == first; }
    bool iAtEnd() { return iter == last; }

    T& next() {
        if (!iAtEnd())
            iter = iter->next;
        return iter->item;
    }

    T& prev() {
        if (!iAtBegin())
            iter = iter->prev;
        return iter->item;
    }

    T& icur() { return iter->item; }
};

#endif
