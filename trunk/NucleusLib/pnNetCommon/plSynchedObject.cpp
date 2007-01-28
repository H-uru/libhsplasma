#include "plSynchedObject.h"

plSynchedObject::plSynchedObject(PlasmaVer pv) { }
plSynchedObject::~plSynchedObject() { }

short plSynchedObject::ClassIndex() { return 0x0028; }

void plSynchedObject::read(hsStream * S) {
    hsKeyedObject::read(S);
    SDLKeys.clear();
    SDLKeys2.clear();
    flags = S->readInt();

    if (flags & 0x10) {
        SDLKeys.setSize(S->readShort());
        for (int i=0; i<SDLKeys.getSize(); i++)
            SDLKeys[i] = S->readSafeStr();
    }
    if (flags & 0x40) {
        SDLKeys2.setSize(S->readShort());
        for (int i=0; i<SDLKeys2.getSize(); i++)
            SDLKeys2[i] = S->readSafeStr();
    }
}

void plSynchedObject::write(hsStream * S) {
    hsKeyedObject::write(S);
    S->writeInt(flags);
    if (flags & 0x10) {
        for (int i=0; i<SDLKeys.getSize(); i++)
            S->writeSafeStr(SDLKeys[i]);
    }
    if (flags & 0x40) {
        for (int i=0; i<SDLKeys2.getSize(); i++)
            S->writeSafeStr(SDLKeys2[i]);
    }
}

