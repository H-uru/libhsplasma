#include "pfObjectFlocker.h"

pfObjectFlocker::FlockStruct::FlockStruct()
               : fFloat1(0.0f), fFloat3(0.0f) {
    fFloat2[0] = 0.0f;
    fFloat2[1] = 0.0f;
    fFloat2[2] = 0.0f;
    fFloat2[3] = 0.0f;
    fFloat2[4] = 0.0f;
    fFloat2[5] = 0.0f;
}

pfObjectFlocker::pfObjectFlocker()
               : fFlags(0), fBool1(false), fBool2(false), fFloat1(0.0f) { }

IMPLEMENT_CREATABLE(pfObjectFlocker, kObjectFlocker, plSingleModifier)

void pfObjectFlocker::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    S->readByte();
    fFlags = S->readByte();
    fTarget = mgr->readKey(S);

    fFlockStruct.fFloat1 = S->readFloat();
    fFlockStruct.fFloat2[0] = S->readFloat();
    fFlockStruct.fFloat2[1] = S->readFloat();
    fFlockStruct.fFloat2[2] = S->readFloat();
    fFlockStruct.fFloat2[3] = S->readFloat();
    fFlockStruct.fFloat2[4] = S->readFloat();
    fFlockStruct.fFloat2[5] = S->readFloat();
    fFlockStruct.fFloat3 = S->readFloat();

    fFloat1 = S->readFloat();
    fBool1 = S->readBool();
    fBool2 = S->readBool();
}

void pfObjectFlocker::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeByte(1);
    S->writeByte(fFlags);
    mgr->writeKey(S, fTarget);

    S->writeFloat(fFlockStruct.fFloat1);
    S->writeFloat(fFlockStruct.fFloat2[0]);
    S->writeFloat(fFlockStruct.fFloat2[1]);
    S->writeFloat(fFlockStruct.fFloat2[2]);
    S->writeFloat(fFlockStruct.fFloat2[3]);
    S->writeFloat(fFlockStruct.fFloat2[4]);
    S->writeFloat(fFlockStruct.fFloat2[5]);
    S->writeFloat(fFlockStruct.fFloat3);

    S->writeFloat(fFloat1);
    S->writeBool(fBool1);
    S->writeBool(fBool2);
}

void pfObjectFlocker::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->writeComment("This stuff obviously needs research");

    prc->startTag("FlockParams");
    prc->writeParamHex("Flags", fFlags);
    prc->writeParam("Float1", fFloat1);
    prc->writeParam("Bool1", fBool1);
    prc->writeParam("Bool2", fBool2);
    prc->endTag(true);

    prc->writeSimpleTag("Target");
    fTarget->prcWrite(prc);
    prc->closeTag();

    prc->startTag("FlockStruct");
    prc->writeParam("Float1", fFlockStruct.fFloat1);
    prc->writeParam("Float2_0", fFlockStruct.fFloat2[0]);
    prc->writeParam("Float2_1", fFlockStruct.fFloat2[1]);
    prc->writeParam("Float2_2", fFlockStruct.fFloat2[2]);
    prc->writeParam("Float2_3", fFlockStruct.fFloat2[3]);
    prc->writeParam("Float2_4", fFlockStruct.fFloat2[4]);
    prc->writeParam("Float2_5", fFlockStruct.fFloat2[5]);
    prc->writeParam("Float3", fFlockStruct.fFloat3);
    prc->endTag(true);
}

void pfObjectFlocker::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "FlockParams") {
        fFlags = tag->getParam("Flags", "0").toUint();
        fFloat1 = tag->getParam("Float1", "0").toFloat();
        fBool1 = tag->getParam("Bool1", "false").toBool();
        fBool2 = tag->getParam("Bool2", "false").toBool();
    } else if (tag->getName() == "Target") {
        if (tag->hasChildren())
            fTarget = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "FlockStruct") {
        fFlockStruct.fFloat1 = tag->getParam("Float1", "0").toFloat();
        fFlockStruct.fFloat2[0] = tag->getParam("Float2_0", "0").toFloat();
        fFlockStruct.fFloat2[1] = tag->getParam("Float2_1", "0").toFloat();
        fFlockStruct.fFloat2[2] = tag->getParam("Float2_2", "0").toFloat();
        fFlockStruct.fFloat2[3] = tag->getParam("Float2_3", "0").toFloat();
        fFlockStruct.fFloat2[4] = tag->getParam("Float2_4", "0").toFloat();
        fFlockStruct.fFloat2[5] = tag->getParam("Float2_5", "0").toFloat();
        fFlockStruct.fFloat3 = tag->getParam("Float3", "0").toFloat();
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
