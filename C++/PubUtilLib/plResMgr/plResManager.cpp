#include "plResManager.h"

plResManager* plResManager::inst = NULL;

plResManager::plResManager(PlasmaVer pv) {
    setVer(pv);
    if (inst != NULL)
        throw "Never construct me more than once!";
    inst = this;
}

plResManager::~plResManager() {
    inst = NULL;
}

void plResManager::setVer(PlasmaVer pv, bool mutate) {
    // set this object's ver, and then recurse on all children
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

