#ifndef _HSKEYS_H
#define _HSKEYS_H

#include "CoreLib/hsStream.h"
#include "CoreLib/hsMatrix33.h"
#include "CoreLib/hsMatrix44.h"
#include "PubUtilLib/plTransform/hsAffineParts.h"

struct hsKeyFrame {
    enum {
        kUnknownKeyFrame, kPoint3KeyFrame, kBezPoint3KeyFrame, kScalarKeyFrame,
        kBezScalarKeyFrame, kScaleKeyFrame, kBezScaleKeyFrame, kQuatKeyFrame,
        kCompressedQuatKeyFrame32, kCompressedQuatKeyFrame64, k3dsMaxKeyFrame,
        kMatrix33KeyFrame, kMatrix44KeyFrame
    };
    static const char* TypeNames[];

    unsigned short fFrame;
    float fFrameTime;

    hsKeyFrame();
    virtual ~hsKeyFrame();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc)=0;
    virtual void prcParse(const pfPrcTag* tag)=0;
    virtual struct UruKeyFrame* toUruKey();
    virtual hsKeyFrame* toHsKey();
};

struct hsPoint3Key : public hsKeyFrame {
    hsVector3 fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual struct UruKeyFrame* toUruKey();
    virtual hsKeyFrame* toHsKey();
};

struct hsBezPoint3Key : public hsKeyFrame {
    hsVector3 fInTan, fOutTan, fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual struct UruKeyFrame* toUruKey();
    virtual hsKeyFrame* toHsKey();
};

struct hsScalarKey : public hsKeyFrame {
    float fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual hsKeyFrame* toHsKey();
};

struct hsBezScalarKey : public hsKeyFrame {
    float fInTan, fOutTan, fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual hsKeyFrame* toHsKey();
};

struct hsScaleValue : public hsKeyFrame {
    hsVector3 fS;
    hsQuat fQ;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual hsKeyFrame* toHsKey();
};

struct hsScaleKey : public hsKeyFrame {
    hsScaleValue fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual hsKeyFrame* toHsKey();
};

struct hsBezScaleKey : public hsKeyFrame {
    hsVector3 fInTan, fOutTan;
    hsScaleValue fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual hsKeyFrame* toHsKey();
};

struct hsQuatKey : public hsKeyFrame {
    hsQuat fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual struct UruKeyFrame* toUruKey();
    virtual hsKeyFrame* toHsKey();
};

struct hsCompressedQuatKey32 : public hsKeyFrame {
    unsigned int fData;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual struct UruKeyFrame* toUruKey();
    virtual hsKeyFrame* toHsKey();
};

struct hsCompressedQuatKey64 : public hsKeyFrame {
    unsigned int fData[2];

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual struct UruKeyFrame* toUruKey();
    virtual hsKeyFrame* toHsKey();
};

struct hsG3DSMaxKeyFrame : public hsKeyFrame {
    hsAffineParts fParts;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual struct UruKeyFrame* toUruKey();
    virtual hsKeyFrame* toHsKey();
};

struct hsMatrix33Key : public hsKeyFrame {
    hsMatrix33 fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual struct UruKeyFrame* toUruKey();
    virtual hsKeyFrame* toHsKey();
};

struct hsMatrix44Key : public hsKeyFrame {
    hsMatrix44 fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual struct UruKeyFrame* toUruKey();
    virtual hsKeyFrame* toHsKey();
};

#endif
