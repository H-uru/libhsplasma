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
    if (fSynchFlags & kExcludePersistentState) {
        count = S->readShort();
        for (i=0; i<count; i++) {
            len = S->readShort();
            SDLExcludeList.push_back(S->readStr(len));
        }
    }
    if (fSynchFlags & kHasVolatileState) {
        count = S->readShort();
        for (i=0; i<count; i++) {
            len = S->readShort();
            SDLVolatileList.push_back(S->readStr(len));
        }
    }
}

void plSynchedObject::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);
    S->writeInt(fSynchFlags);

    unsigned short i;
    if (fSynchFlags & kExcludePersistentState) {
        S->writeShort(SDLExcludeList.size());
        for (i=0; i<SDLExcludeList.size(); i++) {
            S->writeShort(SDLExcludeList[i].len());
            S->writeStr(SDLExcludeList[i]);
        }
    }
    if (fSynchFlags & kHasVolatileState) {
        S->writeShort(SDLVolatileList.size());
        for (i=0; i<SDLVolatileList.size(); i++) {
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
        for (i=0; i<SDLExcludeList.size(); i++) {
            prc->startTag("State");
            prc->writeParam("name", SDLExcludeList[i]);
            prc->endTag(true);
        }
        prc->closeTag();
    }
    if (fSynchFlags & kHasVolatileState) {
        prc->writeSimpleTag("VolatileStates");
        for (i=0; i<SDLVolatileList.size(); i++) {
            prc->startTag("State");
            prc->writeParam("name", SDLVolatileList[i]);
            prc->endTag(true);
        }
        prc->closeTag();
    }
}
