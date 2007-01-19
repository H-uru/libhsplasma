#include <stdlib.h>
#include <string.h>
#include "../../PlasmaConstants.h"
#include "plKey.h"

plKey::plKey() : flags(0), pageType(PAGE_NORMAL), extra1(0), objType(0),
                 objID(0), objName(NULL), someID(0), clientID(0), eoaExtra2(0),
                 exists(true) {
    pageID = new PageID();
}

plKey::plKey(plKey * init) {
    flags = init->flags;
    pageID = init->pageID;
    init->pageID->Ref();
    pageType = init->pageType;
    extra1 = init->extra1;
    objType = init->objType;
    objID = init->objID;
    objName = init->objName;
    someID = init->someID;
    clientID = init->clientID;
    eoaExtra2 = init->eoaExtra2;
    exists = init->exists;
}

plKey::~plKey() {
    if (objName)
        delete objName;
    if (pageID)
        pageID->UnRef();
}

PageID * plKey::getPageID() {
    return pageID;
}

short plKey::getPageType() { return pageType; }
short plKey::getObjType()  { return objType;  }
int plKey::getObjID()      { return objID;    }

char* plKey::getObjName() {
    char* name = new char[strlen(objName)+1];
    strcpy(name, objName);
    return name;
}

void plKey::setPageID(PageID * pid) {
    if (pageID) pageID->UnRef();
    pageID = pid;
    pid->Ref();
}

void plKey::setPageType(short pt) { pageType = pt; }
void plKey::setObjType(short ot)  { objType = ot;  }
void plKey::setObjID(int id)      { objID = id;    }

void plKey::setObjName(const char* name) {
    if (objName) free(objName);
    objName = new char[strlen(name)+1];
    strcpy(objName, name);
}

bool plKey::operator==(plKey &other) {
    return ((*pageID) == (*other.pageID) && objType == other.objType &&
            (strcmp(objName, other.objName) == 0));
}

void plKey::read(hsStream *S) {
    flags = S->readByte();
    pageID->read(S);
    pageType = S->readShort();
    if ((flags & 0x02) || S->getVer() == pvEoa)
        extra1 = S->readByte();
    else extra1 = 0;
    objType = S->readShort();
    if (S->getVer() == pvEoa || S->getVer() == pvLive)
        objID = S->readInt();
    objName = S->readSafeStr();
    if ((flags & 0x01) && S->getVer() != pvEoa) {
        someID = S->readInt();
        clientID = S->readInt();
    } else {
        someID = clientID = 0;
    }
    if ((flags & 0x06) && S->getVer() == pvEoa)
        eoaExtra2 = S->readByte();
    else eoaExtra2 = 0;
    exists = true;
}

void plKey::write(hsStream *S) {
    S->writeByte(flags);
    pageID->write(S);
    S->writeShort(pageType);
    if ((flags & 0x02) || S->getVer() == pvEoa)
        S->writeByte(extra1);
    S->writeShort(objType);
    if (S->getVer() == pvEoa || S->getVer() == pvLive)
        S->writeInt(objID);
    S->writeSafeStr(objName);
    if ((flags & 0x01) && S->getVer() != pvEoa) {
        S->writeInt(someID);
        S->writeInt(clientID);
    }
    if ((flags & 0x06) && S->getVer() == pvEoa)
        S->writeByte(eoaExtra2);
}

void plKey::readRef(hsStream *S) {
    exists = true;
    if (S->getVer() != pvEoa)
        exists = S->readBool();
    if (exists) read(S);
}

void plKey::writeRef(hsStream *S) {
    if (S->getVer() != pvEoa)
        S->writeBool(exists);
    if (exists) write(S);
}

