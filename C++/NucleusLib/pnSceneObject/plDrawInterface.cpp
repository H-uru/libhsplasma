#include "plDrawInterface.h"

/*plDrawableKeyRef */
plDrawableKeyRef::plDrawableKeyRef() : DrawKey(0) { }
plDrawableKeyRef::~plDrawableKeyRef() { }

void plDrawableKeyRef::read(hsStream *S) {
    DrawKey = S->readInt();
    plKeyRef::read(S);
}

void plDrawableKeyRef::write(hsStream *S) {
    S->writeInt(DrawKey);
    plKeyRef::write(S);
}


/* plDrawInterface */

plDrawInterface::plDrawInterface(PlasmaVer pv) { }
plDrawInterface::~plDrawInterface() { }

void plDrawInterface::read(hsStream *S) {
    plObjInterface::read(S);
    Drawables.read(S);
    Objects.read(S);
}

void plDrawInterface::write(hsStream *S) {
    plObjInterface::write(S);
    Drawables.write(S);
    Objects.write(S);
}

