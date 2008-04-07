#include "plSynchedObject.h"

plSynchedObject::plSynchedObject() { }
plSynchedObject::~plSynchedObject() { }

IMPLEMENT_CREATABLE(plSynchedObject, kSynchedObject, hsKeyedObject)

int plSynchedObject::getFlags() { return fSynchFlags; }

void plSynchedObject::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);
    SDLExcludeList.clear();
    SDLVolatileList.clear();
    fSynchFlags = S->readInt();

    unsigned short count, len, i;
    if (S->getVer() < pvEoa) {
        if (fSynchFlags & kExcludePersistentState) {
            count = S->readShort();
            SDLExcludeList.setSize(count);
            for (i=0; i<count; i++) {
                len = S->readShort();
                SDLExcludeList[i] = S->readStr(len);
            }
        }
        if (fSynchFlags & kHasVolatileState) {
            count = S->readShort();
            SDLVolatileList.setSize(count);
            for (i=0; i<count; i++) {
                len = S->readShort();
                SDLVolatileList[i] = S->readStr(len);
            }
        }
    } else {
        fSynchFlags &= ~0x8;
        if ((fSynchFlags & 0x6) == 0) {
            count = S->readShort();
            SDLExcludeList.setSize(count);
            for (i=0; i<count; i++) {
                len = S->readShort();
                SDLExcludeList[i] = S->readStr(len);
            }
        }
    }
}

void plSynchedObject::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);
    S->writeInt(fSynchFlags);

    unsigned short i;
    if (fSynchFlags & kExcludePersistentState) {
        S->writeShort(SDLExcludeList.getSize());
        for (i=0; i<SDLExcludeList.getSize(); i++) {
            S->writeShort(SDLExcludeList[i].len());
            S->writeStr(SDLExcludeList[i]);
        }
    }
    if (fSynchFlags & kHasVolatileState) {
        S->writeShort(SDLVolatileList.getSize());
        for (i=0; i<SDLVolatileList.getSize(); i++) {
            S->writeShort(SDLVolatileList[i].len());
            S->writeStr(SDLVolatileList[i]);
        }
    }
}

void plSynchedObject::prcWrite(pfPrcHelper* prc) {
    hsKeyedObject::prcWrite(prc);
    
    prc->startTag("SynchFlags");
    prc->writeParam("value", fSynchFlags);
    prc->endTag(true);

    unsigned int i;
    if (fSynchFlags & kExcludePersistentState) {
        prc->writeSimpleTag("ExcludePersistentStates");
        for (i=0; i<SDLExcludeList.getSize(); i++) {
            prc->startTag("State");
            prc->writeParam("name", SDLExcludeList[i]);
            prc->endTag(true);
        }
        prc->closeTag();
    }
    if (fSynchFlags & kHasVolatileState) {
        prc->writeSimpleTag("VolatileStates");
        for (i=0; i<SDLVolatileList.getSize(); i++) {
            prc->startTag("State");
            prc->writeParam("name", SDLVolatileList[i]);
            prc->endTag(true);
        }
        prc->closeTag();
    }
}
