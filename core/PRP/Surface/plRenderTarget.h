#ifndef _PLRENDERTARGET_H
#define _PLRENDERTARGET_H

#include "plBitmap.h"
#include "Math/hsGeometry3.h"
#include "Sys/hsColor.h"
#include "Math/hsMatrix44.h"
#include "Util/hsBitVector.h"

DllClass plRenderTarget : public plBitmap {
    CREATABLE(plRenderTarget, kRenderTarget, plBitmap)

protected:
    unsigned short fWidth, fHeight;
    union {
        struct {
            unsigned short fLeft, fTop, fRight, fBottom;
        } fAbsolute;
        struct {
            float fLeft, fTop, fRight, fBottom;
        } fProportional;
    } fViewport;
    bool fProportionalViewport;
    unsigned char fZDepth, fStencilDepth;

public:
    plRenderTarget();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    void readData(hsStream* S);
    void writeData(hsStream* S);

protected:
    void IRead(hsStream* S);
    void IWrite(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plCubicRenderTarget : public plRenderTarget {
    CREATABLE(plCubicRenderTarget, kCubicRenderTarget, plRenderTarget)

public:
    enum Faces {
        kLeftFace, kRightFace, kFrontFace, kBackFace, kTopFace, kBottomFace
    };

protected:
    plRenderTarget fFaces[6];

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plRenderTarget* getFace(size_t which) { return &fFaces[which]; }
};

#endif
