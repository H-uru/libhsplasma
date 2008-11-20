#ifndef _PLATCANIM_H
#define _PLATCANIM_H

#include "plAGAnim.h"

DllClass plATCAnim : public plAGAnim {
public:
    // These were originally std::maps, but are changed
    // to structs for performance:
    DllStruct MarkerMap {
        plString fKey;
        float fValue;
    };

    DllStruct LoopMap {
        plString fKey;
        float fStart, fEnd;
    };

protected:
    float fInitial, fLoopStart, fLoopEnd;
    bool fAutoStart, fLoop;
    unsigned char fEaseInType, fEaseOutType;
    float fEaseInLength, fEaseInMin, fEaseInMax;
    float fEaseOutLength, fEaseOutMin, fEaseOutMax;
    hsTArray<MarkerMap> fMarkers;
    hsTArray<LoopMap> fLoops;
    hsTArray<float> fStopPoints;

public:
    plATCAnim();
    virtual ~plATCAnim();

    DECLARE_CREATABLE(plATCAnim)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plEmoteAnim : public plATCAnim {
protected:
    plAGAnim::BodyUsage fBodyUsage;
    float fFadeIn, fFadeOut;

public:
    plEmoteAnim();
    virtual ~plEmoteAnim();

    DECLARE_CREATABLE(plEmoteAnim)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plAGAnimBink : public plATCAnim {
protected:
    plString fBinkFilename, fSgtFilename, fSubtitleId;

public:
    plAGAnimBink();
    virtual ~plAGAnimBink();

    DECLARE_CREATABLE(plAGAnimBink)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
