#ifndef _PLPRINTSHAPE_H
#define _PLPRINTSHAPE_H

#include "PRP/Object/plObjInterface.h"

DllClass plPrintShape : public plObjInterface {
    CREATABLE(plPrintShape, kPrintShape, plObjInterface)

protected:
    float fWidth, fLength, fHeight;

public:
    plPrintShape();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plActivePrintShape : public plPrintShape {
    CREATABLE(plActivePrintShape, kActivePrintShape, plPrintShape)

protected:
    hsTArray<plKey> fDecalMgrs;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
