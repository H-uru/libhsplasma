#ifndef _PLCAMERAMODIFIER_H
#define _PLCAMERAMODIFIER_H

#include "PRP/Modifier/plModifier.h"
#include "PRP/Message/plCameraMsg.h"

DllClass plCameraModifier1 : public plSingleModifier {
public:
    DllClass CamTrans {
    protected:
        plKey fTransTo;
        bool fCutPos, fCutPOA, fIgnore;
        float fAccel, fDecel, fVelocity, fPOAAccel, fPOADecel, fPOAVelocity;

    public:
        CamTrans();
        ~CamTrans();

        void read(hsStream* S, plResManager* mgr);
        void write(hsStream* S, plResManager* mgr);
        void prcWrite(pfPrcHelper* prc);
        void prcParse(const pfPrcTag* tag, plResManager* mgr);
    };

protected:
    hsVector3 fFrom, fAt;
    plKey fBrain;
    hsTArray<CamTrans*> fTrans;
    float fFOVw, fFOVh;
    hsTArray<plMessage*> fMessageQueue;
    hsTArray<plKey> fSenderQueue;
    hsTArray<plCameraMsg*> fFOVInstructions;
    bool fAnimated, fStartAnimOnPush, fStopAnimOnPop, fResetAnimOnPop;

    void DeleteTrans();

public:
    plCameraModifier1();
    virtual ~plCameraModifier1();

    DECLARE_CREATABLE(plCameraModifier1)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
