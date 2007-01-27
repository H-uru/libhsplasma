#ifndef _PLRESMANAGER_H
#define _PLRESMANAGER_H

#include "../../CoreLib/hsRefCnt.h"
#include "../../DynLib/PlasmaVersions.h"
#include "../../DynLib/PageID.h"
#include "../../NucleusLib/pnKeyedObject/plKey.h"
#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../CoreLib/hsStream.h"
#include "../../CoreLib/hsTArray.hpp"
#include "plKeyCollector.h"
#include "plPageSettings.h"
#include "../../NucleusLib/inc/hsResMgr.h"
#include "../../NucleusLib/pnDispatch/plDispatch.h"
#include <vector>
#include <xmemory>

class plResManager : hsResMgr {
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

  int fInited; //this+0x8
  unsigned short fPageOutHint; //this+0xc
  class plRegistry * fRegistry; //this+0x10
  bool fReadingObject; //this+0x14
//  class std::vector<plKey,std::allocator<plKey> > fQueuedReads; //this+0x18
  class plUoidAliasMgr * fpAliases; //this+0x28
  unsigned char fLoaded; //this+0x2c
  class plDispatch * fDispatch; //this+0x30
  class hsStream * fInitialState; //this+0x34
  unsigned long fCurCloneID; //this+0x38
  unsigned long fCurClonePlayerID; //this+0x3c
  unsigned long fCloningCounter; //this+0x40
//  class std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,plRegistrySource *,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,plRegistrySource *> > > fIOSources; //this+0x44
//  class hsTArray<plResAgeHolder *> fHoldingAges; //this+0x50
//  class hsTArray<plResManager::plVersionPair> fReadVersionStack; //this+0x58
//  function  * fProgressProc; //this+0x60
  class plResManagerHelper * fMyHelper; //this+0x64
  bool fLogReadTimes; //this+0x68

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
	virtual plDispatchBase * Dispatch(){ return fDispatch; }
};

#endif

