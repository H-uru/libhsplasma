#include "plSynchedObject.h"

plSynchedObject::plSynchedObject() { }
plSynchedObject::~plSynchedObject() { }

void plSynchedObject::read(hsStream * S) {
    hsKeyedObject::read(S);
    SDLKeys.clear();
    SDLKeys2.clear();
    flags = S->readInt();

    if (flags & 0x10)
        SDLKeys.read16(S);
    if (flags & 0x40)
        SDLKeys.read16(S);
}

void plSynchedObject::write(hsStream * S) {
    hsKeyedObject::write(S);
    S->writeInt(flags);
    if (flags & 0x10)
        SDLKeys.write16(S);
    if (flags & 0x40)
        SDLKeys.write16(S);
}

const char* plSynchedObject::getTypeName() { return "plSynchedObject"; }
const int plSynchedObject::getTypeNum() { return 0x28; }

