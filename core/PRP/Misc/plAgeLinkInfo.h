#ifndef _PLNETSERVERSESSIONINFO_H
#define _PLNETSERVERSESSIONINFO_H

#include "PRP/plCreatable.h"
#include "Sys/plUUID.h"
#include "plSpawnPointInfo.h"

DllClass plAgeInfoStruct : public plCreatable {
public:
    enum {
        kHasAgeFilename = 0x1,
        kHasAgeInstanceName = 0x2,
        kHasAgeInstanceGuid = 0x4,
        kHasAgeUserDefinedName = 0x8,
        kHasAgeSequenceNumber = 0x10,
        kHasAgeDescription = 0x20,
        kHasAgeLanguage = 0x40
    };

protected:
    unsigned char fFlags;
    plString fAgeFilename, fAgeInstanceName;
    plUUID fAgeInstanceGuid;
    plString fAgeUserDefinedName, fAgeDescription;
    int fAgeSequenceNumber, fAgeLanguage;
    plString fDisplayName;

public:
    plAgeInfoStruct();
    virtual ~plAgeInfoStruct();

    DECLARE_CREATABLE(plAgeInfoStruct)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    void UpdateFlags();
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool isEmpty();
};

DllClass plAgeLinkStruct : public plCreatable {
public:
    enum {
        kHasAgeInfo = 0x1,
        kHasLinkingRules = 0x2,
        kHasSpawnPt_DEAD = 0x4,
        kHasSpawnPt_DEAD2 = 0x8,
        kHasAmCCR = 0x10,
        kHasSpawnPt = 0x20,
        kHasParentAgeFilename = 0x40
    };

protected:
    unsigned short fFlags;
    signed char fLinkingRules;
    unsigned char fAmCCR;
    plAgeInfoStruct fAgeInfo;
    plSpawnPointInfo fSpawnPoint;
    plString fParentAgeFilename;

public:
    plAgeLinkStruct();
    virtual ~plAgeLinkStruct();

    DECLARE_CREATABLE(plAgeLinkStruct)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    void UpdateFlags();
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
