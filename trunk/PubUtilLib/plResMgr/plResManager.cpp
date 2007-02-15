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
    for (unsigned int i=0; i<pages.size(); i++) {
        delete[] pages[i]->ageName;
        delete[] pages[i]->pageName;
        delete pages[i];
    }
}

void plResManager::setVer(PlasmaVer pv, bool mutate) {
    if (ver == pv) return;
    ver = pv;

    //
}

PlasmaVer plResManager::getVer() { return ver; }

plKey* plResManager::readKeyBase(hsStream* S) {
    plKey* k = new plKey();
    k->flags = S->readByte();
    k->pageID.setVer(S->getVer());
    k->pageID.read(S);
    k->pageType = S->readShort();
    if ((k->flags & 0x02) || S->getVer() == pvEoa)
        k->extra1 = S->readByte();
    else k->extra1 = 0;
    k->objType = S->readShort();
    if (S->getVer() == pvEoa || S->getVer() == pvLive)
        k->objID = S->readInt();
    k->objName = S->readSafeStr();
    if ((k->flags & 0x01) && S->getVer() != pvEoa) {
        k->someID = S->readInt();
        k->clientID = S->readInt();
    } else {
        k->someID = k->clientID = 0;
    }
    if ((k->flags & 0x06) && S->getVer() == pvEoa)
        k->eoaExtra2 = S->readByte();
    else k->eoaExtra2 = 0;
    k->exists = true;
    return k;
}

plKey* plResManager::readKey(hsStream* S) {
    plKey* k = new plKey();
    k->exists = true;
    if (S->getVer() != pvEoa)
        k->exists = S->readBool();
    if (k->exists) {
        k = readKeyBase(S);
        if (plKey* xkey = keys.findKey(k)) {
            delete k;
            k = xkey;
        } else {
            keys.add(k);
        }
    }
    return k;
}

plKey* plResManager::readRealKey(hsStream* S) {
    plKey* k = new plKey();
    k->exists = true;
    k = readKeyBase(S);
    if (plKey* xkey = keys.findKey(k)) {
        delete k;
        k = xkey;
    } else {
        keys.add(k);
    }
    return k;
}

void plResManager::writeKeyBase(hsStream* S, plKey* key) {
    S->writeByte(key->flags);
    key->pageID.setVer(S->getVer(), true);
    key->pageID.write(S);
    S->writeShort(key->pageType);
    if ((key->flags & 0x02) || S->getVer() == pvEoa)
        S->writeByte(key->extra1);
    S->writeShort(key->objType);
    if (S->getVer() == pvEoa || S->getVer() == pvLive)
        S->writeInt(key->objID);
    S->writeSafeStr(key->objName);
    if ((key->flags & 0x01) && S->getVer() != pvEoa) {
        S->writeInt(key->someID);
        S->writeInt(key->clientID);
    }
    if ((key->flags & 0x06) && S->getVer() == pvEoa)
        S->writeByte(key->eoaExtra2);
}

void plResManager::writeKey(hsStream* S, plKey* key) {
    //key->exists = (strcmp(key->objName, "") != 0);
    if (S->getVer() != pvEoa)
        S->writeBool(key->exists);
    if (key->exists || S->getVer() == pvEoa)
        writeKeyBase(S, key);
}

void plResManager::writeRealKey(hsStream* S, plKey* key) {
    writeKeyBase(S, key);
}

hsKeyedObject* plResManager::getObject(plKey& key) {
    plKey* fk = keys.findKey(&key);
    if (!fk) return NULL;
    return fk->objPtr;
}

plPageSettings* plResManager::ReadPage(const char* filename) {
    hsStream* S = new hsStream();
    setVer(S->getVer());
    S->open(filename, fmRead);
    plPageSettings* page = new plPageSettings;
    short prpver = S->readShort();
    if (prpver == 6) {
        page->ver = pvEoa;
        S->setVer(page->ver);
        page->pageID.setVer(page->ver);
        setVer(page->ver);
        unsigned short nTypes = S->readShort();
        S->skip(nTypes * 4); // Type info table...
        page->pageID.read(S);
        page->pageType = S->readByte();
        page->ageName = S->readSafeStr();
        page->pageName = S->readSafeStr();
    } else if (prpver == 5) {
        S->readShort(); // prpver is 32-bits in Uru PRPs
        unsigned int tempPid = S->readInt();
        page->pageType = S->readShort();
        page->ageName = S->readSafeStr();
        delete[] S->readSafeStr(); // District
        page->pageName = S->readSafeStr();
        short maj, min;
        maj = S->readShort();
        min = S->readShort();
        if (maj == 69) page->ver = pvLive;
        else if (min == 11) page->ver = pvPrime;
        else if (min == 12) page->ver = pvPots;
        else throw "Unsupported Plasma version!";
        S->setVer(page->ver);
        page->pageID.setVer(page->ver);
        page->pageID.parse(tempPid);
        setVer(page->ver);
        S->readInt(); // 0
        S->readInt(); // 8
    } else
        throw "Unsupported page format!";
    pages.push_back(page);
        
    /*unsigned int datSize =*/ S->readInt();
    /*unsigned int datOff =*/ S->readInt();
    unsigned int idxOff = S->readInt();

    S->seek(idxOff);
    ReadKeyring(S, page->pageID);
    page->nObjects = ReadObjects(S, page->pageID);
    S->close();
    delete S;
    return page;
}

