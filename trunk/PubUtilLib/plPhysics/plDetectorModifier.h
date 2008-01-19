#ifndef _PLDETECTORMODIFIER_H
#define _PLDETECTORMODIFIER_H

#include "NucleusLib/pnModifier/plModifier.h"

DllClass plDetectorModifier : public plSingleModifier {
protected:
    hsTArray<plKey> fReceivers;
    plKey fRemoteMod, fProxyKey;

public:
    plDetectorModifier();
    virtual ~plDetectorModifier();

    DECLARE_CREATABLE(plDetectorModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plPickingDetector : public plDetectorModifier {
public:
    plPickingDetector();
    virtual ~plPickingDetector();

    DECLARE_CREATABLE(plPickingDetector)
};

#endif
