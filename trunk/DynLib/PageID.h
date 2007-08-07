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

    int getID() const;
    void setID(int pid);
    
    PlasmaVer getVer() const;
    void setVer(PlasmaVer pv, bool mutate = false);

    bool isGlobal() const;
    int getPageNum() const;
    int getSeqPrefix() const;
    void setPageNum(int pn);
    void setSeqPrefix(int sp);

    bool operator==(PageID& other) const;
    PageID& operator=(const PageID& other);

    char* toString() const;

    void parse(unsigned int id);
    unsigned int unparse() const;
    void read(hsStream* S);
    void write(hsStream* S);

    void invalidate();
    bool isValid() const;
};

struct PageComparator {
    bool operator()(PageID pid1, PageID pid2) const;
};

#endif
