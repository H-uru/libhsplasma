#include "pfGUITextBoxMod.h"

pfGUITextBoxMod::pfGUITextBoxMod() : fUseLocalizationPath(false) {
    fFlags.setName(kCenterJustify, "kCenterJustify");
    fFlags.setName(kRightJustify, "kRightJustify");
}

pfGUITextBoxMod::~pfGUITextBoxMod() { }

IMPLEMENT_CREATABLE(pfGUITextBoxMod, kGUITextBoxMod, pfGUIControlMod)

void pfGUITextBoxMod::read(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::read(S, mgr);

    int len = S->readInt();
    fText = S->readStr(len);

    if (S->getVer() == pvLive)
        fUseLocalizationPath = S->readBool();
    else
        fUseLocalizationPath = false;
    if (fUseLocalizationPath)
        fLocalizationPath = S->readSafeWStr();
}

void pfGUITextBoxMod::write(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::write(S, mgr);

    S->writeInt(fText.len());
    S->write(fText.len(), fText.cstr());

    if (fLocalizationPath.empty())
        fUseLocalizationPath = false;
    if (S->getVer() == pvLive) {
        S->writeBool(fUseLocalizationPath);
        if (fUseLocalizationPath)
            S->writeSafeWStr(fLocalizationPath);
    }
}

void pfGUITextBoxMod::IPrcWrite(pfPrcHelper* prc) {
    pfGUIControlMod::IPrcWrite(prc);

    prc->writeTagNoBreak("Text");
    prc->getStream()->writeStr(fText);
    prc->closeTagNoBreak();

    prc->startTag("LocalizationPath");
    if (fUseLocalizationPath)
        prc->writeParam("value", hsWStringToString(fLocalizationPath));
    else
        prc->writeParam("Use", false);
    prc->endTag(true);
}
