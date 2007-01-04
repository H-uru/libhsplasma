#include "hsRefCount.h"

int hsRefCount::refCount = 0;

hsRefCount::hsRefCount() {  }
hsRefCount::~hsRefCount() { }

int hsRefCount::getRefCount() { return refCount; }

int hsRefCount::RemoveRef() {
    return --refCount;
}

void hsRefCount::AddRef() {
    refCount++;
}

