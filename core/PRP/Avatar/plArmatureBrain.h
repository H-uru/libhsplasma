#ifndef _PLARMATUREBRAIN_H
#define _PLARMATUREBRAIN_H

#include "PRP/plCreatable.h"

DllClass plArmatureBrain : public plCreatable {
public:
    plArmatureBrain();
    virtual ~plArmatureBrain();

    DECLARE_CREATABLE(plArmatureBrain)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plAvBrainHuman : public plArmatureBrain {
protected:
    bool fIsCustomAvatar;

public:
    plAvBrainHuman();
    virtual ~plAvBrainHuman();

    DECLARE_CREATABLE(plAvBrainHuman);

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool isCustomAvatar() const;
    void setIsCustomAvatar(bool value);
};

DllClass plAvBrainClimb : public plArmatureBrain {
public:
    DECLARE_CREATABLE(plAvBrainClimb);
};

DllClass plAvBrainCritter : public plArmatureBrain {
public:
    DECLARE_CREATABLE(plAvBrainCritter);
};

DllClass plAvBrainDrive : public plArmatureBrain {
public:
    DECLARE_CREATABLE(plAvBrainDrive);
};

DllClass plAvBrainPirahna : public plArmatureBrain {
public:
    DECLARE_CREATABLE(plAvBrainPirahna);
};

DllClass plAvBrainQuab : public plArmatureBrain {
public:
    DECLARE_CREATABLE(plAvBrainQuab);
};

DllClass plAvBrainRideAnimatedPhysical : public plArmatureBrain {
public:
    DECLARE_CREATABLE(plAvBrainRideAnimatedPhysical);
};

DllClass plAvBrainSwim : public plArmatureBrain {
public:
    DECLARE_CREATABLE(plAvBrainSwim);
};

#endif
