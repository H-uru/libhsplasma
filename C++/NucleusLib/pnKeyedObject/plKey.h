#ifndef _PLKEY_H
#define _PLKEY_H

#include "../../CoreLib/hsStream.h"
#include "../../DynLib/PageID.h"
#include "../../CoreLib/hsRefCnt.h"

class plKey : public hsRefCnt {
protected:
    char flags;
    PageID * pageID;
    short pageType;
    char extra1;
    short objType;
    int objID;
    char* objName;
    int someID, clientID;
    char eoaExtra2;

public:
    bool exists;

    plKey();
    plKey(plKey * init);
    ~plKey();

    PageID * getPageID();
    short getPageType();
    short getObjType();
    int getObjID();
    char* getObjName();
    
    void setPageID(PageID * pid);
    void setPageType(short pt);
    void setObjType(short ot);
    void setObjID(int id);
    void setObjName(const char* name);

    bool operator==(plKey &other);

    void read(hsStream *S);
    void write(hsStream *S);
    
    void readRef(hsStream *S);
    void writeRef(hsStream *S);
};

#endif
