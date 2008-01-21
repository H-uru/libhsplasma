#include "plResManager.h"
#include "NucleusLib/pnFactory/plFactory.h"
#include "PubUtilLib/plScene/plSceneNode.h"
#include "PubUtilLib/plJPEG/plJPEG.h"
#include "CoreLib/plDebug.h"

plResManager* plResManager::fGlobalResMgr = NULL;
unsigned int plResManager::fNumResMgrs = 0;
PlasmaVer plResManager::fPlasmaVer = pvUnknown;

plResManager::plResManager(PlasmaVer pv) {
    setVer(pv);
    if (plJPEG::inst == NULL)
        plJPEG::inst = new plJPEG;
    fNumResMgrs++;
}

plResManager::~plResManager() {
    while (ages.size() > 0)
        UnloadAge(ages[0]);
    while (pages.size() > 0)
        UnloadPage(pages[0]->getLocation());
    fNumResMgrs--;
    if ((fNumResMgrs == 1) && (fGlobalResMgr != NULL))
        delete fGlobalResMgr;
    if ((fNumResMgrs == 0) && (plJPEG::inst != NULL)) {
        delete plJPEG::inst;
        plJPEG::inst = NULL;
    }
}

plResManager* plResManager::GetGlobalResMgr() {
    if (fGlobalResMgr == NULL)
        fGlobalResMgr = new plResManager();
    return fGlobalResMgr;
}

void plResManager::setVer(PlasmaVer pv, bool mutate) {
    if (fPlasmaVer == pv) return;
    fPlasmaVer = pv;

    //
}

PlasmaVer plResManager::getVer() { return fPlasmaVer; }

plKey plResManager::readKey(hsStream* S) {
    if (getVer() != S->getVer())
        throw hsVersionMismatchException(__FILE__, __LINE__);

    bool exists = (S->getVer() == pvEoa || S->getVer() == pvHex) ? true : S->readBool();
    if (exists)
        return readUoid(S);
    else
        return plKey();
}

plKey plResManager::readUoid(hsStream* S) {
    if (getVer() != S->getVer())
        throw hsVersionMismatchException(__FILE__, __LINE__);

    plKey k = new plKeyData();
    if (S->getVer() == pvLive)
        S->readBool();
    k->readUoid(S);
    plKey xkey;
    if (k->getUoid().getLocation().isReserved())
        xkey = GetGlobalResMgr()->keys.findKey(k);
    else
        xkey = keys.findKey(k);
    if (xkey.Exists()) {
        return xkey;
    } else {
        if (k->getUoid().getLocation().isReserved())
            GetGlobalResMgr()->keys.add(k);
        else
            keys.add(k);
        return k;
    }
}

void plResManager::writeKey(hsStream* S, plKey key) {
    if (getVer() != S->getVer())
        throw hsVersionMismatchException(__FILE__, __LINE__);

    //key->exists = (strcmp(key->objName, "") != 0);
    if (S->getVer() != pvEoa && S->getVer() != pvHex)
        S->writeBool(key.Exists());
    if (key.Exists() || S->getVer() == pvEoa || S->getVer() == pvHex) {
        if (S->getVer() == pvLive)
            S->writeBool(key.Exists());
        key->writeUoid(S);
    }
}

void plResManager::writeKey(hsStream* S, hsKeyedObject* ko) {
    writeKey(S, ko->getKey());
}

void plResManager::writeUoid(hsStream* S, plKey key) {
    if (getVer() != S->getVer())
        throw hsVersionMismatchException(__FILE__, __LINE__);

    if (S->getVer() == pvLive)
        S->writeBool(true);
    key->writeUoid(S);
}

void plResManager::writeUoid(hsStream* S, hsKeyedObject* ko) {
    writeUoid(S, ko->getKey());
}

hsKeyedObject* plResManager::getObject(const plKey& key) {
    plKey fk = keys.findKey(key);
    if (!fk.Exists()) return NULL;
    return fk->getObj();
}

unsigned int plResManager::countKeys(const PageID& pid) {
    return keys.countKeys(pid);
}

plPageInfo* plResManager::ReadPage(const char* filename) {
    hsFileStream* S = new hsFileStream();
    setVer(S->getVer());
    if (!S->open(filename, fmRead))
        throw hsFileReadException(__FILE__, __LINE__, filename);
    plPageInfo* page = new plPageInfo;
    page->read(S);
    pages.push_back(page);
    setVer(S->getVer());

    S->seek(page->getIndexStart());
    ReadKeyring(S, page->getLocation());
    page->setNumObjects(ReadObjects(S, page->getLocation()));
    S->close();
    delete S;
    return page;
}

