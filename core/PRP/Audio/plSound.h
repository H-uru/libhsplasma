#ifndef _PLSOUND_H
#define _PLSOUND_H

#include "PRP/Object/plSceneObject.h"
#include "Math/hsGeometry3.h"
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
        void prcParse(const pfPrcTag* tag);
    };

protected:
    unsigned char fType, fPriority;
    bool fPlaying;
    double fTime;
    int fMaxFalloff, fMinFalloff;
    int fOuterVol, fInnerCone, fOuterCone;
    float fCurrVolume, fDesiredVol, fFadedVolume;
    unsigned int fProperties;
    plEAXSourceSettings fEAXSettings;
    plFadeParams fFadeInParams, fFadeOutParams;
    plKey fSoftRegion, fSoftOcclusionRegion, fDataBuffer;
    plString fSubtitleId;

public:
    plSound();
    virtual ~plSound();

    DECLARE_CREATABLE(plSound)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);

public:
    unsigned char getType() const;
    unsigned char getPriority() const;
    bool isPlaying() const;
    double getTime() const;
    int getMaxFalloff() const;
    int getMinFalloff() const;
    int getOuterVol() const;
    int getInnerCone() const;
    int getOuterCone() const;
    float getCurrVolume() const;
    float getDesiredVol() const;
    float getFadedVolume() const;
    unsigned int getProperties() const;
    plKey getSoftRegion() const;
    plKey getSoftOcclusionRegion() const;
    plKey getDataBuffer() const;
    plString getSubtitleId() const;

    void setType(unsigned char type);
    void setPriority(unsigned char priority);
    void setPlaying(bool playing);
    void setTime(double time);
    void setFalloff(int min, int max);
    void setOuterVol(int vol);
    void setCone(int inner, int outer);
    void setCurrVolume(float vol);
    void setDesiredVol(float vol);
    void setFadedVolume(float vol);
    void setProperties(unsigned int props);
    void setSoftRegion(plKey region);
    void setSoftOcclusionRegion(plKey region);
    void setDataBuffer(plKey buffer);
    void setSubtitleId(const plString& subtitle);

    plEAXSourceSettings& getEAXSettings();
    plFadeParams& getFadeInParams();
    plFadeParams& getFadeOutParams();
};

#endif
