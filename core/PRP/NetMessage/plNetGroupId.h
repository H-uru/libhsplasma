#ifndef _PLNETGROUPID_H
#define _PLNETGROUPID_H

#include "PRP/KeyedObject/plLocation.h"

DllClass plNetGroupId {
public:
    enum {
        kNetGroupConstant = 0x01,
        kNetGroupLocal = 0x02,
    };

private:
    plLocation fID;
    unsigned char fFlags;

public:
    plNetGroupId();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    plLocation getID() const { return fID; }
    unsigned char getFlags() const { return fFlags; }

    void setID(const plLocation& loc) { fID = loc; }
    void setFlags(unsigned char flags) { fFlags = flags; }
};

#endif
