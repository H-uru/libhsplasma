#ifndef _PLPOSCONTROLLER_H
#define _PLPOSCONTROLLER_H

#include "plKeyControllers.hpp"

DllClass plPosController : public plController {
    CREATABLE(plPosController, kPosController, plController)

public:
    enum { kSimple = 1, kCompound };

public:
    virtual int getType() const = 0;
};


DllClass plSimplePosController : public plPosController {
    CREATABLE(plSimplePosController, kSimplePosController, plPosController)

protected:
    plPoint3Controller* fPosition;

public:
    plSimplePosController();
    virtual ~plSimplePosController();

    virtual int getType() const { return kSimple; }
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plPoint3Controller* getPosition() const { return fPosition; }
    void setPosition(plPoint3Controller* pos);
};


DllClass plCompoundPosController : public plPosController {
    CREATABLE(plCompoundPosController, kCompoundPosController, plPosController)

protected:
    plScalarController* fXController;
    plScalarController* fYController;
    plScalarController* fZController;

public:
    plCompoundPosController();
    virtual ~plCompoundPosController();

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
