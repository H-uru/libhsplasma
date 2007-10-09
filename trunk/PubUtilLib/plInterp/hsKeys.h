#ifndef _HSKEYS_H
#define _HSKEYS_H

#include "../../CoreLib/hsStream.h"
#include "../../CoreLib/hsMatrix33.h"
#include "../../CoreLib/hsMatrix44.h"
#include "../plTransform/hsAffineParts.h"

struct hsKeyFrame {
    enum {
        kUnknownKeyFrame, kPoint3KeyFrame, kBezPoint3KeyFrame, kScalarKeyFrame,
        kBezScalarKeyFrame, kScaleKeyFrame, kBezScaleKeyFrame, kQuatKeyFrame,
        kCompressedQuatKeyFrame32, kCompressedQuatKeyFrame64, k3dsMaxKeyFrame,
        kMatrix33KeyFrame, kMatrix44KeyFrame
    };

    unsigned short fFrame;

    hsKeyFrame();
    virtual ~hsKeyFrame();

    virtual void read(hsStream* S)=0;
    virtual void write(hsStream* S)=0;
    virtual void prcWrite(pfPrcHelper* prc)=0;
};

struct hsPoint3Key : public hsKeyFrame {
    hsPoint3 fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

struct hsBezPoint3Key : public hsKeyFrame {
    hsPoint3 fInTan, fOutTan, fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

struct hsScalarKey : public hsKeyFrame {
    float fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

struct hsBezScalarKey : public hsKeyFrame {
    float fInTan, fOutTan, fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

struct hsScaleValue : public hsKeyFrame {
    hsVector3 fS;
    hsQuat fQ;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

struct hsScaleKey : public hsKeyFrame {
    hsScaleValue fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

struct hsBezScaleKey : public hsKeyFrame {
    hsPoint3 fInTan, fOutTan;
    hsScaleValue fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

struct hsQuatKey : public hsKeyFrame {
    hsQuat fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

struct hsCompressedQuatKey32 : public hsKeyFrame {
    unsigned int fData;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

struct hsCompressedQuatKey64 : public hsKeyFrame {
    unsigned int fData[2];

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

struct hsG3DSMaxKeyFrame : public hsKeyFrame {
    hsAffineParts fParts;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

struct hsMatrix33Key : public hsKeyFrame {
    hsMatrix33 fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

struct hsMatrix44Key : public hsKeyFrame {
    hsMatrix44 fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
