#include "plResManager.h"
#include "plFactory.h"
#include "PRP/plSceneNode.h"
#include "Debug/plDebug.h"
#include "Stream/hsRAMStream.h"

unsigned int plResManager::fNumResMgrs = 0;

plResManager::plResManager(PlasmaVer pv) : fPlasmaVer(pvUnknown) {
    setVer(pv);
    fNumResMgrs++;
    progressFunc = NULL;
}

plResManager::~plResManager() {
    while (ages.size() > 0)
        UnloadAge(ages[0]->getAgeName());
    while (pages.size() > 0)
        UnloadPage(pages[0]->getLocation());
    fNumResMgrs--;
}

void plResManager::setVer(PlasmaVer pv, bool force) {
    if (fPlasmaVer == pv) return;
    if ((fPlasmaVer == pvUnknown) || force)
        fPlasmaVer = pv;
}

PlasmaVer plResManager::getVer() { return fPlasmaVer; }

plKey plResManager::readKey(hsStream* S) {
    if (getVer() != S->getVer())
        throw hsVersionMismatchException(__FILE__, __LINE__);

    if (S->getVer() < pvEoa) {
        if (S->readBool())
            return readUoid(S);
        else
            return plKey();
    } else {
        return readUoid(S);
    }
}

plKey plResManager::readUoid(hsStream* S) {
    if (getVer() != S->getVer())
        throw hsVersionMismatchException(__FILE__, __LINE__);

    plKey k = new plKeyData();
    k->readUoid(S);
    if (!k->getLocation().isValid())
        return plKey();
    return AddKey(k);
}

void plResManager::writeKey(hsStream* S, plKey key) {
    if (getVer() != S->getVer())
        throw hsVersionMismatchException(__FILE__, __LINE__);

    //key->exists = (strcmp(key->objName, "") != 0);
    if (S->getVer() < pvEoa)
        S->writeBool(key.Exists());
    if (key.Exists() || S->getVer() >= pvEoa)
        writeUoid(S, key);
}

void plResManager::writeKey(hsStream* S, hsKeyedObject* ko) {
    writeKey(S, ko->getKey());
}

void plResManager::writeUoid(hsStream* S, plKey key) {
    if (getVer() != S->getVer())
        throw hsVersionMismatchException(__FILE__, __LINE__);

    if (!key.Exists()) {
        plKey empty = new plKeyData();
        empty->writeUoid(S);
    } else {
        key->writeUoid(S);
    }
}

void plResManager::writeUoid(hsStream* S, hsKeyedObject* ko) {
    writeUoid(S, ko->getKey());
}

plKey plResManager::prcParseKey(const pfPrcTag* tag) {
    plKey k = plKeyData::PrcParse(tag);
    if (k.Exists())
        return AddKey(k);
    return k;
}

hsKeyedObject* plResManager::getObject(plKey key) {
    plKey fk = keys.findKey(key);
    if (!fk.Exists()) return NULL;
    return fk->getObj();
}

unsigned int plResManager::countKeys(const plLocation& loc) {
    return keys.countKeys(loc);
}

plPageInfo* plResManager::ReadPage(const char* filename) {
    hsFileStream* S = new hsFileStream();
    if (!S->open(filename, fmRead))
        throw hsFileReadException(__FILE__, __LINE__, filename);
    plPageInfo* page = new plPageInfo();
    page->read(S);

    for (size_t i=0; i<pages.size(); i++) {
        if (pages[i]->getLocation() == page->getLocation()) {
            delete page;
            return pages[i];
        }
    }

    pages.push_back(page);
    setVer(S->getVer(), true);

    S->seek(page->getIndexStart());
    ReadKeyring(S, page->getLocation());
    page->setNumObjects(ReadObjects(S, page->getLocation()));
    S->close();
    delete S;
    return page;
}

plPageInfo* plResManager::ReadPagePrc(const pfPrcTag* root) {
    plPageInfo* page = new plPageInfo();
    page->prcParse(root);

    const pfPrcTag* tag = root->getFirstChild();
    while (tag != NULL) {
        hsKeyedObject* ko = hsKeyedObject::Convert(prcParseCreatable(tag));
        if (ko != NULL)
            ko->getKey()->setObj(ko);
        tag = tag->getNextSibling();
    }

    for (size_t i=0; i<pages.size(); i++) {
        if (pages[i]->getLocation() == page->getLocation()) {
            delete page;
            return pages[i];
        }
    }

    pages.push_back(page);
    return page;
}