void plResManager::WritePage(const char* filename, plPageSettings* page) {
    hsStream* S = new hsStream();
    page->pageID.setVer(ver, true);
    S->open(filename, fmWrite);
    S->setVer(ver, true);
    if (ver == pvEoa) {
        S->writeShort(6);
        throw "Incomplete";
        // unsigned short nTypes = S->readShort();
        //S->skip(nTypes * 4); // Type info table...
        page->pageID.write(S);
        S->writeByte(page->pageType);
        S->writeSafeStr(page->ageName);
        S->writeSafeStr(page->pageName);
    } else {
        S->writeInt(5);
        page->pageID.write(S);
        S->writeShort(page->pageType);
        S->writeSafeStr(page->ageName);
        S->writeSafeStr("District");
        S->writeSafeStr(page->pageName);
        short maj=-1, min=-1;
        if (ver == pvLive) {
            maj = 69;
            min = 3;
        } else if (ver == pvPrime) {
            maj = 63;
            min = 11;
        } else if (ver == pvPots) {
            maj = 63;
            min = 12;
        }
        S->writeShort(maj);
        S->writeShort(min);
        S->writeInt(0);
        S->writeInt(8);
    }
    
    unsigned int datSize = 0, datOff = 0, idxOff = 0;
    S->writeInt(0);
    S->writeInt(0);
    S->writeInt(0);
    datOff = S->pos();
    page->nObjects = WriteObjects(S, page->pageID);
    idxOff = S->pos();
    WriteKeyring(S, page->pageID);
    datSize = S->pos() - datOff;
    S->seek(datOff-12);
    S->writeInt(datSize);
    S->writeInt(datOff);
    S->writeInt(idxOff);
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
            plPageSettings* page = ReadPage(pageFileName);
            page->loadFlags = (pageFlag ? atoi(&pageFlag[1]) : 0);
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
        if (age->pages[i]->loadFlags == 0)
            sprintf(lnBuf, "Page=%s,%d", age->pages[i]->pageName,
                                 age->pages[i]->pageID.getPageNum());
        else
            sprintf(lnBuf, "Page=%s,%d,%d", age->pages[i]->pageName,
                                 age->pages[i]->pageID.getPageNum(), 1);
        S->writeLine(lnBuf);
    }

    S->close();
    delete S;
}

void plResManager::ReadKeyring(hsStream* S, PageID& pid) {
    unsigned int tCount = S->readInt();
    for (unsigned int i=0; i<tCount; i++) {
        S->readShort(); // objType
        if (S->getVer() == pvEoa) {
            S->readInt(); // dataSize
            S->readByte(); // flag
        }
        unsigned int oCount = S->readInt();
        for (unsigned int j=0; j<oCount; j++) {
            plKey* key = readKeyBase(S);
            key->fileOff = S->readInt();
            key->objSize = S->readInt();
            keys.add(key);
        }
    }
}

void plResManager::WriteKeyring(hsStream* S, PageID& pid) {
    std::vector<short> types = keys.getTypes(pid);
    S->writeInt(types.size());
    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey*> kList = keys.getKeys(pid, types[i]);
        if (kList.size() <= 0) continue;
        S->writeShort(kList[0]->objType);
        if (S->getVer() == pvEoa) {
            throw "Incomplete";
        }
        S->writeInt(kList.size());
        for (unsigned int j=0; j<kList.size(); j++) {
            writeKeyBase(S, kList[j]);
            S->writeInt(kList[j]->fileOff);
            S->writeInt(kList[j]->objSize);
        }
    }
}

unsigned int plResManager::ReadObjects(hsStream* S, PageID& pid) {
    std::vector<short> types = keys.getTypes(pid);
    unsigned int nRead = 0;
    
    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey*> kList = keys.getKeys(pid, types[i]);
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
                    printf("Failed reading [%04X]%s: %s\n",
                           kList[j]->objType, kList[j]->objName, e);
                    delete kList[j]->objPtr;
                    kList[j]->objPtr = NULL;
                } catch (...) {
                    printf("Undefined error reading [%04X]%s\n",
                           kList[j]->objType, kList[j]->objName);
                    delete kList[j]->objPtr;
                    kList[j]->objPtr = NULL;
                }
            }
        }
    }

    return nRead;
}

unsigned int plResManager::WriteObjects(hsStream* S, PageID& pid) {
    std::vector<short> types = keys.getTypes(pid);
    unsigned int nWritten = 0;

    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey*> kList = keys.getKeys(pid, types[i]);
        //printf("* Writing %d objects of type [%04X]\n", kList.size(), types[i]);
        for (unsigned int j=0; j<kList.size(); j++) {
            kList[j]->fileOff = S->pos();
            kList[j]->objID = j;
            if (kList[j]->objPtr != NULL) {
                try {
                    S->writeShort(kList[j]->objType);
                    kList[j]->objPtr->write(S);
                    nWritten++;
                } catch (const char* e) {
                    printf("Failed writing [%04X]%s: %s\n",
                           kList[j]->objType, kList[j]->objName, e);
                } catch (...) {
                    printf("Undefined error writing [%04X]%s\n",
                           kList[j]->objType, kList[j]->objName);
                }
            }
            kList[j]->objSize = S->pos() - kList[j]->fileOff;
        }
    }

    return nWritten;
}

plSceneNode* plResManager::getSceneNode(PageID &pid) {
    std::vector<plKey*> kList = keys.getKeys(pid, 0x0000);
    if (kList.size() < 1) return NULL;
    return (plSceneNode*)kList[0]->objPtr;
}

