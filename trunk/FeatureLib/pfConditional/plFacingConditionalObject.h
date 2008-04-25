#ifndef _PLFACINGCONDITIONALOBJECT_H
#define _PLFACINGCONDITIONALOBJECT_H

#include "plConditionalObject.h"

DllClass plFacingConditionalObject : public plConditionalObject {
protected:
    float fTolerance;
    bool fDirectional;

public:
    plFacingConditionalObject();
    virtual ~plFacingConditionalObject();

    DECLARE_CREATABLE(plFacingConditionalObject)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
