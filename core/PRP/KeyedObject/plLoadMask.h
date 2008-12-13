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
    ~plLoadMask();
    
    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    bool isUsed();
    void setQuality(unsigned char low, unsigned char high);
    void setMask(unsigned short mask);
    void setAlways();
    unsigned short getMask() const;
    unsigned char getQuality(size_t which) const;
};

#endif
