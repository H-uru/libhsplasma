#ifndef _PLRENDERTARGET_H
#define _PLRENDERTARGET_H

#include "PubUtilLib/plGImage/plBitmap.h"
#include "CoreLib/hsGeometry3.h"
#include "CoreLib/hsColor.h"
#include "CoreLib/hsMatrix44.h"
#include "CoreLib/hsBitVector.h"

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
    virtual void IPrcWrite(pfPrcHelper* prc);

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
    hsMatrix44 fWorldToCameras[6], fCameraToWorlds[6];

public:
    plCubicRenderTarget();
    virtual ~plCubicRenderTarget();

    DECLARE_CREATABLE(plCubicRenderTarget)

    virtual void readData(hsStream* S);
    virtual void writeData(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
};
#endif
