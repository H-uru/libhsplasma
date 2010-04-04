#include "plNetSharedState.h"

/* plGenericType */
plGenericType::plGenericType() : fType(kNone) { }

void plGenericType::read(hsStream* S) {
    fType = S->readByte();
    switch (fType) {
    case kString:
    case kAny:
        fString = S->readSafeStr();
        break;
    case kBool:
        fBool = S->readBool();
        break;
    case kByte:
        fByte = S->readByte();
        break;
    case kInt:
    case kUint:
        fUint = S->readInt();
        break;
    case kFloat:
        fFloat = S->readFloat();
        break;
    case kDouble:
        fDouble = S->readDouble();
        break;
    default:
        throw hsBadParamException(__FILE__, __LINE__, "Invalid variable type");
    }
}

void plGenericType::write(hsStream* S) {
    S->writeByte(fType);
    switch (fType) {
    case kString:
    case kAny:
        S->writeSafeStr(fString);
        break;
    case kBool:
        S->writeBool(fBool);
        break;
    case kByte:
        S->writeByte(fByte);
        break;
    case kInt:
    case kUint:
        S->writeInt(fUint);
        break;
    case kFloat:
        S->writeFloat(fFloat);
        break;
    case kDouble:
        S->writeDouble(fDouble);
        break;
    }
}

void plGenericType::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plGenericType");
    prc->writeParam("Type", fType);

    switch (fType) {
    case kString:
    case kAny:
        prc->writeParam("Value", fString);
        break;
    case kBool:
        prc->writeParam("Value", fBool);
        break;
    case kByte:
        prc->writeParam("Value", fByte);
        break;
    case kInt:
        prc->writeParam("Value", fInt);
        break;
    case kUint:
        prc->writeParam("Value", fUint);
        break;
    case kFloat:
        prc->writeParam("Value", fFloat);
        break;
    case kDouble:
        prc->writeParam("Value", fDouble);
        break;
    }
    prc->endTag(true);
}

void plGenericType::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plGenericType")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fType = tag->getParam("Type", "0xFF").toUint();
    switch (fType) {
    case kString:
    case kAny:
        fString = tag->getParam("Value", "");
        break;
    case kBool:
        fBool = tag->getParam("Value", "false").toBool();
        break;
    case kByte:
        fByte = tag->getParam("Value", "0").toUint();
        break;
    case kInt:
        fInt = tag->getParam("Value", "0").toInt();
        break;
    case kUint:
        fUint = tag->getParam("Value", "0").toUint();
        break;
    case kFloat:
        fFloat = tag->getParam("Value", "0").toFloat();
        break;
    case kDouble:
        fDouble = tag->getParam("Value", "0").toFloat();
        break;
    default:
        throw hsBadParamException(__FILE__, __LINE__, "Invalid variable type");
    }
}


/* plGenericVar */
void plGenericVar::read(hsStream* S) {
    fName = S->readSafeStr();
    fValue.read(S);
}

void plGenericVar::write(hsStream* S) {
    S->writeSafeStr(fName);
    fValue.write(S);
}

void plGenericVar::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plGenericVar");
    prc->writeParam("Name", fName);
    prc->endTag();
    fValue.prcWrite(prc);
    prc->closeTag();
}

void plGenericVar::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plGenericVar")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fName = tag->getParam("Name", "");
    if (tag->hasChildren())
        fValue.prcParse(tag);
}


/* plNetSharedState */
plNetSharedState::plNetSharedState() : fServerMayDelete(false) { }

void plNetSharedState::read(hsStream* S) {
    unsigned short sz = S->readShort();
    fName = S->readStr(sz);
    size_t count = S->readInt();
    fServerMayDelete = S->readBool();

    fVars.setSize(count);
    for (size_t i=0; i<count; i++)
        fVars[i].read(S);
}

void plNetSharedState::write(hsStream* S) {
    S->writeShort(fName.len());
    S->writeStr(fName);
    S->writeInt(fVars.getSize());
    S->writeBool(fServerMayDelete);

    for (size_t i=0; i<fVars.getSize(); i++)
        fVars[i].write(S);
}

void plNetSharedState::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plNetSharedState");
    prc->writeParam("Name", fName);
    prc->writeParam("ServerMayDelete", fServerMayDelete);
    prc->endTag();

    for (size_t i=0; i<fVars.getSize(); i++)
        fVars[i].prcWrite(prc);

    prc->closeTag();
}

void plNetSharedState::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plNetSharedState")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fName = tag->getParam("Name", "");
    fServerMayDelete = tag->getParam("ServerMayDelete", "false").toBool();

    fVars.setSize(tag->countChildren());
    const pfPrcTag* child = tag->getFirstChild();
    for (size_t i=0; i<fVars.getSize(); i++) {
        fVars[i].prcParse(child);
        child = child->getNextSibling();
    }
}
