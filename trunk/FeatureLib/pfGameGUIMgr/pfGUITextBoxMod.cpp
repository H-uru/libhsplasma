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
    if (len > 0) {
        char* buf = new char[len+1];
        S->read(len, buf);
        buf[len] = 0;
        fText = buf;
        delete[] buf;
    } else {
        fText = "";
    }

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

void pfGUITextBoxMod::prcWrite(pfPrcHelper* prc) {
    pfGUIControlMod::prcWrite(prc);

    prc->writeTagNoBreak("Text");
    prc->getStream()->write(fText.len(), fText.cstr());
    prc->closeTagNoBreak();

    prc->startTag("LocalizationPath");
    if (fUseLocalizationPath)
        prc->writeParam("value", hsWStringToString(fLocalizationPath));
    else
        prc->writeParam("Use", false);
    prc->endTag(true);
}
