#ifndef _PLSYNCHEDOBJECT_H
#define _PLSYNCHEDOBJECT_H

#include "NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "CoreLib/hsTArray.hpp"

DllClass plSynchedObject : public hsKeyedObject {
public:
    enum LocallyOwnedAnswer { kNo, kYes };

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

    class StateDefn {
        plKey* fObjKey;
        unsigned int fSendFlags;
        char* fSDLName;
    };

protected:
    unsigned int fSynchFlags;
    hsTArray<plString> SDLExcludeList;
    hsTArray<plString> SDLVolatileList;

public:
    plSynchedObject();
    virtual ~plSynchedObject();

    DECLARE_CREATABLE(plSynchedObject)
    
    int getFlags() const;

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif

