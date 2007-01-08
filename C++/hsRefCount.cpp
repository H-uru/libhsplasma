#include "hsRefCount.h"

hsRefCount::hsRefCount() : refCount(1) {  }
hsRefCount::~hsRefCount() { }

int hsRefCount::getRefCount() { return refCount; }

int hsRefCount::UnRef() {
    if (refCount == 1)
        delete this;

    return --refCount;
}

void hsRefCount::Ref() {
    refCount++;
}