void plResManager::WritePage(const char* filename, plPageInfo* page) {
    hsFileStream* S = new hsFileStream();
    S->open(filename, fmWrite);
    S->setVer(getVer());
    if (getVer() >= pvLive) {
        std::vector<short> types = keys.getTypes(page->getLocation());
        page->setClassList(types);
    }
    //keys.sortKeys(page->getLocation());
    page->write(S);
    page->setDataStart(S->pos());
    page->setNumObjects(WriteObjects(S, page->getLocation()));
    page->setIndexStart(S->pos());
    WriteKeyring(S, page->getLocation());
    if (getVer() >= pvEoa)
        page->setChecksum(S->pos());
    else
        page->setChecksum(S->pos() - page->getDataStart());
    page->writeSums(S);
    S->close();
    delete S;
}

void plResManager::WritePagePrc(pfPrcHelper* prc, plPageInfo* page) {
    page->prcWrite(prc); // starts <Page>
    
    // Objects:
    std::vector<short> types = keys.getTypes(page->getLocation());
    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = keys.getKeys(page->getLocation(), types[i]);
        for (unsigned int j=0; j<kList.size(); j++) {
            if (kList[j]->getObj() != NULL)
                kList[j]->getObj()->prcWrite(prc);
        }
    }
    
    prc->closeTag();
}

plPageInfo* plResManager::FindPage(const plLocation& loc) {
    std::vector<plPageInfo*>::iterator pi = pages.begin();
    while (pi != pages.end()) {
        if ((*pi)->getLocation() == loc)
            return *pi;
        pi++;
    }
    return NULL;
}

void plResManager::UnloadPage(const plLocation& loc) {
    keys.delAll(loc);
    DelPage(loc);
}

plAgeInfo* plResManager::ReadAge(const char* filename, bool readPages) {
    plAgeInfo* age = new plAgeInfo();
    age->readFromFile(filename);

    for (std::vector<plAgeInfo*>::iterator it=ages.begin(); it!=ages.end(); ) {
        if ((*it)->getAgeName() == age->getAgeName()) {
            delete *it;
            it = ages.erase(it);
        } else {
            it++;
        }
    }
    
    if (readPages) {
        plString path = plString(filename).beforeLast(PATHSEP);
        if (path.len() > 0)
            path = path + PATHSEP;

        if (age->getNumPages() > 0) {
            plString file = plString::Format("%s_District_%s.prp",
                    age->getAgeName().cstr(),
                    age->getPage(0).fName.cstr());
            FILE* F = fopen((path + file).cstr(), "rb");
            if (F == NULL) {
                setVer(pvEoa, true);
            } else {
                setVer(pvPots, true);
                fclose(F);
            }
        }

        for (size_t i=0; i<age->getNumPages(); i++)
            ReadPage(path + age->getPageFilename(i, getVer()));
        for (size_t i=0; i<age->getNumCommonPages(getVer()); i++)
            ReadPage(path + age->getCommonPageFilename(i, getVer()));
    }

    ages.push_back(age);
    return age;
}

plAgeInfo* plResManager::ReadAgePrc(const pfPrcTag* root) {
    plAgeInfo* age = new plAgeInfo();
    age->prcParse(root);

    for (std::vector<plAgeInfo*>::iterator it=ages.begin(); it!=ages.end(); ) {
        if ((*it)->getAgeName() == age->getAgeName()) {
            delete *it;
            it = ages.erase(it);
        } else {
            it++;
        }
    }

    ages.push_back(age);
    return age;
}

void plResManager::WriteAge(const char* filename, plAgeInfo* age) {
    plString path = filename;
    plString ageName = path.afterLast(PATHSEP);
    if (!ageName.beforeLast('.').empty())
        ageName = ageName.beforeLast('.');
    age->setAgeName(ageName);
    age->writeToFile(path, getVer());
}

void plResManager::WriteAgePrc(pfPrcHelper* prc, plAgeInfo* age) {
    age->prcWrite(prc);
}

plAgeInfo* plResManager::FindAge(const plString& name) {
    std::vector<plAgeInfo*>::iterator ai = ages.begin();
    while (ai != ages.end()) {
        if ((*ai)->getAgeName() == name)
            return *ai;
        ai++;
    }
    return NULL;
}

void plResManager::UnloadAge(const plString& name) {
    std::vector<plAgeInfo*>::iterator ai = ages.begin();
    while (ai != ages.end()) {
        if ((*ai)->getAgeName() == name) {
            plAgeInfo* age = *ai;
            for (size_t i=0; i<age->getNumPages(); i++)
                UnloadPage(age->getPageLoc(i, fPlasmaVer));
            delete age;
            ages.erase(ai);
            ai = ages.end();
        } else {
            ai++;
        }
    }
}

