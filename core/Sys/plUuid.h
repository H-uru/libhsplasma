#ifndef _PLUUID_H
#define _PLUUID_H

#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

DllStruct plUuid {
protected:
    unsigned int fData1;
    unsigned short fData2, fData3;
    unsigned char fData4[8];

public:
    plUuid();
    plUuid(unsigned int data1, unsigned short data2, unsigned short data3,
           const unsigned char* data4);
    plUuid(const plUuid& init);
    plUuid(const char* str);

    plUuid& operator=(const plUuid& init);
    bool operator==(const plUuid& other) const;
    bool operator!=(const plUuid& other) const;

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    void clear();
    bool isNull() const;
    plString toString() const;
    void fromString(const plString& str);
};

extern const plUuid NullUuid;

#endif
