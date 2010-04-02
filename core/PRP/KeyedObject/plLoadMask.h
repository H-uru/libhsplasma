#ifndef _PLLOADMASK_H
#define _PLLOADMASK_H

#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

DllClass plLoadMask {
protected:
    union {
        unsigned char fQuality[2];
        unsigned short fMask;
    };

public:
    plLoadMask();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    bool isUsed() { return (fMask != 0xFFFF); }
    void setQuality(unsigned char low, unsigned char high);
    void setMask(unsigned short mask) { fMask = mask; }
    void setAlways() { fMask = 0xFFFF; }
    unsigned short getMask() const { return fMask; }
    unsigned char getQuality(size_t which) const { return fQuality[which]; }
};

#endif
