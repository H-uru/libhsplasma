#ifndef _PLUUID_H
#define _PLUUID_H

#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

DllClass plUUID {
protected:
    struct WinUUID {
        unsigned int Data1;
        unsigned short Data2, Data3;
        unsigned char Data4[8];
    };
    
    unsigned char fData[16];

public:
    plUUID();
    plUUID(const plUUID& init);
    plUUID(const char* str);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    void clear();
    bool isNull() const;
    plString toString() const;
    void fromString(const plString& str);
};

#endif
