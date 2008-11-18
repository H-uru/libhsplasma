#include "plAgeLinkInfo.h"
#include "Util/hsBitVector.h"

/* plAgeInfoStruct */
plAgeInfoStruct::plAgeInfoStruct()
               : fFlags(0), fAgeSequenceNumber(0), fAgeLanguage(0) { }
plAgeInfoStruct::~plAgeInfoStruct() { }

IMPLEMENT_CREATABLE(plAgeInfoStruct, kAgeInfoStruct, plCreatable)

void plAgeInfoStruct::read(hsStream* S, plResManager* mgr) {
    fFlags = S->readByte();
    if (fFlags & kHasAgeFilename) {
        size_t len = S->readShort();
        fAgeFilename = S->readStr(len);
    }
    if (fFlags & kHasAgeInstanceName) {
        size_t len = S->readShort();
        fAgeInstanceName = S->readStr(len);
    }
    if (fFlags & kHasAgeInstanceGuid) {
        fAgeInstanceGuid.read(S);
    }
    if (fFlags & kHasAgeUserDefinedName) {
        size_t len = S->readShort();
        fAgeUserDefinedName = S->readStr(len);
    }
    if (fFlags & kHasAgeSequenceNumber) {
        fAgeSequenceNumber = S->readInt();
    }
    if (fFlags & kHasAgeDescription) {
        size_t len = S->readShort();
        fAgeDescription = S->readStr(len);
    }
    if (fFlags & kHasAgeLanguage) {
        fAgeLanguage = S->readInt();
    }
}

void plAgeInfoStruct::write(hsStream* S, plResManager* mgr) {
    S->writeByte(fFlags);
    if (fFlags & kHasAgeFilename) {
        S->writeShort(fAgeFilename.len());
        S->writeStr(fAgeFilename);
    }
    if (fFlags & kHasAgeInstanceName) {
        S->writeShort(fAgeInstanceName.len());
        S->writeStr(fAgeInstanceName);
    }
    if (fFlags & kHasAgeInstanceGuid) {
        fAgeInstanceGuid.write(S);
    }
    if (fFlags & kHasAgeUserDefinedName) {
        S->writeShort(fAgeUserDefinedName.len());
        S->writeStr(fAgeUserDefinedName);
    }
    if (fFlags & kHasAgeSequenceNumber) {
        S->writeInt(fAgeSequenceNumber);
    }
    if (fFlags & kHasAgeDescription) {
        S->writeShort(fAgeDescription.len());
        S->writeStr(fAgeDescription);
    }
    if (fFlags & kHasAgeLanguage) {
        S->writeInt(fAgeLanguage);
    }
}

void plAgeInfoStruct::prcParse(const pfPrcTag* tag, plResManager* mgr) {
    clear();
    plCreatable::prcParse(tag, mgr);
}

void plAgeInfoStruct::IPrcWrite(pfPrcHelper* prc) {
    if (fFlags & kHasAgeFilename) {
        prc->startTag("AgeFilename");
        prc->writeParam("value", fAgeFilename);
        prc->endTag(true);
    }
    if (fFlags & kHasAgeInstanceName) {
        prc->startTag("InstanceName");
        prc->writeParam("value", fAgeInstanceName);
        prc->endTag(true);
    }
    if (fFlags & kHasAgeInstanceGuid) {
        prc->writeSimpleTag("AgeInstanceGUID");
        fAgeInstanceGuid.prcWrite(prc);
        prc->closeTag();
    }
    if (fFlags & kHasAgeUserDefinedName) {
        prc->startTag("UserDefinedName");
        prc->writeParam("value", fAgeUserDefinedName);
        prc->endTag(true);
    }
    if (fFlags & kHasAgeSequenceNumber) {
        prc->startTag("SequenceNumber");
        prc->writeParam("value", fAgeSequenceNumber);
        prc->endTag(true);
    }
    if (fFlags & kHasAgeDescription) {
        prc->startTag("AgeDescription");
        prc->writeParam("value", fAgeDescription);
        prc->endTag(true);
    }
    if (fFlags & kHasAgeLanguage) {
        prc->startTag("AgeLanguage");
        prc->writeParam("value", fAgeLanguage);
        prc->endTag(true);
    }
}

