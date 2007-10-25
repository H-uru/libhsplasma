#include "pfGUICheckBoxCtrl.h"

pfGUICheckBoxCtrl::pfGUICheckBoxCtrl() : fClicking(false), fChecked(false) { }
pfGUICheckBoxCtrl::~pfGUICheckBoxCtrl() { }

IMPLEMENT_CREATABLE(pfGUICheckBoxCtrl, kGUICheckBoxCtrl, pfGUIControlMod)

void pfGUICheckBoxCtrl::setChecked(bool checked) {
    fChecked = checked;
    //TODO: Animation stuff...
}

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

void pfGUICheckBoxCtrl::prcWrite(pfPrcHelper* prc) {
    pfGUIControlMod::prcWrite(prc);

    prc->startTag("CheckBoxParams");
    prc->writeParam("AnimName", fAnimName);
    prc->writeParam("Checked", fChecked);
    prc->endTag(true);

    prc->writeSimpleTag("AnimKeys");
    for (size_t i=0; i<fAnimKeys.getSize(); i++)
        fAnimKeys[i]->prcWrite(prc);
    prc->closeTag();
}
