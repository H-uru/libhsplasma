#ifndef _PLATCANIM_H
#define _PLATCANIM_H

#include "plAGAnim.h"
#include <map>

DllClass plATCAnim : public plAGAnim {
public:
    typedef std::map<plString, float> marker_t;
    typedef std::map<plString, std::pair<float, float> > loop_t;

protected:
    float fInitial, fLoopStart, fLoopEnd;
    bool fAutoStart, fLoop;
    unsigned char fEaseInType, fEaseOutType;
    float fEaseInLength, fEaseInMin, fEaseInMax;
    float fEaseOutLength, fEaseOutMin, fEaseOutMax;
    marker_t fMarkers;
    loop_t fLoops;
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

public:
    marker_t& getMarkers();
    loop_t& getLoops();

    float getInitial() const;
    float getLoopStart() const;
    float getLoopEnd() const;
    bool getAutoStart() const;
    bool getDoLoop() const;
    unsigned char getEaseInType() const;
    unsigned char getEaseOutType() const;
    float getEaseInLength() const;
    float getEaseInMin() const;
    float getEaseInMax() const;
    float getEaseOutLength() const;
    float getEaseOutMin() const;
    float getEaseOutMax() const;

    float getMarker(const plString& key) const;
    std::pair<float, float> getLoop(const plString& key) const;
    const hsTArray<float>& getStops() const;

    void setInitial(float init);
    void setLoopStart(float start);
    void setLoopEnd(float end);
    void setAutoStart(bool autoStart);
    void setDoLoop(bool loop);
    void setEaseInType(unsigned char type);
    void setEaseOutType(unsigned char type);
    void setEaseInParams(float length, float min, float max);
    void setEaseOutParams(float length, float min, float max);

    void setMarker(const plString& key, float value);
    void setLoop(const plString& key, float start, float end);
    void setStops(const hsTArray<float>& stops);
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

public:
    plAGAnim::BodyUsage getBodyUsage() const;
    float getFadeIn() const;
    float getFadeOut() const;

    void setBodyUsage(plAGAnim::BodyUsage usage);
    void setFadeIn(float fade);
    void setFadeOut(float fade);
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

public:
    plString getBinkFilename() const;
    plString getSgtFilename() const;
    plString getSubtitleId() const;

    void setBinkFilename(const plString& filename);
    void setSgtFilename(const plString& filename);
    void setSubtitleId(const plString& id);
};

#endif
