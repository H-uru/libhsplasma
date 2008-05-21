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
    virtual struct UruKeyFrame* toUruKey()=0;
};

struct hsPoint3Key : public hsKeyFrame {
    hsVector3 fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual struct UruKeyFrame* toUruKey();
};

struct hsBezPoint3Key : public hsKeyFrame {
    hsVector3 fInTan, fOutTan, fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual struct UruKeyFrame* toUruKey();
};

struct hsScalarKey : public hsKeyFrame {
    float fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual struct UruKeyFrame* toUruKey();
};

struct hsBezScalarKey : public hsKeyFrame {
    float fInTan, fOutTan, fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual struct UruKeyFrame* toUruKey();
};

struct hsScaleKey : public hsKeyFrame {
    // Folding hsScaleKey and hsScaleValue together:
    hsVector3 fS;
    hsQuat fQ;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual struct UruKeyFrame* toUruKey();
};

struct hsBezScaleKey : public hsKeyFrame {
    hsVector3 fInTan, fOutTan;
    hsVector3 fS;
    hsQuat fQ;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual struct UruKeyFrame* toUruKey();
};

struct hsQuatKey : public hsKeyFrame {
    hsQuat fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual struct UruKeyFrame* toUruKey();
};

struct hsCompressedQuatKey32 : public hsKeyFrame {
    enum { kCompQuatNukeX, kCompQuatNukeY, kCompQuatNukeZ, kCompQuatNukeW };
    static const float kOneOverRootTwo, k10BitScaleRange;

    unsigned int fData;

    hsQuat getQuat();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual struct UruKeyFrame* toUruKey();
};

struct hsCompressedQuatKey64 : public hsKeyFrame {
    enum { kCompQuatNukeX, kCompQuatNukeY, kCompQuatNukeZ, kCompQuatNukeW };
    static const float kOneOverRootTwo, k20BitScaleRange, k21BitScaleRange;

    unsigned int fData[2];

    hsQuat getQuat();
    
    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual struct UruKeyFrame* toUruKey();
};

struct hsG3DSMaxKeyFrame : public hsKeyFrame {
    hsAffineParts fParts;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual struct UruKeyFrame* toUruKey();
};

struct hsMatrix33Key : public hsKeyFrame {
    hsMatrix33 fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual struct UruKeyFrame* toUruKey();
};

struct hsMatrix44Key : public hsKeyFrame {
    hsMatrix44 fValue;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    virtual void prcParse(const pfPrcTag* tag);
    virtual struct UruKeyFrame* toUruKey();
};

#endif
