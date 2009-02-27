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

    fUseLocalizationPath = (S->getVer() == pvLive) ? S->readBool() : false;
    if (fUseLocalizationPath)
        fLocalizationPath = S->readSafeWStr();
}

void pfGUITextBoxMod::write(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::write(S, mgr);

    S->writeInt(fText.len());
    S->writeStr(fText);

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

    prc->writeSimpleTag("Text");
    prc->writeHexStream(fText.len(), (unsigned char*)fText.cstr());
    prc->closeTag();

    prc->startTag("LocalizationPath");
    if (fUseLocalizationPath)
        prc->writeParam("value", hsWStringToString(fLocalizationPath));
    else
        prc->writeParam("Use", false);
    prc->endTag(true);
}

void pfGUITextBoxMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Text") {
        size_t bufLen = tag->getContents().getSize();
        char* buf = new char[bufLen + 1];
        tag->readHexStream(bufLen, (unsigned char*)buf);
        buf[bufLen] = 0;
        fText = buf;
    } else if (tag->getName() == "LocalizationPath") {
        fLocalizationPath = hsStringToWString(tag->getParam("value", ""));
        fUseLocalizationPath = tag->getParam("Use", "true").toBool();
    } else {
        pfGUIControlMod::IPrcParse(tag, mgr);
    }
}
