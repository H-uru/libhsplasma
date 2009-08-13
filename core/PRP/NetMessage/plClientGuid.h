#ifndef _PLCLIENTGUID_H
#define _PLCLIENTGUID_H

#include "PRP/plCreatable.h"
#include "Sys/plUuid.h"

DllClass plClientGuid : public plCreatable {
public:
    enum Flags {
        kAcctUuid = 0x1,
        kPlayerID = 0x2,
        kTempPlayerID = 0x4,
        kCCRLevel = 0x8,
        kProtectedLogin = 0x10,
        kBuildType = 0x20,
        kPlayerName = 0x40,
        kSrcAddr = 0x80,
        kSrcPort = 0x100,
        kReserved = 0x200,
        kClientKey = 0x400,
    };

private:
    unsigned short fFlags;
    plUuid fAcctUuid;
    unsigned int fPlayerID;
    plString fPlayerName;
    unsigned char fCCRLevel, fProtectedLogin, fBuildType;
    unsigned int fSrcAddr;
    unsigned short fSrcPort;
    unsigned short fReserved;
    plString fClientKey;

public:
    plClientGuid();
    ~plClientGuid();

    DECLARE_CREATABLE(plClientGuid)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
