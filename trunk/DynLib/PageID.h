#ifndef _PAGEID_H
#define _PAGEID_H

#include "../PlasmaDefs.h"
#include "PlasmaVersions.h"
#include "../CoreLib/hsStream.h"

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

#endif
