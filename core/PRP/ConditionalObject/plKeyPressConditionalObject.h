#ifndef _PLKEYPRESSCONDITIONALOBJECT_H
#define _PLKEYPRESSCONDITIONALOBJECT_H

#include "plConditionalObject.h"
#include "Sys/Platform.h"

DllClass plKeyPressConditionalObject : public plConditionalObject {
protected:
    plKeyDef fKeyEvent;

public:
    plKeyPressConditionalObject();
    virtual ~plKeyPressConditionalObject();

    DECLARE_CREATABLE(plKeyPressConditionalObject)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