void plResManager::WritePage(const char* filename, plPageInfo* page) {
    hsFileStream* S = new hsFileStream();
    S->open(filename, fmWrite);
    S->setVer(getVer());
    if (getVer() == pvEoa || getVer() == pvHex || getVer() == pvLive) {
        std::vector<short> types = keys.getTypes(page->getLocation().getPageID());
        page->setClassList(types);
        keys.sortKeys(page->getLocation().getPageID());
    }
    page->write(S);
    page->setDataStart(S->pos());
    page->setNumObjects(WriteObjects(S, page->getLocation()));
    page->setIndexStart(S->pos());
    WriteKeyring(S, page->getLocation());
    if (getVer() == pvEoa || getVer() == pvHex)
        page->setChecksum(S->pos());
    else
        page->setChecksum(S->pos() - page->getDataStart());
    page->writeSums(S);
    S->close();
    delete S;
}

void plResManager::WritePrc(pfPrcHelper* prc, plPageInfo* page) {
    page->prcWrite(prc); // starts <Page>
    
    // Objects:
    std::vector<short> types = keys.getTypes(page->getLocation().getPageID());
    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = keys.getKeys(page->getLocation().getPageID(), types[i]);
        for (unsigned int j=0; j<kList.size(); j++) {
            if (kList[j]->getObj() != NULL) {
                kList[j]->getObj()->prcWrite(prc);
                prc->closeTag();
            }
        }
    }
    
    prc->closeTag();
}

void plResManager::UnloadPage(const plLocation& loc) {
    std::vector<plPageInfo*>::iterator pi = pages.begin();
    while (pi != pages.end()) {
        if ((*pi)->getLocation() == loc) {
            plPageInfo* page = *pi;
            pages.erase(pi);
            delete page;
            pi = pages.end();
        } else {
            pi++;
        }
    }
}

plAgeInfo* plResManager::ReadAge(const char* filename) {
    plAgeInfo* age = new plAgeInfo();
    age->readFromFile(filename);
    
    for (size_t i=0; i<age->getNumPages(); i++) {
        plPageInfo* page = age->getPage(i);
        age->setPage(i, ReadPage(page->getFilename(getVer())));
    }

    ages.push_back(age);
    return age;
}

void plResManager::WriteAge(const char* filename, plAgeInfo* age) {
    plString path = filename;
    plString ageName = path.afterLast(PATHSEP);
    if (!ageName.beforeLast('.').empty())
        ageName = ageName.beforeLast('.');
    path = path.beforeLast(PATHSEP);
    age->setAgeName(ageName);
    age->writeToPath(path, getVer());
}

void plResManager::UnloadAge(plAgeInfo* age) {
    for (size_t i=0; i<age->getNumPages(); i++)
        UnloadPage(age->getPage(i)->getLocation());
    
    std::vector<plAgeInfo*>::iterator ai = ages.begin();
    while (ai != ages.end()) {
        if ((*ai) == age) {
            ages.erase(ai);
            ai = ages.end();
        } else {
            ai++;
        }
    }
    delete age;
    age = NULL;
}

void plResManager::ReadKeyring(hsStream* S, const plLocation& loc) {
    //plDebug::Debug("* Reading Keyring");
    //keys.addPage(loc.pageID);
    unsigned int tCount = S->readInt();
    for (unsigned int i=0; i<tCount; i++) {
        short type = S->readShort(); // objType
        if (S->getVer() == pvEoa || S->getVer() == pvHex || S->getVer() == pvLive) {
            S->readInt(); // # of bytes after this int to next key list
            S->readByte(); // flag?
        }
        unsigned int oCount = S->readInt();
        keys.reserveKeySpace(loc.getPageID(), type, oCount);
        //plDebug::Debug("  * Indexing %d objects of type [%04X]", oCount, type);
        for (unsigned int j=0; j<oCount; j++) {
            plKey key = new plKeyData();
            key->read(S);
            //if (S->getVer() != pvEoa && S->getVer() != pvHex && S->getVer() != pvLive)
            //    key->setID(j);
            keys.add(key);
            //plDebug::Debug("    * Key %s", key->toString());
        }
    }
}