void plResManager::ReadKeyring(hsStream* S, const plLocation& loc) {
    //plDebug::Debug("* Reading Keyring");
    //keys.addPage(loc.pageID);
    unsigned int tCount = S->readInt();
    for (unsigned int i=0; i<tCount; i++) {
        short type = pdUnifiedTypeMap::PlasmaToMapped(S->readShort(), S->getVer()); // objType
        if (S->getVer() >= pvLive) {
            S->readInt();   // # of bytes after this int to next key list
            S->readByte();  // flag?
        }
        unsigned int oCount = S->readInt();
        keys.reserveKeySpace(loc, type, oCount);
        //plDebug::Debug("  * Indexing %d objects of type [%04hX]", oCount, type);
        for (unsigned int j=0; j<oCount; j++) {
            plKey key = new plKeyData();
            key->read(S);

            plKey xkey = keys.findKey(key);
            if (xkey.Exists()) {
                xkey->setFileOff(key->getFileOff());
                xkey->setObjSize(key->getObjSize());
            } else {
                keys.add(key);
            }
        }
    }
}

void plResManager::WriteKeyring(hsStream* S, const plLocation& loc) {
    std::vector<short> types = keys.getTypes(loc, true);
    S->writeInt(types.size());
    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = keys.getKeys(loc, types[i], true);
        S->writeShort(pdUnifiedTypeMap::MappedToPlasma(kList[0]->getType(), S->getVer()));
        unsigned int lenPos = S->pos();
        if (S->getVer() >= pvLive) {
            S->writeInt(0);
            S->writeByte(0);
        }
        S->writeInt(kList.size());
        for (unsigned int j=0; j<kList.size(); j++)
            kList[j]->write(S);
        if (S->getVer() >= pvLive) {
            unsigned int nextPos = S->pos();
            S->seek(lenPos);
            S->writeInt(nextPos - lenPos - 4);
            S->seek(nextPos);
        }
    }
}

unsigned int plResManager::ReadObjects(hsStream* S, const plLocation& loc) {
    std::vector<short> types = keys.getTypes(loc);
    unsigned int nRead = 0;
    
    if (progressFunc != NULL)
        progressFunc(0.0f);

    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = keys.getKeys(loc, types[i]);
        //plDebug::Debug("* Reading %d objects of type [%04hX]%s", kList.size(),
        //               types[i], pdUnifiedTypeMap::ClassName(types[i]));
        for (unsigned int j=0; j<kList.size(); j++) {
            if (kList[j]->getFileOff() <= 0) continue;
            //plDebug::Debug("  * (%d) Reading %s @ 0x%08X", j, kList[j]->getName(),
            //               kList[j]->fileOff);
            S->seek(kList[j]->getFileOff());
            try {
                plCreatable* pCre = ReadCreatable(S, true, kList[j]->getObjSize());
                if (pCre != NULL && pCre->isStub()) {
                    plCreatableStub* stub = (plCreatableStub*)pCre;
                    hsKeyedObjectStub* ko = new hsKeyedObjectStub();
                    hsRAMStream RS(S->getVer());
                    RS.copyFrom(stub->getData(), stub->getLength());
                    ko->read(&RS, this);
                    ko->setStub(stub);
                    kList[j]->setObj(ko);
                } else {
                    kList[j]->setObj(hsKeyedObject::Convert(pCre));
                }
                if (kList[j]->getObj() != NULL) {
                    nRead++;
                    if (kList[j]->getObjSize() != S->pos() - kList[j]->getFileOff()) {
                        plDebug::Warning("[%04hX:%s] Size-Read difference: %d bytes",
                            kList[j]->getType(), kList[j]->getName().cstr(),
                            (int)(kList[j]->getObjSize() -
                                  (S->pos() - kList[j]->getFileOff())));
                        plDebug::Debug("At: 0x%08X (%d bytes)",
                            kList[j]->getFileOff(),
                            kList[j]->getObjSize());
                    }
                }
            } catch (const hsException& e) {
                plDebug::Error("Failed reading %s: %s",
                               kList[j]->toString().cstr(), e.what());
                plDebug::Debug("Failure on line %s:%d", e.File(), e.Line());
                delete kList[j]->getObj();
                kList[j]->setObj(NULL);
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

        if (progressFunc != NULL)
            progressFunc((float)(i+1)/types.size());
    }

    return nRead;
}

unsigned int plResManager::WriteObjects(hsStream* S, const plLocation& loc) {
    std::vector<short> types = keys.getTypes(loc);
    unsigned int nWritten = 0;

    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = keys.getKeys(loc, types[i]);
        //plDebug::Debug("* Writing %d objects of type [%04hX]", kList.size(), types[i]);
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
            } else {
                WriteCreatable(S, NULL);
                plDebug::Warning("Object for %s does not exist", kList[j]->toString().cstr());
            }
            kList[j]->setObjSize(S->pos() - kList[j]->getFileOff());
        }
    }

    return nWritten;
}

