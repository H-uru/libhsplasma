#ifndef _PLDETECTCONDITIONALOBJECTS_H
#define _PLDETECTCONDITIONALOBJECTS_H

#include "plConditionalObject.h"

DllClass plLocalPlayerInBoxConditionalObject : public plConditionalObject {
    CREATABLE(plLocalPlayerInBoxConditionalObject,
              kLocalPlayerInBoxConditionalObject,
              plConditionalObject)
};

DllClass plLocalPlayerIntersectPlaneConditionalObject : public plConditionalObject {
    CREATABLE(plLocalPlayerIntersectPlaneConditionalObject,
              kLocalPlayerIntersectPlaneConditionalObject,
              plConditionalObject)
};

DllClass plObjectInBoxConditionalObject : public plConditionalObject {
    CREATABLE(plObjectInBoxConditionalObject,
              kObjectInBoxConditionalObject,
              plConditionalObject)
};

DllClass plObjectIntersectPlaneConditionalObject : public plConditionalObject {
    CREATABLE(plObjectIntersectPlaneConditionalObject,
              kObjectIntersectPlaneConditionalObject,
              plConditionalObject)
};

#endif
