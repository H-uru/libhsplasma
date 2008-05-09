#ifndef _PLSDL_H
#define _PLSDL_H

#include "NucleusLib/pnFactory/plCreatable.h"

namespace plSDL {
    enum ContentsFlags {
        kHasUoid = 0x1,
        kHasNotificationInfo = 0x2,
        kHasTimeStamp = 0x4,
        kSameAsDefault = 0x8,
        kHasDirtyFlag = 0x10,
        kWantTimeStamp = 0x20
    };

    unsigned int VariableLengthRead(hsStream* S, size_t size);
    void VariableLengthWrite(hsStream* S, size_t size, unsigned int value);
};

DllClass plSDLCreatableStub : public plCreatable {
protected:
    short fClassIdx;
    unsigned char* fData;
    size_t fDataLen;

public:
    plSDLCreatableStub();
    plSDLCreatableStub(short hClass, size_t length);
    virtual ~plSDLCreatableStub();

    virtual short ClassIndex() const;

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

    short getClassIdx() const;
    unsigned char* getData() const;
    size_t getLength() const;
};

#endif
