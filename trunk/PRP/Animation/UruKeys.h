#ifndef _URUKEYS_H
#define _URUKEYS_H

#include "CoreLib/hsStream.h"
#include "CoreLib/hsMatrix33.h"
#include "CoreLib/hsMatrix44.h"
#include "PubUtilLib/plTransform/hsAffineParts.h"


DllStruct UruKeyFrame {
public:
    enum {
        kBezController = 0x2
    };

    unsigned int fFlags, fFrameNum;
    float fFrameTime;

public:
    UruKeyFrame();
    virtual ~UruKeyFrame();
    virtual const char* const ClassName()=0;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
    virtual void IPrcWrite(pfPrcHelper* prc)=0;
    virtual void IPrcParse(const pfPrcTag* tag)=0;
    virtual struct hsKeyFrame* toHsKey()=0;

};

DllStruct ScalarKeyFrame : public UruKeyFrame {
    float fInTan, fOutTan, fValue;

    ScalarKeyFrame();
    virtual ~ScalarKeyFrame();
    virtual const char* const ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);
    virtual struct hsKeyFrame* toHsKey();

};

DllStruct Point3KeyFrame : public UruKeyFrame {
    hsVector3 fInTan, fOutTan, fValue;

    Point3KeyFrame();
    virtual ~Point3KeyFrame();
    virtual const char* const ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);
    virtual struct hsKeyFrame* toHsKey();
};

DllStruct QuatKeyFrame : public UruKeyFrame {
    hsQuat fValue;

    QuatKeyFrame();
    virtual ~QuatKeyFrame();
    virtual const char* const ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);
    virtual struct hsKeyFrame* toHsKey();
};

DllStruct Matrix33KeyFrame : public UruKeyFrame {
    hsMatrix33 fValue;

    Matrix33KeyFrame();
    virtual ~Matrix33KeyFrame();
    virtual const char* const ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);
    virtual struct hsKeyFrame* toHsKey();
};

DllStruct Matrix44KeyFrame : public UruKeyFrame {
    hsMatrix44 fValue;

    Matrix44KeyFrame();
    virtual ~Matrix44KeyFrame();
    virtual const char* const ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);
    virtual struct hsKeyFrame* toHsKey();
};

DllStruct ScaleKeyFrame : public UruKeyFrame {
    hsVector3 fInTan, fOutTan;

    // I'm just folding ScaleValue and ScaleKey together here...
    hsVector3 fS;
    hsQuat fQ;

    ScaleKeyFrame();
    virtual ~ScaleKeyFrame();
    virtual const char* const ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);
    virtual struct hsKeyFrame* toHsKey();
};

#endif
