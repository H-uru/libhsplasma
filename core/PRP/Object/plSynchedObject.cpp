/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "plSynchedObject.h"
#include "Debug/plDebug.h"

plSynchedObject::plSynchedObject() : fSynchFlags(0) { }

void plSynchedObject::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);
    fSDLExcludeList.clear();
    fSDLVolatileList.clear();
    fSynchFlags = S->readInt();

    unsigned short count, len, i;
    if (S->getVer() < pvEoa || S->getVer() == pvUniversal) {
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

        // Synch Flags adjustment -- this is guesswork :/
        unsigned int eoaFlags = fSynchFlags;
        fSynchFlags = ((eoaFlags & 0x1) ? kDontDirty : 0)
                    | ((eoaFlags & 0x2) ? kExcludePersistentState : 0)
                    | ((eoaFlags & 0x4) ? kExcludeAllPersistentState : 0);
        if (eoaFlags & 0xFFFFFFF0)
            plDebug::Debug("Myst5 Object got unknown synch flags: %08X", eoaFlags);
    }
}

void plSynchedObject::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    unsigned short i;
    if (S->getVer() < pvEoa || S->getVer() == pvUniversal) {
        S->writeInt(fSynchFlags);
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
        // Synch Flags adjustment -- this is guesswork :/
        unsigned int eoaFlags = ((fSynchFlags & kDontDirty) ? 0x1 : 0)
                              | ((fSynchFlags & kExcludePersistentState) ? 0x2 : 0)
                              | ((fSynchFlags & kExcludeAllPersistentState) ? 0x4 : 0);

        S->writeInt(eoaFlags);
        if ((eoaFlags & 0x6) == 0) {
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

void plSynchedObject::setExclude(const plString& sdl) {
    fSynchFlags |= kExcludePersistentState;
    fSDLExcludeList.append(sdl);
}

void plSynchedObject::setVolatile(const plString& sdl) {
    fSynchFlags |= kHasVolatileState;
    fSDLVolatileList.append(sdl);
}

void plSynchedObject::clearExcludes() {
    fSDLExcludeList.clear();
    fSynchFlags &= ~kExcludePersistentState;
}

void plSynchedObject::clearVolatiles() {
    fSDLVolatileList.clear();
    fSynchFlags &= ~kHasVolatileState;
}
