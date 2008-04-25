#ifndef _PLDETECTCONDITIONALOBJECTS_H
#define _PLDETECTCONDITIONALOBJECTS_H

#include "plConditionalObject.h"

DllClass plLocalPlayerInBoxConditionalObject : public plConditionalObject {
public:
    plLocalPlayerInBoxConditionalObject();
    virtual ~plLocalPlayerInBoxConditionalObject();

    DECLARE_CREATABLE(plLocalPlayerInBoxConditionalObject)
};

DllClass plLocalPlayerIntersectPlaneConditionalObject : public plConditionalObject {
public:
    plLocalPlayerIntersectPlaneConditionalObject();
    virtual ~plLocalPlayerIntersectPlaneConditionalObject();

    DECLARE_CREATABLE(plLocalPlayerIntersectPlaneConditionalObject)
};

DllClass plObjectInBoxConditionalObject : public plConditionalObject {
public:
    plObjectInBoxConditionalObject();
    virtual ~plObjectInBoxConditionalObject();

    DECLARE_CREATABLE(plObjectInBoxConditionalObject)
};

DllClass plObjectIntersectPlaneConditionalObject : public plConditionalObject {
public:
    plObjectIntersectPlaneConditionalObject();
    virtual ~plObjectIntersectPlaneConditionalObject();

    DECLARE_CREATABLE(plObjectIntersectPlaneConditionalObject)
};

#endif
