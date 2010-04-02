#include "pfGUICheckBoxCtrl.h"

pfGUICheckBoxCtrl::pfGUICheckBoxCtrl() : fChecked(false) { }

void pfGUICheckBoxCtrl::read(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::read(S, mgr);

    fAnimKeys.setSize(S->readInt());
    for (size_t i=0; i<fAnimKeys.getSize(); i++)
        fAnimKeys[i] = mgr->readKey(S);
    fAnimName = S->readSafeStr();
    fChecked = S->readBool();
}

void pfGUICheckBoxCtrl::write(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::write(S, mgr);

    S->writeInt(fAnimKeys.getSize());
    for (size_t i=0; i<fAnimKeys.getSize(); i++)
        mgr->writeKey(S, fAnimKeys[i]);
    S->writeSafeStr(fAnimName);
    S->writeBool(fChecked);
}

void pfGUICheckBoxCtrl::IPrcWrite(pfPrcHelper* prc) {
    pfGUIControlMod::IPrcWrite(prc);

    prc->startTag("CheckBoxParams");
    prc->writeParam("AnimName", fAnimName);
    prc->writeParam("Checked", fChecked);
    prc->endTag(true);

    prc->writeSimpleTag("AnimKeys");
    for (size_t i=0; i<fAnimKeys.getSize(); i++)
        fAnimKeys[i]->prcWrite(prc);
    prc->closeTag();
}

void pfGUICheckBoxCtrl::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "CheckBoxParams") {
        fAnimName = tag->getParam("AnimName", "");
        fChecked = tag->getParam("Checked", "false").toBool();
    } else if (tag->getName() == "AnimKeys") {
        fAnimKeys.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fAnimKeys.getSize(); i++) {
            fAnimKeys[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        pfGUIControlMod::IPrcParse(tag, mgr);
    }
}
