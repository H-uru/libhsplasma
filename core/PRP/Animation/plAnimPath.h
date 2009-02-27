#ifndef _PLANIMPATH_H
#define _PLANIMPATH_H

#include "PRP/plCreatable.h"
#include "Math/hsAffineParts.h"
#include "Math/hsMatrix44.h"
#include "Util/hsTArray.hpp"
#include "plTMController.h"

DllClass plAnimPath : public plCreatable {
public:
    enum Flags {
        kNone = 0,
        kFavorFwdSearch = 0x1,
        kFavorBwdSearch = 0x2,
        kCalcPosOnly = 0x4,
        kFarthest = 0x8,
        kWrap = 0x10,
        kIncrement = 0x20
    };

protected:
   unsigned int fAnimPathFlags;
   float fMinDistSq, fLength;
   hsMatrix44 fLocalToWorld, fWorldToLocal;
   plCompoundController* fController;
   plTMController* fTMController;
   hsAffineParts fParts;

public:
    plAnimPath();
    virtual ~plAnimPath();

    DECLARE_CREATABLE(plAnimPath)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned int getFlags() const;
    float getMinDistSq() const;
    float getLength() const;
    const hsMatrix44& getLocalToWorld() const;
    const hsMatrix44& getWorldToLocal() const;
    plCompoundController* getController() const;
    plTMController* getTMController() const;
    const hsAffineParts& getAffineParts() const;

    void setFlags(unsigned int flags);
    void setMinDistSq(float dist);
    void setLength(float length);
    void setLocalToWorld(const hsMatrix44& l2w);
    void setWorldToLocal(const hsMatrix44& w2l);
    void setController(plCompoundController* controller);
    void setTMController(plTMController* controller);
    void setAffineParts(const hsAffineParts& parts);
};

#endif
