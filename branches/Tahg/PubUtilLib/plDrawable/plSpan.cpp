#include "plSpan.h"

plSpan::plSpan() : DrawableType(0), MatIndex(0), Flags(0), c98(0), i94(0),
                  s9A(0), s9C(0), s9E(0), Dist1(0.0f), Dist2(0.0f), f1B0(0.0f) {
    LocalToWorld = hsMatrix44::IdentityMatrix();
    WorldToLocal = hsMatrix44::IdentityMatrix();
}

plSpan::~plSpan() { }

void plSpan::read(hsStream *S) {
    DrawableType = S->readInt();
    MatIndex = S->readInt();
    LocalToWorld.Read(S);
    WorldToLocal.Read(S);
    Flags = S->readInt();
    bounds1.read(S);
    bounds2.read(S);
    c98 = S->readInt();
    i94 = S->readInt();
    s9A = S->readShort();
    s9C = S->readShort();
    s9E = S->readShort();
    Dist1 = S->readFloat();
    Dist2 = S->readFloat();
    if (Flags & 0x10)
        f1B0 = S->readFloat();
    else
        f1B0 = 0.0f;
}

void plSpan::write(hsStream *S) {
    S->writeInt(DrawableType);
    S->writeInt(MatIndex);
    LocalToWorld.Write(S);
    WorldToLocal.Write(S);
    S->writeInt(Flags);
    bounds1.write(S);
    bounds2.write(S);
    S->writeInt(c98);
    S->writeInt(i94);
    S->writeShort(s9A);
    S->writeShort(s9C);
    S->writeShort(s9E);
    S->writeFloat(Dist1);
    S->writeFloat(Dist2);
    if (Flags & 0x10)
        S->writeFloat(f1B0);
}

