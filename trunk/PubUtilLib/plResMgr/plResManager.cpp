#include "plResManager.h"
#include "../../NucleusLib/pnFactory/plFactory.h"
#include "../plJPEG/plJPEG.h"

plResManager* plResManager::inst = NULL;

plResManager::plResManager(PlasmaVer pv) {
    setVer(pv);
    if (inst != NULL)
        throw "Never construct me more than once!";
    inst = this;
    plJPEG::inst = new plJPEG;
}

plResManager::~plResManager() {
    inst = NULL;
    for (unsigned int i=0; i<pages.size(); i++)
        delete pages[i];
}

void plResManager::setVer(PlasmaVer pv, bool mutate) {
    if (ver == pv) return;
    ver = pv;

    //
}

PlasmaVer plResManager::getVer() { return ver; }

plKey* plResManager::readKey(hsStream* S) {
    plKey* k = new plKey();
    k->exists = true;
    if (S->getVer() != pvEoa)
        k->exists = S->readBool();
    if (k->exists) {
        k->readUoid(S);
        if (plKey* xkey = keys.findKey(k)) {
            delete k;
            k = xkey;
        } else {
            keys.add(k);
        }
    }
    return k;
}

plKey* plResManager::readUoidKey(hsStream* S) {
    plKey* k = new plKey();
    k->exists = true;
    k->readUoid(S);
    if (plKey* xkey = keys.findKey(k)) {
        delete k;
        k = xkey;
    } else {
        keys.add(k);
    }
    return k;
}

void plResManager::writeKey(hsStream* S, plKey* key) {
    //key->exists = (strcmp(key->objName, "") != 0);
    if (S->getVer() != pvEoa)
        S->writeBool(key->exists);
    if (key->exists || S->getVer() == pvEoa)
        key->writeUoid(S);
}

void plResManager::writeUoidKey(hsStream* S, plKey* key) {
    key->writeUoid(S);
}

hsKeyedObject* plResManager::getObject(plKey& key) {
    plKey* fk = keys.findKey(&key);
    if (!fk) return NULL;
    return fk->objPtr;
}

plPageInfo* plResManager::ReadPage(const char* filename) {
    hsStream* S = new hsStream();
    setVer(S->getVer());
    if (!S->open(filename, fmRead))
        throw "Error reading file!";
    plPageInfo* page = new plPageInfo;
    page->read(S);
    pages.push_back(page);

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
    S->setVer(ver, true);
    page->write(S);
    page->setDataStart(S->pos());
    page->nObjects = WriteObjects(S, page->getLocation());
    page->setIndexStart(S->pos());
    WriteKeyring(S, page->getLocation());
    page->setChecksum(S->pos() - page->getDataStart());
    page->writeSums(S);
    S->close();
    delete S;
}

plAgeSettings* plResManager::ReadAge(const char* filename) {
    plEncryptedStream* S = new plEncryptedStream();
    S->open(filename, fmRead);

    char* ln;
    plAgeSettings* age = new plAgeSettings;
    while (!S->eof()) {
        ln = S->readLine();
        if (strncmp(ln, "StartDateTime=", 14) == 0) {
            age->startDateTime = atoi(&ln[14]);
        } else if (strncmp(ln, "DayLength=", 10) == 0) {
            age->dayLength = atoi(&ln[10]);
        } else if (strncmp(ln, "MaxCapacity=", 12) == 0) {
            age->maxCapacity = atoi(&ln[12]);
        } else if (strncmp(ln, "LingerTime=", 11) == 0) {
            age->lingerTime = atoi(&ln[11]);
        } else if (strncmp(ln, "SequencePrefix=", 15) == 0) {
            age->sequencePrefix = atoi(&ln[15]);
        } else if (strncmp(ln, "ReleaseVersion=", 15) == 0) {
            age->releaseVersion = atoi(&ln[15]);
        } else if (strncmp(ln, "Page=", 5) == 0) {
            char* pageName = &ln[5];
            char* pageIdx = strchr(pageName, ',');
            char* pageFlag = strchr(pageIdx, ',');
            char* pageFileName = new char[256];
            strcpy(pageFileName, filename);
            char* afName = strrchr(pageFileName, '.');
            sprintf(afName, "_District_%*s.prp", pageIdx - pageName, pageName);
            plPageInfo* page = ReadPage(pageFileName);
            page->holdFlag = (pageFlag ? atoi(&pageFlag[1]) != 0 : false);
            age->pages.push_back(page);
            delete[] pageFileName;
        }
    }

    S->close();
    delete S;
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
                    age->pages[i]->getLocation().pageID.getPageNum(), 1);
        else
            sprintf(lnBuf, "Page=%s,%d", age->pages[i]->getPage(),
                    age->pages[i]->getLocation().pageID.getPageNum());
        S->writeLine(lnBuf);
    }

    S->close();
    delete S;
}

