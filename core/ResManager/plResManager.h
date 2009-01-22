#ifndef _PLRESMANAGER_H
#define _PLRESMANAGER_H

#include "PlasmaDefs.h"
#include "Util/PlasmaVersions.h"
#include "PRP/KeyedObject/plLocation.h"
#include "pdUnifiedTypeMap.h"
#include "Stream/plEncryptedStream.h"
#include "Util/hsTArray.hpp"
#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"
#include "plKeyCollector.h"
#include "PRP/plPageInfo.h"
#include "plAgeInfo.h"

typedef void (*ProgressCallback)(float progress);

DllClass plResManager {
private:
    static unsigned int fNumResMgrs;

protected:
    PlasmaVer fPlasmaVer;
    plKeyCollector keys;
    std::vector<plPageInfo*> pages;
    std::vector<plAgeInfo*> ages;
    ProgressCallback progressFunc;

private:
    void ReadKeyring(hsStream* S, const plLocation& loc);
    unsigned int ReadObjects(hsStream* S, const plLocation& loc);
    void WriteKeyring(hsStream* S, const plLocation& loc);
    unsigned int WriteObjects(hsStream* S, const plLocation& loc);

public:
    plResManager(PlasmaVer pv = pvUnknown);
    virtual ~plResManager();

    void setVer(PlasmaVer pv, bool force = false);
    PlasmaVer getVer();

    plKey readKey(hsStream* S);
    plKey readUoid(hsStream* S);
    void writeKey(hsStream* S, plKey key);
    void writeKey(hsStream* S, hsKeyedObject* ko);
    void writeUoid(hsStream* S, plKey key);
    void writeUoid(hsStream* S, hsKeyedObject* ko);
    plKey prcParseKey(const pfPrcTag* tag);
    class hsKeyedObject* getObject(plKey key);
    unsigned int countKeys(const plLocation& loc);

    plPageInfo* ReadPage(const char* filename);
    plPageInfo* ReadPagePrc(const pfPrcTag* root);
    void WritePage(const char* filename, plPageInfo* page);
    void WritePagePrc(pfPrcHelper* prc, plPageInfo* page);
    plPageInfo* FindPage(const plLocation& loc);
    void UnloadPage(const plLocation& loc);

    plAgeInfo* ReadAge(const char* filename, bool readPages);
    plAgeInfo* ReadAgePrc(const pfPrcTag* root);
    void WriteAge(const char* filename, plAgeInfo* age);
    void WriteAgePrc(pfPrcHelper* prc, plAgeInfo* age);
    plAgeInfo* FindAge(const plString& name);
    void UnloadAge(const plString& name);

    class plCreatable* ReadCreatable(hsStream* S, bool canStub = false, int stubLen = 0);
    void WriteCreatable(hsStream* S, class plCreatable* pCre);
    class plCreatable* prcParseCreatable(const pfPrcTag* tag);

    class plSceneNode* getSceneNode(const plLocation& loc);
    std::vector<plLocation> getLocations();
    std::vector<short> getTypes(const plLocation& loc);
    std::vector<plKey> getKeys(const plLocation& loc, short type);

    plKey AddKey(plKey key);
    void MoveKey(plKey key, const plLocation& to);
    void AddObject(const plLocation& loc, hsKeyedObject* obj);
    void AddPage(plPageInfo* page);
    void AddAge(plAgeInfo* age);
    void DelObject(plKey obj);
    void DelPage(const plLocation& loc);
    void DelAge(const plString& name);

    void ChangeLocation(plLocation from, plLocation to);
    ProgressCallback SetProgressFunc(ProgressCallback newFunc);
};

#endif
