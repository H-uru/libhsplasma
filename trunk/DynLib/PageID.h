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

    int getID();
    void setID(int pid);
    
    PlasmaVer getVer();
    void setVer(PlasmaVer pv, bool mutate = false);

    bool isGlobal();
    int getPageNum();
    int getSeqPrefix();
    void setPageNum(int pn);
    void setSeqPrefix(int sp);

    bool operator==(PageID& other);
    PageID& operator=(const PageID& other);

    const char* toString();

    void parse(unsigned int id);
    unsigned int unparse();
    void read(hsStream *S);
    void write(hsStream *S);

    void invalidate();
    bool isValid();
};

struct PageComparator {
    bool operator()(PageID pid1, PageID pid2) const;
};

#endif
