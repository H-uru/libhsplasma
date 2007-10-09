#ifndef _PLPOSCONTROLLER_H
#define _PLPOSCONTROLLER_H

#include "plKeyControllers.h"

DllClass plPosController : public plController {
public:
    enum { kSimple = 1, kCompound };

public:
    DECLARE_CREATABLE(plPosController)

    virtual int getType() const =0;
};

DllClass plSimplePosController : public plPosController {
protected:
    plPoint3Controller* fPosition;

public:
    plSimplePosController();
    virtual ~plSimplePosController();

    DECLARE_CREATABLE(plSimplePosController)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual int getType() const;
};

DllClass plCompoundPosController : public plPosController {
protected:
    plScalarController* fXController;
    plScalarController* fYController;
    plScalarController* fZController;

public:
    plCompoundPosController();
    virtual ~plCompoundPosController();

    DECLARE_CREATABLE(plCompoundPosController)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual int getType() const;
};

#endif
