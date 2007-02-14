#ifndef _PLRESMANAGER_H
#define _PLRESMANAGER_H

#include "../../CoreLib/hsRefCnt.h"
#include "../../DynLib/PlasmaVersions.h"
#include "../../DynLib/PageID.h"
#include "../../NucleusLib/pnKeyedObject/plKey.h"
#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../PubUtilLib/plScene/plSceneNode.h"
#include "../../CoreLib/hsStream.h"
#include "../../CoreLib/hsTArray.hpp"
#include "plKeyCollector.h"
#include "plPageSettings.h"
#ifdef Tahg
  #include "../../NucleusLib/inc/hsResMgr.h"
  #include "../../NucleusLib/pnDispatch/plDispatch.h"
  #include <vector>
  #include <xmemory>
#endif

class plResManager /* : hsResMgr */ {
protected:
    PlasmaVer ver;

public:
    plKeyCollector keys;
    std::vector<plPageSettings*> pages;

private:
    plKey* readKeyBase(hsStream* S);
    void writeKeyBase(hsStream* S, plKey* key);
    void ReadKeyring(hsStream* S, PageID& pid);
    unsigned int ReadObjects(hsStream* S, PageID& pid);
    void WriteKeyring(hsStream* S, PageID& pid);
    unsigned int WriteObjects(hsStream* S, PageID& pid);

#ifdef Tahg
    bool fInited;
    unsigned short fPageOutHint;
    class plRegistry * fRegistry;
    bool fReadingObject;
    //class std::vector<plKey> fQueuedReads;
    class plUoidAliasMgr * fpAliases;
    unsigned char fLoaded;
    class plDispatch * fDispatch;
    class hsStream * fInitialState;
    unsigned long fCurCloneID;
    unsigned long fCurClonePlayerID;
    unsigned long fCloningCounter;
    //class std::map<std::string, plRegistrySource*> fIOSources;
    //class hsTArray<plResAgeHolder *> fHoldingAges;
    //class hsTArray<plResManager::plVersionPair> fReadVersionStack;
    //function * fProgressProc;
    class plResManagerHelper * fMyHelper;
    bool fLogReadTimes;
public:
	virtual plDispatchBase * Dispatch(){ return fDispatch; }
#endif

public:
    static plResManager* inst;

    plResManager(PlasmaVer pv = pvUnknown);
    virtual ~plResManager();

    virtual void setVer(PlasmaVer pv, bool mutate = false);
    PlasmaVer getVer();

    plKey* readKey(hsStream* S);
    plKey* readRealKey(hsStream* S);
    void writeKey(hsStream* S, plKey* key);
    void writeRealKey(hsStream* S, plKey* key);
    hsKeyedObject* getObject(plKey& key);

    plPageSettings* ReadPage(const char* filename);
    void WritePage(const char* filename, plPageSettings* page);

    plSceneNode* getSceneNode(PageID& pid);
};

#endif

