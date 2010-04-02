#ifndef _PLNETSERVERSESSIONINFO_H
#define _PLNETSERVERSESSIONINFO_H

#include "PRP/plCreatable.h"
#include "Sys/plUuid.h"
#include "plSpawnPointInfo.h"

DllClass plAgeInfoStruct : public plCreatable {
    CREATABLE(plAgeInfoStruct, kAgeInfoStruct, plCreatable)

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
    plUuid fAgeInstanceGuid;
    plString fAgeUserDefinedName, fAgeDescription;
    int fAgeSequenceNumber, fAgeLanguage;
    plString fDisplayName;

public:
    plAgeInfoStruct();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcParse(const pfPrcTag* tag, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool isEmpty() { return (fFlags == 0); }
    void clear() { fFlags = 0; }

    const plString& getAgeFilename() const { return fAgeFilename; }
    const plString& getAgeInstanceName() const { return fAgeInstanceName; }

    void setAgeFilename(const plString& name);
    void setAgeInstanceName(const plString& name);
};


DllClass plAgeLinkStruct : public plCreatable {
    CREATABLE(plAgeLinkStruct, kAgeLinkStruct, plCreatable)

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

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcParse(const pfPrcTag* tag, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    void clear();
};


DllClass plAgeLinkEffects {
protected:
    plString fLinkInAnimName;
    bool fBool1, fBool2, fBool3, fBool4;

public:
    plAgeLinkEffects();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

#endif
