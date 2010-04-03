#ifndef _PLARMATUREBRAIN_H
#define _PLARMATUREBRAIN_H

#include "PRP/plCreatable.h"

DllClass plArmatureBrain : public plCreatable {
    CREATABLE(plArmatureBrain, kArmatureBrain, plCreatable)

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plAvBrainHuman : public plArmatureBrain {
    CREATABLE(plAvBrainHuman, kAvBrainHuman, plArmatureBrain)

protected:
    bool fIsCustomAvatar;

public:
    plAvBrainHuman();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool isCustomAvatar() const { return fIsCustomAvatar; }
    void setIsCustomAvatar(bool value) { fIsCustomAvatar = value; }
};


DllClass plAvBrainClimb : public plArmatureBrain {
    CREATABLE(plAvBrainClimb, kAvBrainClimb, plArmatureBrain)
};


DllClass plAvBrainCritter : public plArmatureBrain {
    CREATABLE(plAvBrainCritter, kAvBrainCritter, plArmatureBrain)
};


DllClass plAvBrainDrive : public plArmatureBrain {
    CREATABLE(plAvBrainDrive, kAvBrainDrive, plArmatureBrain)
};


DllClass plAvBrainPirahna : public plArmatureBrain {
    CREATABLE(plAvBrainPirahna, kAvBrainPirahna, plArmatureBrain)
};


DllClass plAvBrainQuab : public plArmatureBrain {
    CREATABLE(plAvBrainQuab, kAvBrainQuab, plArmatureBrain)
};


DllClass plAvBrainRideAnimatedPhysical : public plArmatureBrain {
    CREATABLE(plAvBrainRideAnimatedPhysical, kAvBrainRideAnimatedPhysical,
              plArmatureBrain)
};


DllClass plAvBrainSwim : public plArmatureBrain {
    CREATABLE(plAvBrainSwim, kAvBrainSwim, plArmatureBrain)
};

#endif
