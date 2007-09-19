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
#include "../../FeatureLib/pfPRC/pfPrcHelper.h"
#include "plKeyCollector.h"
#include "plPageInfo.h"
#include "plPageSettings.h"

DllClass plResManager /* : public hsResMgr */ {
private:
    static plResManager* fGlobalResMgr;
    static unsigned int fNumResMgrs;

protected:
    PlasmaVer ver;
    plKeyCollector keys;
    std::vector<plPageInfo*> pages;
    std::vector<plAgeSettings*> ages;

private:
    plKey readKeyBase(hsStream* S);
    void writeKeyBase(hsStream* S, plKey key);
    void ReadKeyring(hsStream* S, plLocation& loc);
    unsigned int ReadObjects(hsStream* S, plLocation& loc);
    void WriteKeyring(hsStream* S, plLocation& loc);
    unsigned int WriteObjects(hsStream* S, plLocation& loc);

public:
    plResManager(PlasmaVer pv = pvUnknown);
    virtual ~plResManager();
    static plResManager* GetGlobalResMgr();

    virtual void setVer(PlasmaVer pv, bool mutate = false);
    PlasmaVer getVer();

    plKey readKey(hsStream* S);
    plKey readUoid(hsStream* S);
    void writeKey(hsStream* S, plKey key);
    void writeKey(hsStream* S, hsKeyedObject* ko);
    void writeUoid(hsStream* S, plKey key);
    void writeUoid(hsStream* S, hsKeyedObject* ko);
    hsKeyedObject* getObject(const plKey& key);
    unsigned int countKeys(const PageID& pid);

    plPageInfo* ReadPage(const char* filename);
    void WritePage(const char* filename, plPageInfo* page);
    void WritePrc(pfPrcHelper* prc, plPageInfo* page);
    void UnloadPage(plLocation& loc);
    
    plAgeSettings* ReadAge(const char* filename);
    void WriteAge(const char* filename, plAgeSettings* age);
    void UnloadAge(plAgeSettings* age);

    plCreatable* ReadCreatable(hsStream* S);
    void WriteCreatable(hsStream* S, plCreatable* pCre);

    plSceneNode* getSceneNode(plLocation& loc);
};

#endif

