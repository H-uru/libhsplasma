#ifndef _PLROTCONTROLLER_H
#define _PLROTCONTROLLER_H

#include "plKeyControllers.h"

DllClass plRotController : public plController {
public:
    enum { kSimple = 1, kUnused, kCompound };

public:
    DECLARE_CREATABLE(plRotController)

    virtual int getType() const =0;
};

DllClass plSimpleRotController : public plRotController {
protected:
    plQuatController* fRot;

public:
    plSimpleRotController();
    virtual ~plSimpleRotController();

    DECLARE_CREATABLE(plSimpleRotController)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
    virtual int getType() const;
};

DllClass plCompoundRotController : public plRotController {
protected:
    plScalarController* fXController;
    plScalarController* fYController;
    plScalarController* fZController;

public:
    plCompoundRotController();
    virtual ~plCompoundRotController();

    DECLARE_CREATABLE(plCompoundRotController)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
    virtual int getType() const;
};

#endif
