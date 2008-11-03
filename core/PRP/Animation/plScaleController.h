#ifndef _PLSCALECONTROLLER_H
#define _PLSCALECONTROLLER_H

#include "plKeyControllers.h"

DllClass plScaleController : public plController {
public:
    enum { kSimple = 1 };

public:
    DECLARE_CREATABLE(plScaleController)

    virtual int getType() const =0;
};

DllClass plSimpleScaleController : public plScaleController {
protected:
    plScaleValueController* fValue;

public:
    plSimpleScaleController();
    virtual ~plSimpleScaleController();

    DECLARE_CREATABLE(plSimpleScaleController)

    virtual int getType() const;
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plScaleValueController* getValue() const;
    void setValue(plScaleValueController* value);
};

#endif
