#ifndef _PLAGANIM_H
#define _PLAGANIM_H

#include "PRP/Object/plSynchedObject.h"
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
    unsigned char fEoaFlag;

public:
    plAGAnim();
    virtual ~plAGAnim();

    DECLARE_CREATABLE(plAGAnim)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumApplicators() const;
    plAGApplicator* getApplicator(size_t idx) const;
    void clearApplicators();
    void addApplicator(plAGApplicator* app);
    void delApplicator(size_t idx);

    float getBlend() const;
    float getStart() const;
    float getEnd() const;
    plString getName() const;

    void setBlend(float blend);
    void setStart(float start);
    void setEnd(float end);
    void setName(const plString& name);
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

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plString getVarName() const;
    void setVarName(const plString& name);
};

#endif
