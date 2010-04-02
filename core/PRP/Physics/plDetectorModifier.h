#ifndef _PLDETECTORMODIFIER_H
#define _PLDETECTORMODIFIER_H

#include "PRP/Modifier/plModifier.h"

DllClass plDetectorModifier : public plSingleModifier {
    CREATABLE(plDetectorModifier, kDetectorModifier, plSingleModifier)

protected:
    hsTArray<plKey> fReceivers;
    plKey fRemoteMod, fProxyKey;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plKey>& getReceivers() const { return fReceivers; }
    hsTArray<plKey>& getReceivers() { return fReceivers; }
    void addReceiver(plKey rcvr) { fReceivers.append(rcvr); }
    void delReceiver(size_t idx) { fReceivers.remove(idx); }
    void clearReceivers() { fReceivers.clear(); }

    plKey getRemoteMod() const { return fRemoteMod; }
    plKey getProxy() const { return fProxyKey; }

    void setRemoteMod(plKey mod) { fRemoteMod = mod; }
    void setProxy(plKey proxy) { fProxyKey = proxy; }
};


DllClass plPickingDetector : public plDetectorModifier {
    CREATABLE(plPickingDetector, kPickingDetector, plDetectorModifier)
};

#endif
