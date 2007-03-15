#ifndef _PLKEY_H
#define _PLKEY_H

#include "../../CoreLib/hsStream.h"
#include "../../CoreLib/hsRefCnt.h"
#include "plUoid.h"

DllClass plKey : public hsRefCnt {
public:
    plUoid uoid;
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
    
    void read(hsStream* S);
    void write(hsStream* S);
    void readUoid(hsStream* S);
    void writeUoid(hsStream* S);

    short getType();
    PageID& getPageID();
    const char* getName();
    void setID(unsigned int id);
};

#endif
