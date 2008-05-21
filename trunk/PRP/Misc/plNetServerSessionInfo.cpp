#include "plNetServerSessionInfo.h"

// plAgeInfoStruct //
plAgeInfoStruct::plAgeInfoStruct() : fFlags(0) { }
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
    } else {
        fAgeSequenceNumber = 0;
    }
    if (fFlags & kHasAgeDescription) {
        size_t len = S->readShort();
        fAgeDescription = S->readStr(len);
    }
    if (fFlags & kHasAgeLanguage) {
        fAgeLanguage = S->readInt();
    } else {
        fAgeLanguage = 0;
    }
}

void plAgeInfoStruct::write(hsStream* S, plResManager* mgr) {
    UpdateFlags();
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

void plAgeInfoStruct::IPrcWrite(pfPrcHelper* prc) {
    UpdateFlags();
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
        fAgeFilename = tag->getParam("value", "");
    } else if (tag->getName() == "InstanceName") {
        fAgeInstanceName = tag->getParam("value", "");
    } else if (tag->getName() == "AgeInstanceGUID") {
        if (tag->hasChildren())
            fAgeInstanceGuid.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "UserDefinedName") {
        fAgeUserDefinedName = tag->getParam("value", "");
    } else if (tag->getName() == "SequenceNumber") {
        fAgeSequenceNumber = tag->getParam("value", "0").toInt();
    } else if (tag->getName() == "AgeDescription") {
        fAgeDescription = tag->getParam("value", "");
    } else if (tag->getName() == "AgeLanguage") {
        fAgeLanguage = tag->getParam("value", "0").toInt();
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plAgeInfoStruct::UpdateFlags() {
    fFlags = 0;
    if (!fAgeFilename.empty())
        fFlags |= kHasAgeFilename;
    if (!fAgeInstanceName.empty())
        fFlags |= kHasAgeInstanceName;
    if (!fAgeUserDefinedName.empty())
        fFlags |= kHasAgeUserDefinedName;
    if (!fAgeInstanceGuid.isNull())
        fFlags |= kHasAgeInstanceGuid;
    if (fAgeSequenceNumber != 0)
        fFlags |= kHasAgeSequenceNumber;
    if (!fAgeDescription.empty())
        fFlags |= kHasAgeDescription;
    if (fAgeLanguage != 0)
        fFlags |= kHasAgeLanguage;
}

bool plAgeInfoStruct::isEmpty() {
    UpdateFlags();
    return (fFlags == 0);
}


// plAgeLinkStruct //
plAgeLinkStruct::plAgeLinkStruct() : fFlags(0) { }
plAgeLinkStruct::~plAgeLinkStruct() { }

IMPLEMENT_CREATABLE(plAgeLinkStruct, kAgeLinkStruct, plCreatable)

void plAgeLinkStruct::read(hsStream* S, plResManager* mgr) {
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
}

void plAgeLinkStruct::write(hsStream* S, plResManager* mgr) {
    UpdateFlags();
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
}

void plAgeLinkStruct::IPrcWrite(pfPrcHelper* prc) {
    UpdateFlags();
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
        if (tag->hasChildren())
            fAgeInfo.prcParse(tag->getFirstChild(), mgr);
    } else if (tag->getName() == "LinkingRules") {
        fLinkingRules = tag->getParam("value", "0").toInt();
    } else if (tag->getName() == "SpawnPoint") {
        if (tag->hasChildren())
            fSpawnPoint.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "AmCCR") {
        fAmCCR = tag->getParam("value", "0").toUint();
    } else if (tag->getName() == "ParentAgeFilename") {
        fParentAgeFilename = tag->getParam("value", "");
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plAgeLinkStruct::UpdateFlags() {
    fFlags = 0;
    if (!fAgeInfo.isEmpty())
        fFlags |= kHasAgeInfo;
    if (fLinkingRules != 0)
        fFlags |= kHasLinkingRules;
    if (fAmCCR != 0)
        fFlags |= kHasAmCCR;
    if (!fSpawnPoint.isEmpty())
        fFlags |= kHasSpawnPt;
    if (!fParentAgeFilename.empty())
        fFlags |= kHasParentAgeFilename;
}
