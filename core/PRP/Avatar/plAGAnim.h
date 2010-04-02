#ifndef _PLAGANIM_H
#define _PLAGANIM_H

#include "PRP/Object/plSynchedObject.h"
#include "plAGApplicator.h"

DllClass plAGAnim : public plSynchedObject {
    CREATABLE(plAGAnim, kAGAnim, plSynchedObject)

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

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plAGApplicator*>& getApplicators() const { return fApps; }
    hsTArray<plAGApplicator*>& getApplicators() { return fApps; }
    void addApplicator(plAGApplicator* app) { fApps.append(app); }
    void delApplicator(size_t idx);
    void clearApplicators();

    float getBlend() const { return fBlend; }
    float getStart() const { return fStart; }
    float getEnd() const { return fEnd; }
    plString getName() const { return fName; }

    void setBlend(float blend) { fBlend = blend; }
    void setStart(float start) { fStart = start; }
    void setEnd(float end) { fEnd = end; }
    void setName(const plString& name) { fName = name; }
};

DllClass plAgeGlobalAnim : public plAGAnim {
    CREATABLE(plAgeGlobalAnim, kAgeGlobalAnim, plAGAnim)

protected:
    plString fGlobalVarName;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plString getVarName() const { return fGlobalVarName; }
    void setVarName(const plString& name) { fGlobalVarName = name; }
};

#endif
