#ifndef _PLRESMANAGER_H
#define _PLRESMANAGER_H

#include "../../PlasmaDefs.h"
#include "../../CoreLib/hsRefCnt.h"
#include "../../DynLib/PlasmaVersions.h"
#include "../../DynLib/PageID.h"
#include "../../NucleusLib/pnKeyedObject/plKey.h"
#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../PubUtilLib/plScene/plSceneNode.h"
#include "../../CoreLib/plEncryptedStream.h"
#include "../../CoreLib/hsTArray.hpp"
#include "plKeyCollector.h"
#include "plPageInfo.h"
#include "plPageSettings.h"
#ifdef Tahg
  #include "../../NucleusLib/inc/hsResMgr.h"
  #include "../../NucleusLib/pnDispatch/plDispatch.h"
  #include <vector>
  #include <xmemory>
#endif

DllClass plResManager /* : public hsResMgr */ {
protected:
    PlasmaVer ver;

public:
    plKeyCollector keys;
    std::vector<plPageInfo*> pages;
    std::vector<plAgeSettings*> ages;

private:
    plKey* readKeyBase(hsStream* S);
    void writeKeyBase(hsStream* S, plKey* key);
    void ReadKeyring(hsStream* S, plLocation& loc);
    unsigned int ReadObjects(hsStream* S, plLocation& loc);
    void WriteKeyring(hsStream* S, plLocation& loc);
    unsigned int WriteObjects(hsStream* S, plLocation& loc);

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
    plKey* readUoidKey(hsStream* S);
    void writeKey(hsStream* S, plKey* key);
    void writeUoidKey(hsStream* S, plKey* key);
    hsKeyedObject* getObject(plKey& key);

    plPageInfo* ReadPage(const char* filename);
    void WritePage(const char* filename, plPageInfo* page);

    plAgeSettings* ReadAge(const char* filename);
    void WriteAge(const char* filename, plAgeSettings* age);

    plSceneNode* getSceneNode(plLocation& loc);
};

#endif

