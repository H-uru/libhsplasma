#include "plResManager.h"
#include "../../NucleusLib/pnFactory/plFactory.h"

plResManager* plResManager::inst = NULL;

plResManager::plResManager(PlasmaVer pv) {
    setVer(pv);
    if (inst != NULL)
        throw "Never construct me more than once!";
    inst = this;
}

plResManager::~plResManager() {
    inst = NULL;
    std::map<PageID, plAgeSettings*, PageComparator>::iterator i;
    for (i = ages.begin(); i != ages.end(); i++)
        delete i->second;
}

void plResManager::setVer(PlasmaVer pv, bool mutate) {
    // set this object's ver, and then recurse on all children
    if (ver == pv) return;
    ver = pv;
}

PlasmaVer plResManager::getVer() { return ver; }

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

void plResManager::writeKey(hsStream* S, plKey* key) {
    key->exists = (strcmp(key->objName, "") != 0);
    if (S->getVer() != pvEoa)
        S->writeBool(key->exists);
    if (key->exists || S->getVer() == pvEoa)
        writeKeyBase(S, key);
}

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

hsKeyedObject* plResManager::getObject(plKey& key) {
    plKey* fk = keys.findKey(&key);
    if (!fk) return NULL;
    return fk->objPtr;
}

plAgeSettings* plResManager::ReadPage(const char* filename) {
    hsStream* S = new hsStream();
    setVer(S->getVer());
    S->open(filename, fmRead);
    plAgeSettings* age = new plAgeSettings;
    unsigned int datSize = 0, datOff = 0, idxOff = 0;
    int ver = S->readInt();
    if (ver == 6) {
        age->ver = pvEoa;
        S->setVer(age->ver);
        // Later...
    } else if (ver == 5) {
        unsigned int tempPid = S->readInt();
        age->pageType = S->readShort();
        age->ageName = S->readSafeStr();
        S->readSafeStr(); // District
        age->pageName = S->readSafeStr();
        short maj, min;
        maj = S->readShort();
        min = S->readShort();
        if (maj == 69) age->ver = pvLive;
        else if (min == 11) age->ver = pvPrime;
        else if (min == 12) age->ver = pvPots;
        else throw "Unsupported Plasma version!";
        S->setVer(age->ver);
        age->pageID.setVer(age->ver);
        age->pageID.parse(tempPid);
        setVer(age->ver);
        S->readInt(); // 0
        S->readInt(); // 8
        datSize = S->readInt();
        datOff = S->readInt();
        idxOff = S->readInt();
    } else
        throw "Unsupported page format!";
    ages[age->pageID] = age;

    S->seek(idxOff);
    ReadKeyring(S, age->pageID);
    age->nObjects = ReadObjects(S, age->pageID);
    S->close();
    delete S;
    return age;
}

void plResManager::WritePage(const char* filename) {

}

void plResManager::ReadKeyring(hsStream* S, PageID& pid) {
    unsigned int tCount = S->readInt();
    for (unsigned int i=0; i<tCount; i++) {
        S->readShort(); // objType
        unsigned int oCount = S->readInt();
        for (unsigned int j=0; j<oCount; j++) {
            plKey* key = readKeyBase(S);
            key->fileOff = S->readInt();
            key->objSize = S->readInt();
            keys.add(key);
        }
    }
}

unsigned int plResManager::ReadObjects(hsStream* S, PageID& pid) {
    std::vector<short> types = keys.getTypes(pid);
    unsigned int nRead = 0;
    
    for (unsigned int i=0; i<types.size(); i++) {
        std::vector<plKey*> kList = keys.getKeys(pid, types[i]);
        printf("* Reading %d objects of type [%04X]\n", kList.size(), types[i]);
        for (unsigned int j=0; j<kList.size(); j++) {
            if (kList[j]->fileOff <= 0) continue;
            S->seek(kList[j]->fileOff);
            kList[j]->objPtr = (hsKeyedObject*)plFactory::Create(S->readShort(), ver);
            if (kList[j]->objPtr != NULL) {
                try {
                    printf("Attempting read of [%04X]%s: ",
                            kList[j]->objType, kList[j]->objName);
                    kList[j]->objPtr->read(S);
                    printf("SUCCESS\n");
                    nRead++;
                } catch (const char* e) {
                    printf("%s\n", e);
                } catch (...) {
                    printf("Undefined error\n");
                }
            }
        }
    }

    return nRead;
}

