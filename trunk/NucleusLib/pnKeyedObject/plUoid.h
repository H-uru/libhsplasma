#ifndef _PLUOID_H
#define _PLUOID_H

#include "../../CoreLib/hsStream.h"
#include "../../CoreLib/plLoadMask.h"
#include "../../DynLib/PageID.h"
#include "../../FeatureLib/pfPRC/pfPrcHelper.h"

DllClass plLocation {
public:
    enum LocFlags {
        kLocalOnly = 0x1,
        kVolatile = 0x2,
        kReserved = 0x4,
        kBuiltIn = 0x8,
        kItinerant = 0x10
    };

public:
    PageID pageID;
    unsigned short flags;

public:
    plLocation();
    ~plLocation();

    bool operator==(plLocation& other);
    plLocation& operator=(plLocation& other);

    int getPageNum();
    int getSeqPrefix();
    void set(int, int, PlasmaVer);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);

    void invalidate();
    bool isValid();
    bool isReserved();
    bool isItinerant();
    bool isVirtual();

    const char* toString();
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
    unsigned short classType;
    char* objName;
    unsigned int objID, clonePlayerID, cloneID;
    unsigned char eoaExtra;

public:
    plUoid();
    ~plUoid();

    bool operator==(plUoid& other);
    plUoid& operator=(plUoid& other);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);

    const char* toString();

    short getType();
    PageID& getPageID();
    const char* getName();
    void setID(unsigned int id);
};

#endif

