#ifndef _PLCUBICENVIRONMAP_H
#define _PLCUBICENVIRONMAP_H

#include "plMipmap.h"

class plCubicEnvironmap : public plBitmap {
public:
    enum Faces { kLeftFace, kRightFace, kFrontFace, kBackFace,
                 kTopFace, kBottomFace, kNumFaces };

protected:
    plMipmap fFaces[kNumFaces];

public:
    plCubicEnvironmap();
    virtual ~plCubicEnvironmap();
    
    DECLARE_CREATABLE(plCubicEnvironmap)

    virtual void readData(hsStream* S);
    virtual void writeData(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
