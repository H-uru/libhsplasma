#ifndef _PLONESHOTCALLBACKS_H
#define _PLONESHOTCALLBACKS_H

#include "Util/hsTArray.hpp"
#include "PRP/KeyedObject/plKey.h"
#include "ResManager/plResManager.h"

DllClass plOneShotCallbacks /* : hsRefCnt */ {
public:
    DllClass plOneShotCallback {
    public:
        plString fMarker;
        plWeakKey fReceiver;
        short fUser;
    };

protected:
    hsTArray<plOneShotCallback> fCallbacks;

public:
    plOneShotCallbacks();
    ~plOneShotCallbacks();

    void read(hsStream* S, plResManager* mgr);
    void write(hsStream* S, plResManager* mgr);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
