#ifndef _PLVOLUMESENSORCONDITIONALOBJECT_H
#define _PLVOLUMESENSORCONDITIONALOBJECT_H

#include "plConditionalObject.h"

DllClass plVolumeSensorConditionalObject : public plConditionalObject {
public:
    enum { kTypeEnter = 0x1, kTypeExit = 0x2 };

protected:
    hsTArray<plKey> fInside;
    int fTrigNum, fType;
    bool fFirst, fTriggered, fIgnoreExtraEnters;

public:
    plVolumeSensorConditionalObject();
    virtual ~plVolumeSensorConditionalObject();

    DECLARE_CREATABLE(plVolumeSensorConditionalObject)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
