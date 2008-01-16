#ifndef _PLONESHOTCALLBACKS_H
#define _PLONESHOTCALLBACKS_H

#include "../../CoreLib/hsTArray.hpp"
#include "../../NucleusLib/pnKeyedObject/plKey.h"
#include "../plResMgr/plResManager.h"

DllClass plOneShotCallbacks /* : hsRefCnt */ {
public:
    DllClass plOneShotCallback {
    public:
        plString fMarker;
        plKey fReceiver;
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
};

#endif
