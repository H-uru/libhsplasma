#ifndef _PLRENDERTARGET_H
#define _PLRENDERTARGET_H

#include "plBitmap.h"
#include "Math/hsGeometry3.h"
#include "Sys/hsColor.h"
#include "Math/hsMatrix44.h"
#include "Util/hsBitVector.h"

DllClass plRenderTarget : public plBitmap {
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
    bool fApplyTexQuality, fProportionalViewport;
    unsigned char fZDepth, fStencilDepth;
    class plCubicRenderTarget* fParent;

public:
    plRenderTarget();
    virtual ~plRenderTarget();

    DECLARE_CREATABLE(plRenderTarget)

    virtual void readData(hsStream* S);
    virtual void writeData(hsStream* S);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    class plCubicRenderTarget* getParent() const;
    void setParent(class plCubicRenderTarget* parent);
};

DllClass plCubicRenderTarget : public plRenderTarget {
public:
    enum Faces {
        kLeftFace, kRightFace, kFrontFace, kBackFace, kTopFace, kBottomFace
    };

protected:
    plRenderTarget* fFaces[6];

public:
    plCubicRenderTarget();
    virtual ~plCubicRenderTarget();

    DECLARE_CREATABLE(plCubicRenderTarget)

    virtual void readData(hsStream* S);
    virtual void writeData(hsStream* S);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};
#endif
