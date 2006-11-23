#include "hsBounds.h"

/* hsBounds */
hsBounds::hsBounds() : Unknown(0) { }
hsBounds::~hsBounds() { }

void hsBounds::read(hsStream *S) {
    Unknown = S->readInt();
}

void hsBounds::write(hsStream *S) {
    S->writeInt(Unknown);
}


/* hsBounds3 */
hsBounds3::hsBounds3() { }
hsBounds3::~hsBounds3() { }

void hsBounds3::read(hsStream *S) {
    hsBounds::read(S);
    min.read(S);
    max.read(S);
}

void hsBounds3::write(hsStream *S) {
    hsBounds::write(S);
    min.write(S);
    max.write(S);
}


/* hsBounds3Ext */
hsBounds3Ext::hsBounds3Ext() : Flags(0) { }
hsBounds3Ext::~hsBounds3Ext() { }

void hsBounds3Ext::read(hsStream *S) {
    Flags = S->readInt();
    hsBounds3::read(S);
    if (Flags & 0x01) {
        ST34.read(S);
        for (int i=0; i<3; i++) {
            ST40[i].read(S);
            f64[2*i] = S->readFloat();
            f64[(2*i)+1] = S->readFloat();
        }
    }
}

void hsBounds3Ext::write(hsStream *S) {
    S->writeInt(Flags);
    hsBounds3::write(S);
    if (Flags & 0x01) {
        ST34.write(S);
        for (int i=0; i<3; i++) {
            ST40[i].write(S);
            S->writeFloat(f64[2*i]);
            S->writeFloat(f64[(2*i)+1]);
        }
    }
}

