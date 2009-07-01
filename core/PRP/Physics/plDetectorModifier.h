#ifndef _PLDETECTORMODIFIER_H
#define _PLDETECTORMODIFIER_H

#include "PRP/Modifier/plModifier.h"

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

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumReceivers() const;
    plKey getReceiver(size_t idx) const;
    void addReceiver(plKey rcvr);
    void delReceiver(size_t idx);
    void clearReceivers();

    plKey getRemoteMod() const;
    plKey getProxy() const;

    void setRemoteMod(plKey mod);
    void setProxy(plKey proxy);
};

DllClass plPickingDetector : public plDetectorModifier {
public:
    DECLARE_CREATABLE(plPickingDetector)
};

#endif
