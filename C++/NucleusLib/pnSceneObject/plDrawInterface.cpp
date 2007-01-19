#include "plDrawInterface.h"

/*plDrawableKeyRef */
plDrawableKey::plDrawableKey() : DrawKey(0) { }
plDrawableKey::~plDrawableKey() { }

void plDrawableKey::read(hsStream *S) {
    DrawKey = S->readInt();
    plKey::read(S);
}

void plDrawableKey::write(hsStream *S) {
    S->writeInt(DrawKey);
    plKey::write(S);
}

void plDrawableKey::readRef(hsStream *S) {
    S->writeInt(DrawKey);
    plKey::readRef(S);
}

void plDrawableKey::writeRef(hsStream *S) {
    S->writeInt(DrawKey);
    plKey::writeRef(S);
}


/* plDrawInterface */

plDrawInterface::plDrawInterface(PlasmaVer pv) { }
plDrawInterface::~plDrawInterface() { }

void plDrawInterface::read(hsStream *S) {
    plObjInterface::read(S);
    int count = S->readInt();
    Drawables.clear();
    Drawables.setSize(count);
    for (int i=0; i<count; i++)
        Drawables[i].readRef(S);
    count = S->readInt();
    Objects.clear();
    Objects.setSize(count);
    for (int i=0; i<count; i++)
        Objects[i].readRef(S);
}

void plDrawInterface::write(hsStream *S) {
    plObjInterface::write(S);
    S->writeInt(Drawables.getSize());
    for (int i=0; i<Drawables.getSize(); i++)
        Drawables[i].writeRef(S);
    S->writeInt(Objects.getSize());
    for (int i=0; i<Objects.getSize(); i++)
        Objects[i].writeRef(S);
}

