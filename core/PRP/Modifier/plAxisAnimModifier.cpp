#include "plAxisAnimModifier.h"

plAxisAnimModifier::plAxisAnimModifier()
                  : fNotify(NULL), fAllOrNothing(false) { }

plAxisAnimModifier::~plAxisAnimModifier() {
    delete fNotify;
}

void plAxisAnimModifier::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    if (S->getVer() >= pvEoa) {
        b65 = S->readBool();
        b66 = S->readBool();
    }

    fXAnim = mgr->readKey(S);
    fYAnim = mgr->readKey(S);
    fNotificationKey = mgr->readKey(S);
    fAllOrNothing = S->readBool();

    setNotify(plNotifyMsg::Convert(mgr->ReadCreatable(S)));
    size_t len = S->readShort();
    fAnimLabel = S->readStr(len);

    if (S->getVer() >= pvEoa) {
        af38.setSizeNull(S->readInt());
        for (size_t i=0; i<af38.getSize(); i++)
            af38[i] = S->readFloat();
        af40.setSizeNull(S->readInt());
        for (size_t i=0; i<af40.getSize(); i++)
            af40[i] = S->readFloat();

        b70 = S->readBool();
        f48 = S->readFloat();
        f58 = S->readFloat();
        f5c = S->readFloat();

        fb0 = S->readFloat();
        fac = S->readFloat();
        fa0 = S->readFloat();
        f98 = S->readFloat();
        fa4 = S->readFloat();

        b60 = S->readBool();
        b90 = S->readBool();
        bb4 = S->readBool();
        bb5 = S->readBool();
    }
}

void plAxisAnimModifier::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    if (S->getVer() >= pvEoa) {
        S->writeBool(b65);
        S->writeBool(b66);
    }

    mgr->writeKey(S, fXAnim);
    mgr->writeKey(S, fYAnim);
    mgr->writeKey(S, fNotificationKey);
    S->writeBool(fAllOrNothing);

    mgr->WriteCreatable(S, fNotify);
    S->writeShort(fAnimLabel.len());
    S->writeStr(fAnimLabel);

    if (S->getVer() >= pvEoa) {
        S->writeInt(af38.getSize());
        for (size_t i=0; i<af38.getSize(); i++)
            S->writeFloat(af38[i]);
        S->writeInt(af40.getSize());
        for (size_t i=0; i<af40.getSize(); i++)
            S->writeFloat(af40[i]);

        S->writeBool(b70);
        S->writeFloat(f48);
        S->writeFloat(f58);
        S->writeFloat(f5c);

        S->writeFloat(fb0);
        S->writeFloat(fac);
        S->writeFloat(fa0);
        S->writeFloat(f98);
        S->writeFloat(fa4);

        S->writeBool(b60);
        S->writeBool(b90);
        S->writeBool(bb4);
        S->writeBool(bb5);
    }
}

void plAxisAnimModifier::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("AxisAnimParams");
    prc->writeParam("AllOrNothing", fAllOrNothing);
    prc->writeParam("AnimLabel", fAnimLabel);
    prc->endTag(true);

    prc->writeSimpleTag("XAnim");
    fXAnim->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("YAnim");
    fYAnim->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("NotificationKey");
    fNotificationKey->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Notify");
    fNotify->prcWrite(prc);
    prc->closeTag();

    prc->startTag("EoaUnknowns");
    prc->writeParam("b65", b65);
    prc->writeParam("b66", b65);
    prc->endTag();

    prc->writeSimpleTag("Array38");
    for (size_t i=0; i<af38.getSize(); i++) {
        prc->startTag("Entry");
        prc->writeParam("value", af38[i]);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->writeSimpleTag("Array40");
    for (size_t i=0; i<af40.getSize(); i++) {
        prc->startTag("Entry");
        prc->writeParam("value", af40[i]);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->startTag("Block1");
    prc->writeParam("b70", b70);
    prc->writeParam("f48", f48);
    prc->writeParam("f58", f58);
    prc->writeParam("f5c", f5c);
    prc->endTag(true);

    prc->startTag("Block2");
    prc->writeParam("fb0", fb0);
    prc->writeParam("fac", fac);
    prc->writeParam("fa0", fa0);
    prc->writeParam("f98", f98);
    prc->writeParam("fa4", fa4);
    prc->endTag(true);

    prc->startTag("Block3");
    prc->writeParam("b60", b60);
    prc->writeParam("b90", b90);
    prc->writeParam("bb4", bb4);
    prc->writeParam("bb5", bb5);
    prc->endTag(true);

    prc->closeTag();    // EoaUnknowns
}

void plAxisAnimModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "AxisAnimParams") {
        fAllOrNothing = tag->getParam("AllOrNothing", "false").toBool();
        fAnimLabel = tag->getParam("AnimLabel", "");
    } else if (tag->getName() == "XAnim") {
        if (tag->hasChildren())
            fXAnim = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "YAnim") {
        if (tag->hasChildren())
            fYAnim = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "NotificationKey") {
        if (tag->hasChildren())
            fNotificationKey = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Notify") {
        if (tag->hasChildren())
            setNotify(plNotifyMsg::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "EoaUnknowns") {
        // Blah, skip for now
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}

void plAxisAnimModifier::setNotify(plNotifyMsg* msg) {
    delete fNotify;
    fNotify = msg;
}
