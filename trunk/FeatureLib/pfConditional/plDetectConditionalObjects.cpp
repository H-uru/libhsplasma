#include "plDetectConditionalObjects.h"

/* plLocalPlayerInBoxConditionalObject */
plLocalPlayerInBoxConditionalObject::plLocalPlayerInBoxConditionalObject() { }
plLocalPlayerInBoxConditionalObject::~plLocalPlayerInBoxConditionalObject() { }

IMPLEMENT_CREATABLE(plLocalPlayerInBoxConditionalObject,
                    kLocalPlayerInBoxConditionalObject,
                    plConditionalObject)


/* plLocalPlayerIntersectPlaneConditionalObject */
plLocalPlayerIntersectPlaneConditionalObject::plLocalPlayerIntersectPlaneConditionalObject() { }
plLocalPlayerIntersectPlaneConditionalObject::~plLocalPlayerIntersectPlaneConditionalObject() { }

IMPLEMENT_CREATABLE(plLocalPlayerIntersectPlaneConditionalObject,
                    kLocalPlayerIntersectPlaneConditionalObject,
                    plConditionalObject)


/* plObjectInBoxConditionalObject */
plObjectInBoxConditionalObject::plObjectInBoxConditionalObject() { }
plObjectInBoxConditionalObject::~plObjectInBoxConditionalObject() { }

IMPLEMENT_CREATABLE(plObjectInBoxConditionalObject,
                    kObjectInBoxConditionalObject,
                    plConditionalObject)


/* plObjectIntersectPlaneConditionalObject */
plObjectIntersectPlaneConditionalObject::plObjectIntersectPlaneConditionalObject() { }
plObjectIntersectPlaneConditionalObject::~plObjectIntersectPlaneConditionalObject() { }

IMPLEMENT_CREATABLE(plObjectIntersectPlaneConditionalObject,
                    kObjectIntersectPlaneConditionalObject,
                    plConditionalObject)