void plAgeInfoStruct::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "AgeFilename") {
        fFlags |= kHasAgeFilename;
        fAgeFilename = tag->getParam("value", "");
    } else if (tag->getName() == "InstanceName") {
        fFlags |= kHasAgeInstanceName;
        fAgeInstanceName = tag->getParam("value", "");
    } else if (tag->getName() == "AgeInstanceGUID") {
        fFlags |= kHasAgeInstanceGuid;
        if (tag->hasChildren())
            fAgeInstanceGuid.prcParse(tag->getFirstChild());
        else
            fAgeInstanceGuid.clear();
    } else if (tag->getName() == "UserDefinedName") {
        fFlags |= kHasAgeUserDefinedName;
        fAgeUserDefinedName = tag->getParam("value", "");
    } else if (tag->getName() == "SequenceNumber") {
        fFlags |= kHasAgeSequenceNumber;
        fAgeSequenceNumber = tag->getParam("value", "0").toInt();
    } else if (tag->getName() == "AgeDescription") {
        fFlags |= kHasAgeDescription;
        fAgeDescription = tag->getParam("value", "");
    } else if (tag->getName() == "AgeLanguage") {
        fFlags |= kHasAgeLanguage;
        fAgeLanguage = tag->getParam("value", "0").toInt();
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

bool plAgeInfoStruct::isEmpty() {
    return (fFlags == 0);
}

void plAgeInfoStruct::clear() {
    fFlags = 0;
}

const plString& plAgeInfoStruct::getAgeFilename() const { return fAgeFilename; }
const plString& plAgeInfoStruct::getAgeInstanceName() const { return fAgeInstanceName; }

void plAgeInfoStruct::setAgeFilename(const plString& name) {
    fFlags |= kHasAgeFilename;
    fAgeFilename = name;
}

void plAgeInfoStruct::setAgeInstanceName(const plString& name) {
    fFlags |= kHasAgeInstanceName;
    fAgeInstanceName = name;
}


/* plAgeLinkStruct */
plAgeLinkStruct::plAgeLinkStruct() : fFlags(0), fLinkingRules(0), fAmCCR(0) { }
plAgeLinkStruct::~plAgeLinkStruct() { }

IMPLEMENT_CREATABLE(plAgeLinkStruct, kAgeLinkStruct, plCreatable)

void plAgeLinkStruct::read(hsStream* S, plResManager* mgr) {
    if (S->getVer() < pvEoa) {
        fFlags = S->readShort();
        if (fFlags & kHasAgeInfo)
            fAgeInfo.read(S, mgr);
        if (fFlags & kHasLinkingRules)
            fLinkingRules = S->readByte();
        if (fFlags & (kHasSpawnPt_DEAD | kHasSpawnPt_DEAD2))
            throw hsNotImplementedException(__FILE__, __LINE__, "Old Code");
        if (fFlags & kHasSpawnPt)
            fSpawnPoint.read(S);
        if (fFlags & kHasAmCCR)
            fAmCCR = S->readByte();
        if (fFlags & kHasParentAgeFilename) {
            size_t len = S->readShort();
            fParentAgeFilename = S->readStr(len);
        }
    } else {
        hsBitVector fields;
        fields.read(S);

        clear();
        fAgeInfo.clear();
        if (fields[0]) {
            fFlags |= kHasAgeInfo;
            size_t len = S->readShort();
            fAgeInfo.setAgeFilename(S->readStr(len));
        }
        if (fields[1]) {
            fFlags |= kHasAgeInfo;
            size_t len = S->readShort();
            fAgeInfo.setAgeInstanceName(S->readStr(len));
        }
        if (fields[2]) {
            fFlags |= kHasSpawnPt;
            fSpawnPoint.read(S);
        }
    }
}

void plAgeLinkStruct::write(hsStream* S, plResManager* mgr) {
    if (S->getVer() < pvEoa) {
        S->writeShort(fFlags);
        if (fFlags & kHasAgeInfo)
            fAgeInfo.write(S, mgr);
        if (fFlags & kHasLinkingRules)
            S->writeByte(fLinkingRules);
        if (fFlags & kHasSpawnPt)
            fSpawnPoint.write(S);
        if (fFlags & kHasAmCCR)
            S->writeByte(fAmCCR);
        if (fFlags & kHasParentAgeFilename) {
            S->writeShort(fParentAgeFilename.len());
            S->writeStr(fParentAgeFilename);
        }
    } else {
        hsBitVector fields;
        fields[0] = true;
        fields[1] = true;
        fields[2] = true;

        S->writeShort(fAgeInfo.getAgeFilename().len());
        S->writeStr(fAgeInfo.getAgeFilename());
        S->writeShort(fAgeInfo.getAgeInstanceName().len());
        S->writeStr(fAgeInfo.getAgeInstanceName());
        fSpawnPoint.write(S);
    }
}

void plAgeLinkStruct::prcParse(const pfPrcTag* tag, plResManager* mgr) {
    fFlags = 0;
    plCreatable::prcParse(tag, mgr);
}

void plAgeLinkStruct::IPrcWrite(pfPrcHelper* prc) {
    if (fFlags & kHasAgeInfo) {
        prc->writeSimpleTag("AgeInfo");
        fAgeInfo.prcWrite(prc);
        prc->closeTag();
    }
    if (fFlags & kHasLinkingRules) {
        prc->startTag("LinkingRules");
        prc->writeParam("value", fLinkingRules);
        prc->endTag(true);
    }
    if (fFlags & kHasSpawnPt) {
        prc->writeSimpleTag("SpawnPoint");
        fSpawnPoint.prcWrite(prc);
        prc->closeTag();
    }
    if (fFlags & kHasAmCCR) {
        prc->startTag("AmCCR");
        prc->writeParam("value", fAmCCR);
        prc->endTag(true);
    }
    if (fFlags & kHasParentAgeFilename) {
        prc->startTag("ParentAgeFilename");
        prc->writeParam("value", fParentAgeFilename);
        prc->endTag(true);
    }
}

void plAgeLinkStruct::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "AgeInfo") {
        fFlags |= kHasAgeInfo;
        if (tag->hasChildren())
            fAgeInfo.prcParse(tag->getFirstChild(), mgr);
        else
            fAgeInfo.clear();
    } else if (tag->getName() == "LinkingRules") {
        fFlags |= kHasLinkingRules;
        fLinkingRules = tag->getParam("value", "0").toInt();
    } else if (tag->getName() == "SpawnPoint") {
        fFlags |= kHasSpawnPt;
        if (tag->hasChildren())
            fSpawnPoint.prcParse(tag->getFirstChild());
        else
            fSpawnPoint.clear();
    } else if (tag->getName() == "AmCCR") {
        fFlags |= kHasAmCCR;
        fAmCCR = tag->getParam("value", "0").toUint();
    } else if (tag->getName() == "ParentAgeFilename") {
        fFlags |= kHasParentAgeFilename;
        fParentAgeFilename = tag->getParam("value", "");
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plAgeLinkStruct::clear() {
    fFlags = 0;
}


/* plAgeLinkEffects */
plAgeLinkEffects::plAgeLinkEffects()
                : fLinkInAnimName("LinkOut"), fBool1(true), fBool2(true),
                  fBool3(true), fBool4(true) { }

void plAgeLinkEffects::read(hsStream* S) {
    if (S->getVer() < pvEoa) {
        fLinkInAnimName = S->readSafeStr();
    } else {
        hsBitVector fields;
        fields.read(S);

        if (fields[0]) {
            size_t len = S->readShort();
            fLinkInAnimName = S->readStr(len);
        }
        if (fields[1])
            fBool1 = S->readInt() != 0;
        if (fields[2])
            fBool2 = S->readInt() != 0;
        if (fields[3])
            fBool3 = S->readInt() != 0;
        if (fields[4])
            fBool4 = S->readInt() != 0;
    }
}

void plAgeLinkEffects::write(hsStream* S) {
    if (S->getVer() < pvEoa) {
        S->writeSafeStr(fLinkInAnimName);
    } else {
        hsBitVector fields;
        fields[1] = true;
        fields[2] = true;
        fields[3] = true;
        fields[4] = true;
        fields.write(S);

        S->writeInt(fBool1 ? 1 : 0);
        S->writeInt(fBool2 ? 1 : 0);
        S->writeInt(fBool3 ? 1 : 0);
        S->writeInt(fBool4 ? 1 : 0);
    }
}

void plAgeLinkEffects::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plAgeLinkEffects");
    prc->writeParam("LinkInAnimName", fLinkInAnimName);
    prc->writeParam("Bool1", fBool1);
    prc->writeParam("Bool2", fBool2);
    prc->writeParam("Bool3", fBool3);
    prc->writeParam("Bool4", fBool4);
    prc->endTag(true);
}

void plAgeLinkEffects::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plAgeLinkEffects")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fLinkInAnimName = tag->getParam("LinkInAnimName", "");
    fBool1 = tag->getParam("Bool1", "true").toBool();
    fBool2 = tag->getParam("Bool2", "true").toBool();
    fBool3 = tag->getParam("Bool3", "true").toBool();
    fBool4 = tag->getParam("Bool4", "true").toBool();
}
