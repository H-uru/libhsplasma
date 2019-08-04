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

#ifndef _PLSYNCHEDOBJECT_H
#define _PLSYNCHEDOBJECT_H

#include "PRP/KeyedObject/hsKeyedObject.h"

class PLASMA_DLL plSynchedObject : public hsKeyedObject
{
    CREATABLE(plSynchedObject, kSynchedObject, hsKeyedObject)

public:
    enum Flags
    {
        kDontDirty = 0x1,
        kSendReliably = 0x2,
        kHasConstantNetGroup = 0x4,
        kDontSynchGameMessages = 0x8,
        kExcludePersistentState = 0x10,
        kExcludeAllPersistentState = 0x20,
        kLocalOnly = kExcludeAllPersistentState | kDontSynchGameMessages,
        kHasVolatileState = 0x40,
        kAllStateIsVolatile = 0x80
    };

    enum SDLSendFlags
    {
        kBCastToClients = 0x1,
        kForceFullSend = 0x2,
        kSkipLocalOwnershipCheck = 0x4,
        kSendImmediately = 0x8,
        kDontPersistOnServer = 0x10,
        kUseRelevanceRegions = 0x20,
        kNewState = 0x40,
        kIsAvatarState = 0x80
    };

protected:
    unsigned int fSynchFlags;
    std::vector<ST::string> fSDLExcludeList;
    std::vector<ST::string> fSDLVolatileList;

public:
    plSynchedObject() : fSynchFlags() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    int getSynchFlags() const { return fSynchFlags; }
    void setSynchFlags(unsigned int flags) { fSynchFlags = flags; }

    const std::vector<ST::string>& getExcludes() const { return fSDLExcludeList; }
    const std::vector<ST::string>& getVolatiles() const { return fSDLVolatileList; }
    void setExclude(const ST::string& sdl);
    void setVolatile(const ST::string& sdl);
    void clearExcludes();
    void clearVolatiles();
};

#endif
