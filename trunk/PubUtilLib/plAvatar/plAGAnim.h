#ifndef _PLAGANIM_H
#define _PLAGANIM_H

#include "NucleusLib/pnNetCommon/plSynchedObject.h"
#include "plAGApplicator.h"

DllClass plAGAnim : public plSynchedObject {
public:
    enum BodyUsage {
        kBodyUnknown, kBodyUpper, kBodyFull, kBodyLower, kBodyMax
    };

protected:
    hsTArray<plAGApplicator*> fApps;
    float fBlend, fStart, fEnd;
    plString fName;

public:
    plAGAnim();
    virtual ~plAGAnim();

    DECLARE_CREATABLE(plAGAnim)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plAgeGlobalAnim : public plAGAnim {
protected:
    plString fGlobalVarName;

public:
    plAgeGlobalAnim();
    virtual ~plAgeGlobalAnim();

    DECLARE_CREATABLE(plAgeGlobalAnim)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plATCAnim : public plAGAnim {
public:
    // These were originally std::maps, but are changed
    // to structs for performance:
    DllStruct MarkerMap {
        plString key;
        float value;
    };

    DllStruct LoopMap {
        plString key;
        float start, end;
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
    virtual void prcWrite(pfPrcHelper* prc);
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
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
