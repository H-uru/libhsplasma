#ifndef _PLAXISANIMMODIFIER_H
#define _PLAXISANIMMODIFIER_H

#include "plModifier.h"
#include "PRP/Message/plNotifyMsg.h"

DllClass plAxisAnimModifier : public plSingleModifier {
private:
    plKey fXAnim, fYAnim, fNotificationKey;
    plNotifyMsg* fNotify;
    plString fAnimLabel;
    bool fAllOrNothing;

    // Lots of unknown EOA parameters:
    bool b65, b66, b70;
    hsTArray<float> af38;
    hsTArray<float> af40;
    float f48, f58, f5c;
    float fb0, fac, fa0, f98, fa4;
    bool b60, b90, bb4, bb5;

public:
    plAxisAnimModifier();
    virtual ~plAxisAnimModifier();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getXAnim() const;
    plKey getYAnim() const;
    plKey getNotificationKey() const;
    plNotifyMsg* getNotify() const;
    plString getAnimLabel() const;
    bool getAllOrNothing() const;

    void setXAnim(plKey anim);
    void setYAnim(plKey anim);
    void setNotificationKey(plKey notify);
    void setNotify(plNotifyMsg* msg);
    void setAnimLabel(const plString& label);
    void setAllOrNothing(bool value);
};

#endif
