#include "hsRefCnt.h"

hsRefCnt::hsRefCnt() : refCount(1) {  }
hsRefCnt::~hsRefCnt() { }

int hsRefCnt::RefCnt() { return refCount; }

int hsRefCnt::UnRef() {
    if (refCount == 1)
        delete this;
    return --refCount;
}

void hsRefCnt::Ref() {
    refCount++;
}
