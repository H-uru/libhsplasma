#ifndef _PLSCALECONTROLLER_H
#define _PLSCALECONTROLLER_H

#include "plKeyControllers.hpp"

DllClass plScaleController : public plController {
    CREATABLE(plScaleController, kScaleController, plController)

public:
    enum { kSimple = 1 };

public:
    virtual int getType() const = 0;
};


DllClass plSimpleScaleController : public plScaleController {
    CREATABLE(plSimpleScaleController, kSimpleScaleController, plScaleController)

protected:
    plScaleValueController* fValue;

public:
    plSimpleScaleController();
    virtual ~plSimpleScaleController();

    virtual int getType() const { return kSimple; }
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plScaleValueController* getValue() const { return fValue; }
    void setValue(plScaleValueController* value);
};

#endif
