#ifndef _PLDETECTCONDITIONALOBJECTS_H
#define _PLDETECTCONDITIONALOBJECTS_H

#include "plConditionalObject.h"

DllClass plLocalPlayerInBoxConditionalObject : public plConditionalObject {
protected:
    plKey fPlayer, fBox;

public:
    plLocalPlayerInBoxConditionalObject();
    virtual ~plLocalPlayerInBoxConditionalObject();

    DECLARE_CREATABLE(plLocalPlayerInBoxConditionalObject)
};

DllClass plLocalPlayerIntersectPlaneConditionalObject : public plConditionalObject {
protected:
    plKey fTarget, fPlane;

public:
    plLocalPlayerIntersectPlaneConditionalObject();
    virtual ~plLocalPlayerIntersectPlaneConditionalObject();

    DECLARE_CREATABLE(plLocalPlayerIntersectPlaneConditionalObject)
};

DllClass plObjectInBoxConditionalObject : public plConditionalObject {
protected:
    hsTArray<plKey> fInside;
    plKey fCurrentTrigger;

public:
    plObjectInBoxConditionalObject();
    virtual ~plObjectInBoxConditionalObject();

    DECLARE_CREATABLE(plObjectInBoxConditionalObject)
};

DllClass plObjectIntersectPlaneConditionalObject : public plConditionalObject {
protected:
    plKey fTarget, fPlane;

public:
    plObjectIntersectPlaneConditionalObject();
    virtual ~plObjectIntersectPlaneConditionalObject();

    DECLARE_CREATABLE(plObjectIntersectPlaneConditionalObject)
};

#endif
