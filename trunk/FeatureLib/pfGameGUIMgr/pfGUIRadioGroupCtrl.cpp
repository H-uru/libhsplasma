#include "pfGUIRadioGroupCtrl.h"
#include "pfGUICheckBoxCtrl.h"

/* pfGroupProc */
pfGroupProc::pfGroupProc(pfGUIRadioGroupCtrl* parent) : fParent(parent) { }

void pfGroupProc::DoSomething(pfGUIControlMod* ctrl) {
    //TODO: Whatever...
}


/* pfGUIRadioGroupCtrl */
pfGUIRadioGroupCtrl::pfGUIRadioGroupCtrl()
                   : fButtonProc(NULL), fValue(0), fDefaultValue(0) {
    fFlags.setName(kAllowNoSelection, "kAllowNoSelection");
}

pfGUIRadioGroupCtrl::~pfGUIRadioGroupCtrl() { }

IMPLEMENT_CREATABLE(pfGUIRadioGroupCtrl, kGUIRadioGroupCtrl, pfGUIControlMod)

void pfGUIRadioGroupCtrl::read(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::read(S, mgr);

    fControls.setSize(S->readInt());
    for (size_t i=0; i<fControls.getSize(); i++)
        fControls[i] = mgr->readKey(S);

    fDefaultValue = fValue = S->readShort();
    //if (fValue != -1 && fControls[fValue].Exists())
    //    fControls[fValue]->getObj()->setChecked(true);
}

void pfGUIRadioGroupCtrl::write(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::write(S, mgr);

    S->writeInt(fControls.getSize());
    for (size_t i=0; i<fControls.getSize(); i++)
        mgr->writeKey(S, fControls[i]);

    S->writeShort(fDefaultValue);
}

void pfGUIRadioGroupCtrl::prcWrite(pfPrcHelper* prc) {
    pfGUIControlMod::prcWrite(prc);

    prc->startTag("Items");
    prc->writeParam("Default", fDefaultValue);
    prc->endTag();
    for (size_t i=0; i<fControls.getSize(); i++)
        fControls[i]->prcWrite(prc);
    prc->closeTag();
}
