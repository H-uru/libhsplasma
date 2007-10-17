#ifndef _PLSOUND_H
#define _PLSOUND_H

#include "../plResMgr/plResManager.h"
#include "../../NucleusLib/pnNetCommon/plSynchedObject.h"
#include "../../NucleusLib/pnSceneObject/plSceneObject.h"
#include "../../CoreLib/hsGeometry3.h"
#include "plEAXEffects.h"

DllClass plSound : public plSynchedObject {
public:
    enum Property {
        kPropIs3DSound = 0x1,
        kPropDisableLOD = 0x2,
        kPropLooping = 0x4,
        kPropAutoStart = 0x8,
        kPropLocalOnly = 0x10,
        kPropLoadOnlyOnCall = 0x20,
        kPropFullyDisabled = 0x40,
        kPropDontFade = 0x80,
        kPropIncidental = 0x100
    };

    enum Type {
        kStartType = 0,
        kSoundFX = kStartType, kAmbience, kBackgroundMusic, kGUISound,
        kNPCVoices, kNumTypes
    };

    enum StreamType {
        kNoStream, kStreamFromRAM, kStreamFromDisk, kStreamCompressed
    };

public:
    DllClass plFadeParams {
    public:
        enum Type { kLinear, kLogarithmic, kExponential };

        float fLengthInSecs, fVolStart, fVolEnd;
        unsigned char fType;
        bool fStopWhenDone, fFadeSoftVol;
        float fCurrTime;

    public:
        plFadeParams();

        void read(hsStream* S);
        void write(hsStream* S);
        void prcWrite(pfPrcHelper* prc);
    };

protected:
    bool fPlaying, fActive;
    double fTime;
    int fMaxFalloff, fMinFalloff;
    float fCurrVolume;
    int fOuterVol, fInnerCone, fOuterCone;
    double fLength;
    float fDesiredVol, fFadedVolume;
    int fProperties;
    unsigned char fType, fPriority;
    bool fMuted, fFading, fRegisteredForTime;
    bool fPlayOnReactivate, fNotHighEnoughPriority;
    hsVector3 fConeOrientation;
    hsPoint3 f3DPosition;
    hsVector3 f3DVelocity;
    plSceneObject* fOwningSceneObject;
    plEAXSourceSettings fEAXSettings;
    bool fQueued;
    plFadeParams fFadeInParams, fFadeOutParams, fCoolSoftVolumeTrickParams;
    plFadeParams* fCurrFadeParams;
    plKey fSoftRegion;
    float fSoftVolume, fDistAttenuation, fDistToListenerSquared;
    double fVirtualStartTime;
    bool fRegistered;
    int fRefIndex;
    plKey fSoftOcclusionRegion;
    plKey fDataBuffer;
    bool fDataBufferLoaded;
    bool fLoading;

    static bool fLoadOnDemandFlag;
    static bool fLoadFromDiskOnDemandFlag;

public:
    plSound();
    virtual ~plSound();

    DECLARE_CREATABLE(plSound)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
};

#endif
