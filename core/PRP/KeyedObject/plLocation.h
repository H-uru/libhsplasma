#ifndef _PLLOCATION_H
#define _PLLOCATION_H

#include "PlasmaDefs.h"
#include "Util/PlasmaVersions.h"
#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

DllClass plLocation {
public:
    enum LocFlags {
        kLocalOnly = 0x1,
        kVolatile = 0x2,
        kReserved = 0x4,
        kBuiltIn = 0x8,
        kItinerant = 0x10
    };

    enum LocState {
        kStateInvalid, kStateNormal, kStateVirtual
    };

protected:
    PlasmaVer fVer;
    int fState;
    int fSeqPrefix, fPageNum;
    unsigned short fFlags;

public:
    plLocation(PlasmaVer pv=pvUnknown);
    plLocation(const plLocation& init);
    ~plLocation();

    PlasmaVer getVer() const;
    void setVer(PlasmaVer pv);

    plLocation& operator=(const plLocation& other);
    bool operator==(const plLocation& other) const;
    bool operator!=(const plLocation& other) const;
    bool operator<(const plLocation& other) const;

    void parse(unsigned int id);
    unsigned int unparse() const;

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    void invalidate();
    bool isValid() const;

    bool isReserved() const;
    bool isItinerant() const;
    bool isVirtual() const;
    bool isGlobal() const;
    void setVirtual();

    int getPageNum() const;
    int getSeqPrefix() const;
    unsigned short getFlags() const;
    void setPageNum(int pn);
    void setSeqPrefix(int sp);
    void setFlags(unsigned short flags);
    void set(int pid, unsigned short flags, PlasmaVer pv);

    plString toString() const;
};

#endif
