#include "plResManager.h"
#include "../../NucleusLib/pnFactory/plFactory.h"
#include "../../PubUtilLib/plScene/plSceneNode.h"
#include "../plJPEG/plJPEG.h"

plResManager* plResManager::fGlobalResMgr = NULL;
unsigned int plResManager::fNumResMgrs = 0;

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
    if (ver == pv) return;
    ver = pv;

    //
}

PlasmaVer plResManager::getVer() { return ver; }

plKey plResManager::readKey(hsStream* S) {
    bool exists = (S->getVer() == pvEoa) ? true : S->readBool();
    if (exists)
        return readUoid(S);
    else
        return plKey();
}

plKey plResManager::readUoid(hsStream* S) {
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
    //key->exists = (strcmp(key->objName, "") != 0);
    if (S->getVer() != pvEoa)
        S->writeBool(key.Exists());
    if (key.Exists() || S->getVer() == pvEoa) {
        if (S->getVer() == pvLive)
            S->writeBool(key.Exists());
        key->writeUoid(S);
    }
}

void plResManager::writeKey(hsStream* S, hsKeyedObject* ko) {
    writeKey(S, ko->getKey());
}

void plResManager::writeUoid(hsStream* S, plKey key) {
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
    hsStream* S = new hsStream();
    setVer(S->getVer());
    if (!S->open(filename, fmRead))
        throw hsFileReadException(__FILE__, __LINE__, filename);
    //    char* buf = new char[256];
    //    sprintf(buf, "Error reading file: %s", filename);
    //    throw (const char*)buf;
    //}
    plPageInfo* page = new plPageInfo;
    page->read(S);
    pages.push_back(page);
    setVer(S->getVer());

    S->seek(page->getIndexStart());
    ReadKeyring(S, page->getLocation());
    page->nObjects = ReadObjects(S, page->getLocation());
    S->close();
    delete S;
    return page;
}

