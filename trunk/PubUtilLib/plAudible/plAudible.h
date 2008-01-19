#ifndef _PLAUDIBLE_H
#define _PLAUDIBLE_H

#include "NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "NucleusLib/pnMessage/plEventCallbackMsg.h"
#include "CoreLib/hsMatrix44.h"

DllClass plAudible : public hsKeyedObject {
protected:
    hsTArray<plEventCallbackMsg*> fCallbacks;

public:
    plAudible();
    virtual ~plAudible();

    DECLARE_CREATABLE(plAudible)
};

DllClass plAudibleNull : public plAudible {
protected:
    plKey fSceneNode, fSceneObj;

public:
    plAudibleNull();
    virtual ~plAudibleNull();

    DECLARE_CREATABLE(plAudibleNull)
};

DllClass plWinAudible : public plAudible {
protected:
    hsTArray<plKey> fSoundObjs;
    plKey fSceneNode, fSceneObj;
    //plWinAudibleProxy* fProxyGen;
    hsMatrix44 fLocalToWorld;
    //plSoundSDLModifier* fSDLMod;

public:
    plWinAudible();
    virtual ~plWinAudible();

    DECLARE_CREATABLE(plWinAudible)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass pl2WayWinAudible : public plWinAudible {
protected:
    //plVoicePlayer* fVoicePlayer;
    //plVoiceRecorder* fVoiceRecorder;

public:
    pl2WayWinAudible();
    virtual ~pl2WayWinAudible();

    DECLARE_CREATABLE(pl2WayWinAudible)
};

#endif
