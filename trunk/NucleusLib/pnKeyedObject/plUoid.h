#ifndef _PLUOID_H
#define _PLUOID_H

#include "CoreLib/hsStream.h"
#include "CoreLib/plLoadMask.h"
#include "CoreLib/plString.h"
#include "DynLib/PageID.h"
#include "FeatureLib/pfPRC/pfPrcHelper.h"

DllClass plLocation {
public:
    enum LocFlags {
        kLocalOnly = 0x1,
        kVolatile = 0x2,
        kReserved = 0x4,
        kBuiltIn = 0x8,
        kItinerant = 0x10
    };

protected:
    PageID pageID;
    unsigned short flags;

public:
    plLocation();
    ~plLocation();

    plLocation& operator=(const plLocation& other);
    bool operator==(const plLocation& other) const;
    bool operator<(const plLocation& other) const;

    int getPageNum() const;
    int getSeqPrefix() const;
    void set(int pid, int lflags, PlasmaVer pv);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);

    void invalidate();
    bool isValid() const;
    bool isReserved() const;
    bool isItinerant() const;
    bool isVirtual() const;

    const PageID& getPageID() const;
    unsigned short getFlags() const;

    plString toString() const;
};

DllClass plUoid {
public:
    enum ContentsFlags {
        kHasCloneIDs = 0x1,
        kHasLoadMask = 0x2
    };

protected:
    plLocation location;
    plLoadMask loadMask;
    short classType;
    plString objName;
    unsigned int objID, clonePlayerID, cloneID;
    unsigned char eoaExtra;

public:
    plUoid();
    ~plUoid();

    plUoid& operator=(const plUoid& other);
    bool operator==(const plUoid& other) const;
    bool operator<(const plUoid& other) const;

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);

    plString toString() const;

    short getType() const;
    const plString& getName() const;
    const plLocation& getLocation() const;
    const PageID& getPageID() const;
    void setID(unsigned int id);
    unsigned int getID() const;
};

#endif