void plResManager::WritePage(const char* filename, plPageInfo* page) {
    hsStream* S = new hsStream();
    S->open(filename, fmWrite);
    S->setVer(ver);
    if (ver == pvEoa || ver == pvLive) {
        std::vector<short> types = keys.getTypes(page->getLocation().getPageID());
        page->setClassList(types);
        keys.sortKeys(page->getLocation().getPageID());
    }
    page->write(S);
    page->setDataStart(S->pos());
    page->nObjects = WriteObjects(S, page->getLocation());
    page->setIndexStart(S->pos());
    WriteKeyring(S, page->getLocation());
    if (ver == pvEoa)
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

void plResManager::UnloadPage(plLocation& loc) {
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

plAgeSettings* plResManager::ReadAge(const char* filename) {
    plEncryptedStream* S = new plEncryptedStream();
    S->open(filename, fmRead);

    plAgeSettings* age = new plAgeSettings;
    char* afName;
    char* pageFileName;
    const char* BuiltIns[2] = { "BuiltIn", "Textures" };
    for (int i=0; i<2; i++) {
        pageFileName = new char[256];
        strcpy(pageFileName, filename);
        afName = strrchr(pageFileName, '.');
        sprintf(afName, "_District_%s.prp", BuiltIns[i]);
        plPageInfo* page = ReadPage(pageFileName);
        age->pages.push_back(page);
        delete[] pageFileName;
    }

    while (!S->eof()) {
        plString ln = S->readLine();
        plString field = ln.beforeFirst('=').toLower();
        plString value = ln.afterFirst('=');
        if (field == "startdatetime") {
            age->startDateTime = value.toInt();
        } else if (field == "daylength") {
            age->dayLength = value.toInt();
        } else if (field == "maxcapacity") {
            age->maxCapacity = value.toInt();
        } else if (field == "lingertime") {
            age->lingerTime = value.toInt();
        } else if (field == "sequenceprefix") {
            age->sequencePrefix = value.toInt();
        } else if (field == "releaseversion") {
            age->releaseVersion = value.toInt();
        } else if (field == "page") {
            plString pageName = value.beforeFirst(',');
            value = value.afterFirst(',');
            //hsUint32 pageIdx = value.beforeFirst(',').toUInt();
            value = value.afterFirst(',');
            hsUint32 pageFlag = value.beforeFirst(',').toUInt();
            pageFileName = new char[256];
            strcpy(pageFileName, filename);
            afName = strrchr(pageFileName, '.');
            sprintf(afName, "_District_%s.prp", pageName.cstr());
            plPageInfo* page = ReadPage(pageFileName);
            page->holdFlag = pageFlag != 0;
            age->pages.push_back(page);
            delete[] pageFileName;
        }
    }

    S->close();
    delete S;
    ages.push_back(age);
    return age;
}

void plResManager::WriteAge(const char* filename, plAgeSettings* age) {
    plEncryptedStream* S = new plEncryptedStream();
    if (ver == pvEoa) S->setVer(pvEoa);
    else S->setVer(pvPrime);
    S->open(filename, fmCreate);

    char* lnBuf = new char[4096];
    sprintf(lnBuf, "StartDateTime=%d", age->startDateTime);
    S->writeLine(lnBuf);
    sprintf(lnBuf, "DayLength=%d", age->dayLength);
    S->writeLine(lnBuf);
    sprintf(lnBuf, "MaxCapacity=%d", age->maxCapacity);
    S->writeLine(lnBuf);
    sprintf(lnBuf, "LingerTime=%d", age->lingerTime);
    S->writeLine(lnBuf);
    sprintf(lnBuf, "SequencePrefix=%d", age->sequencePrefix);
    S->writeLine(lnBuf);
    sprintf(lnBuf, "ReleaseVersion=%d", age->releaseVersion);
    S->writeLine(lnBuf);
    for (unsigned int i=0; i<age->pages.size(); i++) {
        if (age->pages[i]->holdFlag)
            sprintf(lnBuf, "Page=%s,%d,%d", age->pages[i]->getPage(),
                    age->pages[i]->getLocation().getPageID().getPageNum(), 1);
        else
            sprintf(lnBuf, "Page=%s,%d", age->pages[i]->getPage(),
                    age->pages[i]->getLocation().getPageID().getPageNum());
        S->writeLine(lnBuf);
    }

    S->close();
    delete S;
}

void plResManager::UnloadAge(plAgeSettings* age) {
    for (unsigned int i=0; i<age->pages.size(); i++)
        UnloadPage(age->pages[i]->getLocation());
    std::vector<plAgeSettings*>::iterator ai = ages.begin();
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

void plResManager::ReadKeyring(hsStream* S, plLocation& loc) {
    //printf("* Reading Keyring\n");
    //keys.addPage(loc.pageID);
    unsigned int tCount = S->readInt();
    for (unsigned int i=0; i<tCount; i++) {
        short type = S->readShort(); // objType
        if (S->getVer() == pvEoa || S->getVer() == pvLive) {
            S->readInt(); // # of bytes after this int to next key list
            S->readByte(); // flag?
        }
        unsigned int oCount = S->readInt();
        keys.reserveKeySpace(loc.getPageID(), type, oCount);
        //printf("  * Indexing %d objects of type [%04X]\n", oCount, type);
        for (unsigned int j=0; j<oCount; j++) {
            plKey key = new plKeyData();
            key->read(S);
            //if (S->getVer() != pvEoa && S->getVer() != pvLive)
            //    key->setID(j);
            keys.add(key);
            //printf("    * Key %s\n", key->toString());
        }
    }
}

void plResManager::WriteKeyring(hsStream* S, plLocation& loc) {
    std::vector<short> types = keys.getTypes(loc.getPageID());
    S->writeInt(types.size());
    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = keys.getKeys(loc.getPageID(), types[i]);
        if (kList.size() <= 0) continue;
        S->writeShort(pdUnifiedTypeMap::MappedToPlasma(kList[0]->getType(), S->getVer()));
        unsigned int lenPos = S->pos();
        if (S->getVer() == pvEoa || S->getVer() == pvLive) {
            S->writeInt(0);
            S->writeByte(0);
        }
        S->writeInt(kList.size());
        for (unsigned int j=0; j<kList.size(); j++)
            kList[j]->write(S);
        if (S->getVer() == pvEoa || S->getVer() == pvLive) {
            unsigned int nextPos = S->pos();
            S->seek(lenPos);
            S->writeInt(nextPos - lenPos - 4);
            S->seek(nextPos);
        }
    }
}

unsigned int plResManager::ReadObjects(hsStream* S, plLocation& loc) {
    //printf("* Reading Objects\n");
    std::vector<short> types = keys.getTypes(loc.getPageID());
    unsigned int nRead = 0;
    
    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = keys.getKeys(loc.getPageID(), types[i]);
        //printf("* Reading %d objects of type [%04X]%s\n", kList.size(),
        //       types[i], pdUnifiedTypeMap::ClassName(types[i], S->getVer()));
        for (unsigned int j=0; j<kList.size(); j++) {
            if (kList[j]->getFileOff() <= 0) continue;
            //printf("  * (%d) Reading %s @ 0x%08X\n", j, kList[j]->getName(),
            //       kList[j]->fileOff);
            S->seek(kList[j]->getFileOff());
            try {
                kList[j]->setObj(hsKeyedObject::Convert(ReadCreatable(S)));
                if (kList[j]->getObj() != NULL) {
                    nRead++;
                    if (kList[j]->getObjSize() != S->pos() - kList[j]->getFileOff())
                        printf("[%04X:%s] Size-Read difference: %d bytes\n",
                               kList[j]->getType(), kList[j]->getName().cstr(),
                               (signed int)(kList[j]->getObjSize() -
                                            (S->pos() - kList[j]->getFileOff())));
                }
            } catch (const char* e) {
                printf("Failed reading %s: %s\n",
                        kList[j]->toString().cstr(), e);
                delete kList[j]->getObj();
                kList[j]->setObj(NULL);
            } catch (...) {
                printf("Undefined error reading %s\n",
                        kList[j]->toString().cstr());
                delete kList[j]->getObj();
                kList[j]->setObj(NULL);
            }
        }
    }

    return nRead;
}

unsigned int plResManager::WriteObjects(hsStream* S, plLocation& loc) {
    std::vector<short> types = keys.getTypes(loc.getPageID());
    unsigned int nWritten = 0;

    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = keys.getKeys(loc.getPageID(), types[i]);
        //printf("* Writing %d objects of type [%04X]\n", kList.size(), types[i]);
        for (unsigned int j=0; j<kList.size(); j++) {
            kList[j]->setFileOff(S->pos());
            kList[j]->setID(j);
            if (kList[j]->getObj() != NULL) {
                try {
                    WriteCreatable(S, kList[j]->getObj());
                    nWritten++;
                } catch (const char* e) {
                    printf("Failed writing %s: %s\n",
                           kList[j]->toString().cstr(), e);
                } catch (...) {
                    printf("Undefined error writing %s\n",
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
        printf("Warning: NOT reading object of type [%04X]\n", type);
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

plSceneNode* plResManager::getSceneNode(plLocation& loc) {
    std::vector<plKey> kList = keys.getKeys(loc.getPageID(), kSceneNode);
    if (kList.size() < 1) return NULL;
    return (plSceneNode*)kList[0]->getObj();
}