void plResManager::ReadKeyring(hsStream* S, plLocation& loc) {
    unsigned int tCount = S->readInt();
    for (unsigned int i=0; i<tCount; i++) {
        short type = S->readShort(); // objType
        if (S->getVer() == pvEoa) {
            S->readInt(); // dataSize
            S->readByte(); // flag
        }
        unsigned int oCount = S->readInt();
        for (unsigned int j=0; j<oCount; j++) {
            plKey* key = new plKey();
            key->read(S);
            keys.add(key);
        }
    }
}

void plResManager::WriteKeyring(hsStream* S, plLocation& loc) {
    std::vector<short> types = keys.getTypes(loc.pageID);
    S->writeInt(types.size());
    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey*> kList = keys.getKeys(loc.pageID, types[i]);
        if (kList.size() <= 0) continue;
        S->writeShort(kList[0]->getType());
        if (S->getVer() == pvEoa) {
            throw "Incomplete";
        }
        S->writeInt(kList.size());
        for (unsigned int j=0; j<kList.size(); j++)
            kList[j]->write(S);
    }
}

unsigned int plResManager::ReadObjects(hsStream* S, plLocation& loc) {
    std::vector<short> types = keys.getTypes(loc.pageID);
    unsigned int nRead = 0;
    
    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey*> kList = keys.getKeys(loc.pageID, types[i]);
        //printf("* Reading %d objects of type [%04X]\n", kList.size(), types[i]);
        for (unsigned int j=0; j<kList.size(); j++) {
            if (kList[j]->fileOff <= 0) continue;
            S->seek(kList[j]->fileOff);
            kList[j]->objPtr = (hsKeyedObject*)plFactory::Create(S->readShort(), ver);
            if (kList[j]->objPtr != NULL) {
                try {
                    kList[j]->objPtr->read(S);
                    nRead++;
                } catch (const char* e) {
                    printf("Failed reading %s: %s\n",
                           kList[j]->toString(), e);
                    delete kList[j]->objPtr;
                    kList[j]->objPtr = NULL;
                } catch (...) {
                    printf("Undefined error reading %s\n",
                           kList[j]->toString());
                    delete kList[j]->objPtr;
                    kList[j]->objPtr = NULL;
                }
            }
        }
    }

    return nRead;
}

unsigned int plResManager::WriteObjects(hsStream* S, plLocation& loc) {
    std::vector<short> types = keys.getTypes(loc.pageID);
    unsigned int nWritten = 0;

    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey*> kList = keys.getKeys(loc.pageID, types[i]);
        //printf("* Writing %d objects of type [%04X]\n", kList.size(), types[i]);
        for (unsigned int j=0; j<kList.size(); j++) {
            kList[j]->fileOff = S->pos();
            kList[j]->setID(j);
            if (kList[j]->objPtr != NULL) {
                try {
                    S->writeShort(kList[j]->getType());
                    kList[j]->objPtr->write(S);
                    nWritten++;
                } catch (const char* e) {
                    printf("Failed writing %s: %s\n",
                           kList[j]->toString(), e);
                } catch (...) {
                    printf("Undefined error writing %s\n",
                           kList[j]->toString());
                }
            }
            kList[j]->objSize = S->pos() - kList[j]->fileOff;
        }
    }

    return nWritten;
}

plSceneNode* plResManager::getSceneNode(plLocation& loc) {
    std::vector<plKey*> kList = keys.getKeys(loc.pageID, 0x0000);
    if (kList.size() < 1) return NULL;
    return (plSceneNode*)kList[0]->objPtr;
}

