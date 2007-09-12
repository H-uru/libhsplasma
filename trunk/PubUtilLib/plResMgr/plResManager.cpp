#include "plResManager.h"
#include "../../NucleusLib/pnFactory/plFactory.h"
#include "../plJPEG/plJPEG.h"

plResManager* plResManager::inst = NULL;
int plResManager::resManagers = 0;

plResManager::plResManager(PlasmaVer pv) {
    setVer(pv);
    if (inst == NULL)
        inst = this;
    plJPEG::inst = new plJPEG;
    resManagers++;
}

plResManager::~plResManager() {
    resManagers--;
    if (resManagers == 0) {
        while (inst->ages.size() > 0)
            UnloadAge(inst->ages[0]);
        while (inst->pages.size() > 0)
            UnloadPage(inst->pages[0]->getLocation());
        inst = NULL;
    }
}

void plResManager::setVer(PlasmaVer pv, bool mutate) {
    if (ver == pv) return;
    ver = pv;

    //
}

PlasmaVer plResManager::getVer() { return ver; }

plKey plResManager::readKey(hsStream* S) {
    bool exists = (S->getVer() == pvEoa) ? true : S->readBool();
    if (exists) {
        plKey k = new plKeyData();
        if (S->getVer() == pvLive)
            S->readBool();
        k->readUoid(S);
        plKey xkey = inst->keys.findKey(k);
        if (xkey.Exists()) {
            return xkey;
        } else {
            inst->keys.add(k);
            return k;
        }
    } else {
        return plKey();
    }
}

plKey plResManager::readUoidKey(hsStream* S) {
    plKey k = new plKeyData();
    if (S->getVer() == pvLive)
        S->readBool();
    k->readUoid(S);
    plKey xkey = inst->keys.findKey(k);
    if (xkey.Exists())
        k = xkey;
    else
        inst->keys.add(k);
    return k;
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

void plResManager::writeUoidKey(hsStream* S, plKey key) {
    if (S->getVer() == pvLive)
        S->writeBool(true);
    key->writeUoid(S);
}

void plResManager::writeUoidKey(hsStream* S, hsKeyedObject* ko) {
    writeUoidKey(S, ko->getKey());
}

hsKeyedObject* plResManager::getObject(const plKey& key) {
    plKey fk = inst->keys.findKey(key);
    if (!fk.Exists()) return NULL;
    return fk->getObj();
}

plPageInfo* plResManager::ReadPage(const char* filename) {
    hsStream* S = new hsStream();
    setVer(S->getVer());
    if (!S->open(filename, fmRead)) {
        char* buf = new char[256];
        sprintf(buf, "Error reading file: %s", filename);
        throw (const char*)buf;
    }
    plPageInfo* page = new plPageInfo;
    page->read(S);
    inst->pages.push_back(page);
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
        std::vector<short> types = inst->keys.getTypes(page->getLocation().getPageID());
        page->setClassList(types);
        inst->keys.sortKeys(page->getLocation().getPageID());
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
    std::vector<short> types = inst->keys.getTypes(page->getLocation().getPageID());
    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = inst->keys.getKeys(page->getLocation().getPageID(), types[i]);
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
    std::vector<plPageInfo*>::iterator pi = inst->pages.begin();
    while (pi != inst->pages.end()) {
        if ((*pi)->getLocation() == loc) {
            plPageInfo* page = *pi;
            inst->pages.erase(pi);
            delete page;
            pi = inst->pages.end();
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
    inst->ages.push_back(age);
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
    std::vector<plAgeSettings*>::iterator ai = inst->ages.begin();
    while (ai != inst->ages.end()) {
        if ((*ai) == age) {
            inst->ages.erase(ai);
            ai = inst->ages.end();
        } else {
            ai++;
        }
    }
    delete age;
    age = NULL;
}

void plResManager::ReadKeyring(hsStream* S, plLocation& loc) {
    //printf("* Reading Keyring\n");
    //inst->keys.addPage(loc.pageID);
    unsigned int tCount = S->readInt();
    for (unsigned int i=0; i<tCount; i++) {
        short type = S->readShort(); // objType
        if (S->getVer() == pvEoa || S->getVer() == pvLive) {
            S->readInt(); // # of bytes after this int to next key list
            S->readByte(); // flag?
        }
        unsigned int oCount = S->readInt();
        inst->keys.reserveKeySpace(loc.getPageID(), type, oCount);
        //printf("  * Indexing %d objects of type [%04X]\n", oCount, type);
        for (unsigned int j=0; j<oCount; j++) {
            plKey key = new plKeyData();
            key->read(S);
            //if (S->getVer() != pvEoa && S->getVer() != pvLive)
            //    key->setID(j);
            inst->keys.add(key);
            //printf("    * Key %s\n", key->toString());
        }
    }
}

void plResManager::WriteKeyring(hsStream* S, plLocation& loc) {
    std::vector<short> types = inst->keys.getTypes(loc.getPageID());
    S->writeInt(types.size());
    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = inst->keys.getKeys(loc.getPageID(), types[i]);
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
    std::vector<short> types = inst->keys.getTypes(loc.getPageID());
    unsigned int nRead = 0;
    
    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = inst->keys.getKeys(loc.getPageID(), types[i]);
        //printf("* Reading %d objects of type [%04X]%s\n", kList.size(),
        //       types[i], pdUnifiedTypeMap::ClassName(types[i], S->getVer()));
        for (unsigned int j=0; j<kList.size(); j++) {
            if (kList[j]->getFileOff() <= 0) continue;
            //printf("  * (%d) Reading %s @ 0x%08X\n", j, kList[j]->getName(),
            //       kList[j]->fileOff);
            S->seek(kList[j]->getFileOff());
            try {
                kList[j]->setObj((hsKeyedObject*)ReadCreatable(S));
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
    std::vector<short> types = inst->keys.getTypes(loc.getPageID());
    unsigned int nWritten = 0;

    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey> kList = inst->keys.getKeys(loc.getPageID(), types[i]);
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
    plCreatable* pCre = plFactory::Create(S->readShort(), S->getVer());
    if (pCre != NULL)
        pCre->read(S);
    return pCre;
}

void plResManager::WriteCreatable(hsStream* S, plCreatable* pCre) {
    if (pCre == NULL) {
        S->writeShort(0x8000);
    } else {
        S->writeShort(pCre->ClassIndex(S->getVer()));
        pCre->write(S);
    }
}

plSceneNode* plResManager::getSceneNode(plLocation& loc) {
    std::vector<plKey> kList = inst->keys.getKeys(loc.getPageID(), kSceneNode);
    if (kList.size() < 1) return NULL;
    return (plSceneNode*)kList[0]->getObj();
}

