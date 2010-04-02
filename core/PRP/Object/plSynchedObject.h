#ifndef _PLSYNCHEDOBJECT_H
#define _PLSYNCHEDOBJECT_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "Util/hsTArray.hpp"

DllClass plSynchedObject : public hsKeyedObject {
    CREATABLE(plSynchedObject, kSynchedObject, hsKeyedObject)

public:
    enum Flags {
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

    enum SDLSendFlags {
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
    hsTArray<plString> fSDLExcludeList;
    hsTArray<plString> fSDLVolatileList;

public:
    plSynchedObject();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    int getFlags() const { return fSynchFlags; }
    void setFlags(int flags) { fSynchFlags = flags; }

    const hsTArray<plString>& getExcludes() const { return fSDLExcludeList; }
    const hsTArray<plString>& getVolatiles() const { return fSDLVolatileList; }
    void setExclude(const plString& sdl);
    void setVolatile(const plString& sdl);
    void clearExcludes();
    void clearVolatiles();
};

#endif
