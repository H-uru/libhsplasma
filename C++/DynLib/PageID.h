#ifndef _PAGEID_H
#define _PAGEID_H

#include "PlasmaVersions.h"
#include "../CoreLib/hsStream.h"
#include "../hsRefCount.h"

class PageID : public hsRefCount {
private:
    int id;
    PlasmaVer ver;

public:
    PageID();
    PageID(int pid, PlasmaVer pv=pvUnknown);
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

    bool operator==(PageID &other);

    void read(hsStream *S);
    void write(hsStream *S);
};

#endif
