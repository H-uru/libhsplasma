#ifndef _PFOBJECTFLOCKER_H
#define _PFOBJECTFLOCKER_H

#include "PRP/Modifier/plModifier.h"

/* Obviously needs a lot more research */
DllClass pfObjectFlocker : public plSingleModifier {
public:
    DllStruct FlockStruct {
        float fFloat1;
        float fFloat2[6];
        float fFloat3;

        FlockStruct();
    };

protected:
    unsigned char fFlags;
    bool fBool1, fBool2;
    plKey fTarget;
    float fFloat1;
    FlockStruct fFlockStruct;

public:
    pfObjectFlocker();

    DECLARE_CREATABLE(pfObjectFlocker)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
