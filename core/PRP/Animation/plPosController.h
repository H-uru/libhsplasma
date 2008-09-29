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

    virtual int getType() const;
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
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
    virtual int getType() const;

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
