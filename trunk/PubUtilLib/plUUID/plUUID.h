#ifndef _PLUUID_H
#define _PLUUID_H

#include "CoreLib/hsStream.h"
#include "FeatureLib/pfPRC/pfPrcHelper.h"

DllClass plUUID {
protected:
    unsigned char fData[16];

public:
    plUUID();
    plUUID(const plUUID& init);
    //plUUID(const Uuid& init);
    //plUUID(const char* str);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);

    void clear();
    plString toString() const;
    bool isNull() const;
};

#endif
