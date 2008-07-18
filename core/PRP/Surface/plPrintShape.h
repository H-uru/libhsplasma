#ifndef _PLPRINTSHAPE_H
#define _PLPRINTSHAPE_H

#include "PRP/Object/plObjInterface.h"

DllClass plPrintShape : public plObjInterface {
protected:
    float fWidth, fLength, fHeight;

public:
    plPrintShape();
    virtual ~plPrintShape();

    DECLARE_CREATABLE(plPrintShape)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plActivePrintShape : public plPrintShape {
protected:
    hsTArray<plKey> fDecalMgrs;

public:
    plActivePrintShape();
    virtual ~plActivePrintShape();

    DECLARE_CREATABLE(plActivePrintShape)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
