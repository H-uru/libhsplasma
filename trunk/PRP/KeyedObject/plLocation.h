#ifndef _PLLOCATION_H
#define _PLLOCATION_H

#include "PlasmaDefs.h"
#include "Util/PlasmaVersions.h"
#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

DllClass PageID {
private:
    int seqPrefix, pageID;
    PlasmaVer ver;

public:
    PageID(PlasmaVer pv=pvUnknown);
    ~PageID();

    //int getID() const;
    //void setID(int pid);
    
    PlasmaVer getVer() const;
    void setVer(PlasmaVer pv);

    bool isGlobal() const;
    int getPageNum() const;
    int getSeqPrefix() const;
    void setPageNum(int pn);
    void setSeqPrefix(int sp);

    PageID& operator=(const PageID& other);
    bool operator==(const PageID& other) const;
    bool operator<(const PageID& other) const;

    plString toString() const;

    void parse(unsigned int id);
    unsigned int unparse() const;
    void read(hsStream* S);
    void write(hsStream* S);

    void invalidate();
    bool isValid() const;
};

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
    void prcParse(const pfPrcTag* tag);

    void invalidate();
    bool isValid() const;
    bool isReserved() const;
    bool isItinerant() const;
    bool isVirtual() const;

    const PageID& getPageID() const;
    unsigned short getFlags() const;

    plString toString() const;
};

#endif
