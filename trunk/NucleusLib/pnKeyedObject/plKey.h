#ifndef _PLKEY_H
#define _PLKEY_H

#include "../../CoreLib/hsStream.h"
#include "../../DynLib/PageID.h"
#include "../../CoreLib/hsRefCnt.h"

class plKey : public hsRefCnt {
public:
    enum PageTypes {
        kPageNormal = 0x0, kPageGlobal = 0x4, kPageAgeGlobal = 0x8
    };

public:
    char flags;
    PageID pageID;
    short pageType;
    char extra1;
    short objType;
    int objID;
    char* objName;
    int someID, clientID;
    char eoaExtra2;
    class hsKeyedObject* objPtr;

    bool exists;
    
    unsigned int fileOff;
    unsigned int objSize;

public:
    plKey();
    plKey(plKey * init);
    ~plKey();

    bool operator==(plKey &other);

    const char* toString();
    
    /*
    void read(hsStream *S);
    void write(hsStream *S);
    
    void readRef(hsStream *S);
    void writeRef(hsStream *S);
    */
};

#endif
