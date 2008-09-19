#include "plSynchedObject.h"

plSynchedObject::plSynchedObject() : fSynchFlags(0) { }
plSynchedObject::~plSynchedObject() { }

IMPLEMENT_CREATABLE(plSynchedObject, kSynchedObject, hsKeyedObject)

void plSynchedObject::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);
    fSDLExcludeList.clear();
    fSDLVolatileList.clear();
    fSynchFlags = S->readInt();

    unsigned short count, len, i;
    if (S->getVer() < pvEoa) {
        if (fSynchFlags & kExcludePersistentState) {
            count = S->readShort();
            fSDLExcludeList.setSize(count);
            for (i=0; i<count; i++) {
                len = S->readShort();
                fSDLExcludeList[i] = S->readStr(len);
            }
        }
        if (fSynchFlags & kHasVolatileState) {
            count = S->readShort();
            fSDLVolatileList.setSize(count);
            for (i=0; i<count; i++) {
                len = S->readShort();
                fSDLVolatileList[i] = S->readStr(len);
            }
        }
    } else {
        fSynchFlags &= ~0x8;
        if ((fSynchFlags & 0x6) == 0) {
            count = S->readShort();
            fSDLExcludeList.setSize(count);
            for (i=0; i<count; i++) {
                len = S->readShort();
                fSDLExcludeList[i] = S->readStr(len);
            }
        }
    }
}

void plSynchedObject::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);
    S->writeInt(fSynchFlags);

    unsigned short i;
    if (S->getVer() < pvEoa) {
        if (fSynchFlags & kExcludePersistentState) {
            S->writeShort(fSDLExcludeList.getSize());
            for (i=0; i<fSDLExcludeList.getSize(); i++) {
                S->writeShort(fSDLExcludeList[i].len());
                S->writeStr(fSDLExcludeList[i]);
            }
        }
        if (fSynchFlags & kHasVolatileState) {
            S->writeShort(fSDLVolatileList.getSize());
            for (i=0; i<fSDLVolatileList.getSize(); i++) {
                S->writeShort(fSDLVolatileList[i].len());
                S->writeStr(fSDLVolatileList[i]);
            }
        }
    } else {
        if ((fSynchFlags & 0x6) == 0) {
            S->writeShort(fSDLExcludeList.getSize());
            for (i=0; i<fSDLExcludeList.getSize(); i++) {
                S->writeShort(fSDLExcludeList[i].len());
                S->writeStr(fSDLExcludeList[i]);
            }
        }
    }
}

void plSynchedObject::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);
    
    prc->startTag("SynchParams");
    prc->writeParamHex("flags", fSynchFlags);
    prc->endTag();

    unsigned int i;
    prc->writeTagNoBreak("ExcludePersistentStates");
    for (i=0; i<fSDLExcludeList.getSize(); i++)
        prc->getStream()->writeStr(fSDLExcludeList[i] + " ");
    prc->closeTagNoBreak();
    
    prc->writeTagNoBreak("VolatileStates");
    for (i=0; i<fSDLVolatileList.getSize(); i++)
        prc->getStream()->writeStr(fSDLVolatileList[i] + " ");
    prc->closeTagNoBreak();

    prc->closeTag();
}

void plSynchedObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SynchParams") {
        fSynchFlags = tag->getParam("flags", "0").toUint();
        const pfPrcTag* child = tag->getFirstChild();
        while (child != NULL) {
            if (child->getName() == "ExcludePersistentStates") {
                hsTList<plString> states = child->getContents();
                while (!states.empty())
                    fSDLExcludeList.append(states.pop());
            } else if (child->getName() == "VolatileStates") {
                hsTList<plString> states = child->getContents();
                while (!states.empty())
                    fSDLVolatileList.append(states.pop());
            } else {
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            }
            child = child->getNextSibling();
        }
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}

int plSynchedObject::getFlags() const { return fSynchFlags; }
void plSynchedObject::setFlags(int flags) { fSynchFlags = flags; }

void plSynchedObject::clearExcludes() { fSDLExcludeList.clear(); }
void plSynchedObject::clearVolatiles() { fSDLVolatileList.clear(); }

void plSynchedObject::setExclude(const plString& sdl) {
    fSynchFlags |= kExcludePersistentState;
    fSDLExcludeList.append(sdl);
}

void plSynchedObject::setVolatile(const plString& sdl) {
    fSynchFlags |= kHasVolatileState;
    fSDLVolatileList.append(sdl);
}

const hsTArray<plString>& plSynchedObject::getExcludes() const { return fSDLExcludeList; }
const hsTArray<plString>& plSynchedObject::getVolatiles() const { return fSDLVolatileList; }
