#ifndef _PLROTCONTROLLER_H
#define _PLROTCONTROLLER_H

#include "plKeyControllers.hpp"

DllClass plRotController : public plController {
    CREATABLE(plRotController, kRotController, plController)

public:
    enum { kSimple = 1, kUnused, kCompound };

public:
    virtual int getType() const = 0;
};


DllClass plSimpleRotController : public plRotController {
    CREATABLE(plSimpleRotController, kSimpleRotController, plRotController)

protected:
    plQuatController* fRot;

public:
    plSimpleRotController();
    virtual ~plSimpleRotController();

    virtual int getType() const { return kSimple; }
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plQuatController* getRot() const { return fRot; }
    void setRot(plQuatController* rot);
};


DllClass plCompoundRotController : public plRotController {
    CREATABLE(plCompoundRotController, kCompoundRotController, plRotController)

protected:
    plScalarController* fXController;
    plScalarController* fYController;
    plScalarController* fZController;

public:
    plCompoundRotController();
    virtual ~plCompoundRotController();

    virtual int getType() const { return kCompound; }
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plScalarController* getX() const { return fXController; }
    plScalarController* getY() const { return fYController; }
    plScalarController* getZ() const { return fZController; }

    void setX(plScalarController* controller);
    void setY(plScalarController* controller);
    void setZ(plScalarController* controller);
};

#endif
