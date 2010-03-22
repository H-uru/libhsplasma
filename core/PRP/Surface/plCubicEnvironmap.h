#ifndef _PLCUBICENVIRONMAP_H
#define _PLCUBICENVIRONMAP_H

#include "plMipmap.h"

DllClass plCubicEnvironmap : public plBitmap {
public:
    enum Faces { kLeftFace, kRightFace, kFrontFace, kBackFace,
                 kTopFace, kBottomFace, kNumFaces };

    static const char* kFaceNames[kNumFaces];

protected:
    plMipmap fFaces[kNumFaces];

public:
    plCubicEnvironmap();
    virtual ~plCubicEnvironmap();

    DECLARE_CREATABLE(plCubicEnvironmap)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plMipmap* getFace(size_t idx);
};

#endif