plCreatable* plResManager::ReadCreatable(hsStream* S, bool canStub, int stubLen) {
    unsigned short type = S->readShort();
    plCreatable* pCre = plFactory::Create(type, S->getVer());
    if (pCre != NULL) {
        pCre->read(S, this);
    } else if (type != 0x8000) {
        if (canStub) {
            plDebug::Warning("Warning: Type [%04hX]%s is a STUB",
                             pdUnifiedTypeMap::PlasmaToMapped(type, S->getVer()),
                             pdUnifiedTypeMap::ClassName(type, S->getVer()));
            pCre = new plCreatableStub(pdUnifiedTypeMap::PlasmaToMapped(type, S->getVer()), stubLen - 2);
            pCre->read(S, this);
        } else {
            plDebug::Warning("Warning: NOT reading type [%04hX]%s",
                             pdUnifiedTypeMap::PlasmaToMapped(type, S->getVer()),
                             pdUnifiedTypeMap::ClassName(type, S->getVer()));
        }
    }
    return pCre;
}

void plResManager::WriteCreatable(hsStream* S, plCreatable* pCre) {
    if (pCre == NULL) {
        S->writeShort(0x8000);
    } else {
        short classIdx = pCre->ClassIndex(S->getVer());
        if (classIdx == -1) {
            plDebug::Warning("Class [%04hX]%s not available in the requested Plasma version",
                             pCre->ClassIndex(), pCre->ClassName());
            S->writeShort(0x8000);
        } else {
            S->writeShort(classIdx);
            pCre->write(S, this);
        }
    }
}

plCreatable* plResManager::prcParseCreatable(const pfPrcTag* tag) {
    plCreatable* pCre = plFactory::Create(tag->getName());
    if (pCre != NULL)
        pCre->prcParse(tag, this);
    return pCre;
}

plSceneNode* plResManager::getSceneNode(const plLocation& loc) {
    std::vector<plKey> kList = keys.getKeys(loc, kSceneNode);
    if (kList.size() < 1) return NULL;
    return plSceneNode::Convert(kList[0]->getObj());
}

std::vector<plLocation> plResManager::getLocations() {
    std::vector<plLocation> locArr;
    for (size_t i=0; i<pages.size(); i++)
        locArr.push_back(pages[i]->getLocation());
    return locArr;
}

std::vector<short> plResManager::getTypes(const plLocation& loc, bool checkKeys) {
    return keys.getTypes(loc, checkKeys);
}

std::vector<plKey> plResManager::getKeys(const plLocation& loc, short type,
                                         bool checkKeys) {
    return keys.getKeys(loc, type, checkKeys);
}

plKey plResManager::AddKey(plKey key) {
    plKey xkey = keys.findKey(key);
    if (xkey.Exists()) {
        return xkey;
    } else {
        keys.add(key);
        return key;
    }
}

void plResManager::MoveKey(plKey key, const plLocation& to) {
    keys.MoveKey(key, to);
}

void plResManager::AddObject(const plLocation& loc, hsKeyedObject* obj) {
    obj->getKey()->setLocation(loc);
    keys.add(obj->getKey());
}

void plResManager::AddPage(plPageInfo* page) {
    pages.push_back(page);
}

void plResManager::AddAge(plAgeInfo* age) {
    ages.push_back(age);
}

void plResManager::DelObject(plKey obj) {
    keys.del(obj);
}

void plResManager::DelPage(const plLocation& loc) {
    std::vector<plPageInfo*>::iterator pi = pages.begin();
    while (pi != pages.end()) {
        if ((*pi)->getLocation() == loc) {
            plPageInfo* page = *pi;
            delete page;
            pages.erase(pi);
            pi = pages.end();
        } else {
            pi++;
        }
    }
}

void plResManager::DelAge(const plString& name) {
    std::vector<plAgeInfo*>::iterator ai = ages.begin();
    while (ai != ages.end()) {
        if ((*ai)->getAgeName() == name) {
            plAgeInfo* age = *ai;
            delete age;
            ages.erase(ai);
            ai = ages.end();
        } else {
            ai++;
        }
    }
}

void plResManager::ChangeLocation(plLocation from, plLocation to) {
    to.setVer(from.getVer());
    std::vector<plPageInfo*>::iterator pi;
    for (pi = pages.begin(); pi != pages.end(); pi++) {
        if ((*pi)->getLocation() == from)
            (*pi)->setLocation(to);
    }
    keys.ChangeLocation(from, to);
}

ProgressCallback plResManager::SetProgressFunc(ProgressCallback newFunc) {
    ProgressCallback old = progressFunc;
    progressFunc = newFunc;
    return old;
}
