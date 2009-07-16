#include "pfGUITextBoxMod.h"

pfGUITextBoxMod::pfGUITextBoxMod() {
    fFlags.setName(kCenterJustify, "kCenterJustify");
    fFlags.setName(kRightJustify, "kRightJustify");
}

pfGUITextBoxMod::~pfGUITextBoxMod() { }

IMPLEMENT_CREATABLE(pfGUITextBoxMod, kGUITextBoxMod, pfGUIControlMod)

void pfGUITextBoxMod::read(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::read(S, mgr);

    int len = S->readInt();
    fText = S->readStr(len);

    if ((S->getVer() == pvLive) && S->readBool())
        fLocalizationPath = S->readSafeWStr();
    else
        fLocalizationPath = plWString();
}

void pfGUITextBoxMod::write(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::write(S, mgr);

    S->writeInt(fText.len());
    S->writeStr(fText);

    if (S->getVer() == pvLive) {
        S->writeBool(!fLocalizationPath.empty());
        if (!fLocalizationPath.empty())
            S->writeSafeWStr(fLocalizationPath);
    }
}

void pfGUITextBoxMod::IPrcWrite(pfPrcHelper* prc) {
    pfGUIControlMod::IPrcWrite(prc);

    prc->writeSimpleTag("Text");
    prc->writeHexStream(fText.len(), (unsigned char*)fText.cstr());
    prc->closeTag();

    prc->startTag("LocalizationPath");
    prc->writeParam("value", hsWStringToString(fLocalizationPath));
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
    } else {
        pfGUIControlMod::IPrcParse(tag, mgr);
    }
}

const plString& pfGUITextBoxMod::getText() const { return fText; }
const plWString& pfGUITextBoxMod::getLocalizationPath() const { return fLocalizationPath; }

void pfGUITextBoxMod::setText(const plString& text) { fText = text; }
void pfGUITextBoxMod::setLocalizationPath(const plWString& path) { fLocalizationPath = path; }