void plResManager::WriteKeyring(hsStream* S, const plLocation& loc) {
    std::vector<short> types = keys.getTypes(loc.getPageID());
    S->writeInt(types.size());
    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = keys.getKeys(loc.getPageID(), types[i]);
        if (kList.size() <= 0) continue;
        S->writeShort(pdUnifiedTypeMap::MappedToPlasma(kList[0]->getType(), S->getVer()));
        unsigned int lenPos = S->pos();
        if (S->getVer() == pvEoa || S->getVer() == pvHex || S->getVer() == pvLive) {
            S->writeInt(0);
            S->writeByte(0);
        }
        S->writeInt(kList.size());
        for (unsigned int j=0; j<kList.size(); j++)
            kList[j]->write(S);
        if (S->getVer() == pvEoa || S->getVer() == pvHex || S->getVer() == pvLive) {
            unsigned int nextPos = S->pos();
            S->seek(lenPos);
            S->writeInt(nextPos - lenPos - 4);
            S->seek(nextPos);
        }
    }
}

unsigned int plResManager::ReadObjects(hsStream* S, const plLocation& loc) {
    //plDebug::Debug("* Reading Objects");
    std::vector<short> types = keys.getTypes(loc.getPageID());
    unsigned int nRead = 0;
    
    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = keys.getKeys(loc.getPageID(), types[i]);
        //plDebug::Debug("* Reading %d objects of type [%04X]%s", kList.size(),
        //               types[i], pdUnifiedTypeMap::ClassName(types[i], S->getVer()));
        for (unsigned int j=0; j<kList.size(); j++) {
            if (kList[j]->getFileOff() <= 0) continue;
            //plDebug::Debug("  * (%d) Reading %s @ 0x%08X", j, kList[j]->getName(),
            //               kList[j]->fileOff);
            S->seek(kList[j]->getFileOff());
            try {
                kList[j]->setObj(hsKeyedObject::Convert(ReadCreatable(S)));
                if (kList[j]->getObj() != NULL) {
                    nRead++;
                    if (kList[j]->getObjSize() != S->pos() - kList[j]->getFileOff())
                        plDebug::Warning("[%04X:%s] Size-Read difference: %d bytes",
                            kList[j]->getType(), kList[j]->getName().cstr(),
                            (int)(kList[j]->getObjSize() -
                                  (S->pos() - kList[j]->getFileOff())));
                }
            } catch (const std::exception& e) {
                plDebug::Error("Failed reading %s: %s",
                               kList[j]->toString().cstr(), e.what());
                delete kList[j]->getObj();
                kList[j]->setObj(NULL);
            } catch (...) {
                plDebug::Error("Undefined error reading %s",
                               kList[j]->toString().cstr());
                delete kList[j]->getObj();
                kList[j]->setObj(NULL);
            }
        }
    }

    return nRead;
}

unsigned int plResManager::WriteObjects(hsStream* S, const plLocation& loc) {
    std::vector<short> types = keys.getTypes(loc.getPageID());
    unsigned int nWritten = 0;

    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = keys.getKeys(loc.getPageID(), types[i]);
        //plDebug::Debug("* Writing %d objects of type [%04X]", kList.size(), types[i]);
        for (unsigned int j=0; j<kList.size(); j++) {
            kList[j]->setFileOff(S->pos());
            kList[j]->setID(j);
            if (kList[j]->getObj() != NULL) {
                try {
                    WriteCreatable(S, kList[j]->getObj());
                    nWritten++;
                } catch (const char* e) {
                    plDebug::Error("Failed writing %s: %s",
                                   kList[j]->toString().cstr(), e);
                } catch (...) {
                    plDebug::Error("Undefined error writing %s",
                                   kList[j]->toString().cstr());
                }
            }
            kList[j]->setObjSize(S->pos() - kList[j]->getFileOff());
        }
    }

    return nWritten;
}

plCreatable* plResManager::ReadCreatable(hsStream* S) {
    unsigned short type = S->readShort();
    plCreatable* pCre = plFactory::Create(type, S->getVer());
    if (pCre != NULL)
        pCre->read(S, this);
    else if (type != 0x8000)
        plDebug::Warning("Warning: NOT reading object of type [%04X]", type);
    return pCre;
}

void plResManager::WriteCreatable(hsStream* S, plCreatable* pCre) {
    if (pCre == NULL) {
        S->writeShort(0x8000);
    } else {
        S->writeShort(pCre->ClassIndex(S->getVer()));
        pCre->write(S, this);
    }
}

plSceneNode* plResManager::getSceneNode(const plLocation& loc) {
    std::vector<plKey> kList = keys.getKeys(loc.getPageID(), kSceneNode);
    if (kList.size() < 1) return NULL;
    return (plSceneNode*)kList[0]->getObj();
}

std::vector<plLocation> plResManager::getLocations() {
    std::vector<plLocation> locArr;
    for (size_t i=0; i<pages.size(); i++)
        locArr.push_back(pages[i]->getLocation());
    return locArr;
}

std::vector<plKey> plResManager::getKeys(const plLocation& loc, short type) {
    return keys.getKeys(loc.getPageID(), type);
}
