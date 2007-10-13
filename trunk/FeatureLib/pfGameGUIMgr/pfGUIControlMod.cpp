#include "pfGUIControlMod.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

/* pfGUIColorScheme */
pfGUIColorScheme::pfGUIColorScheme() {
    IReset();
}

pfGUIColorScheme::~pfGUIColorScheme() { }

void pfGUIColorScheme::IReset() {
    fForeColor.set(1.0f, 1.0f, 1.0f, 1.0f);
    fBackColor.set(0.0f, 0.0f, 0.0f, 1.0f);
    fSelForeColor.set(1.0f, 1.0f, 1.0f, 1.0f);
    fSelBackColor.set(0.0f, 0.0f, 1.0f, 1.0f);
    fTransparent = 0;
    fFontFace = "Times New Roman";
    fFontSize = 10;
    fFontFlags = 0;
}

void pfGUIColorScheme::read(hsStream* S) {
    fForeColor.read(S);
    fBackColor.read(S);
    fSelForeColor.read(S);
    fSelBackColor.read(S);
    fTransparent = S->readInt();
    fFontFace = S->readSafeStr();
    fFontSize = S->readByte();
    fFontFlags = S->readByte();
}

void pfGUIColorScheme::write(hsStream* S) {
    fForeColor.write(S);
    fBackColor.write(S);
    fSelForeColor.write(S);
    fSelBackColor.write(S);
    S->writeInt(fTransparent);
    S->writeSafeStr(fFontFace);
    S->writeByte(fFontSize);
    S->writeByte(fFontFlags);
}

void pfGUIColorScheme::prcWrite(pfPrcHelper* prc) {
    prc->startTag("pfGUIColorScheme");
    prc->writeParam("Face", fFontFace);
    prc->writeParam("Size", fFontSize);
    prc->writeParam("transparent", fTransparent);
    prc->writeParam("flags", fFontFlags);
    prc->endTag();

    prc->writeSimpleTag("Foreground");
    fForeColor.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Background");
    fBackColor.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("SelForeground");
    fSelForeColor.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("SelBackground");
    fSelBackColor.prcWrite(prc);
    prc->closeTag();

    prc->closeTag();
}


/* pfGUIControlMod */
pfGUIControlMod::pfGUIControlMod()
               : fTagID(0), fEnabled(true), fFocused(false), fVisible(true),
                 fInteresting(false), fNotifyOnInteresting(false),
                 fDialog(NULL), fBoundsValid(false), fCenterValid(false),
                 fHandler(NULL), fColorScheme(NULL), fSkin(NULL) { }

pfGUIControlMod::~pfGUIControlMod() {
    if (fHandler) delete fHandler;
}

IMPLEMENT_CREATABLE(pfGUIControlMod, kGUIControlMod, plSingleModifier)

void pfGUIControlMod::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fTagID = S->readInt();
    fVisible = S->readBool();
    if (fHandler != NULL) delete fHandler;
    fHandler = pfGUICtrlProcWriteableObject::Read(S);

    if (S->readBool()) {
        fDynTextLayer = mgr->readKey(S);
        fDynTextMap = mgr->readKey(S);
    }

    if (S->readBool()) {
        if (fColorScheme != NULL) delete fColorScheme;
        fColorScheme = new pfGUIColorScheme();
        fColorScheme->read(S);
    }

    fSoundIndices.setSizeNull(S->readByte());
    for (size_t i=0; i<fSoundIndices.getSize(); i++)
        fSoundIndices[i] = S->readInt();

    if (fFlags[kHasProxy])
        fProxy = mgr->readKey(S);
    fSkin = mgr->readKey(S);
}

void pfGUIControlMod::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    if (fFlags[kHasProxy] && fProxy == NULL)
        fFlags.clearBit(kHasProxy);
    S->writeInt(fTagID);
    S->writeBool(fVisible);
    pfGUICtrlProcWriteableObject::Write(S, fHandler);

    if (fDynTextMap.Exists()) {
        S->writeBool(true);
        mgr->writeKey(S, fDynTextLayer);
        mgr->writeKey(S, fDynTextMap);
    } else {
        S->writeBool(false);
    }

    if (fColorScheme != NULL) {
        S->writeBool(true);
        fColorScheme->write(S);
    } else {
        S->writeBool(false);
    }

    S->writeByte(fSoundIndices.getSize());
    for (size_t i=0; i<fSoundIndices.getSize(); i++)
        S->writeInt(fSoundIndices[i]);

    if (fFlags[kHasProxy])
        mgr->writeKey(S, fProxy);
    mgr->writeKey(S, fSkin);
}

void pfGUIControlMod::prcWrite(pfPrcHelper* prc) {
    plSingleModifier::prcWrite(prc);

    if (fFlags[kHasProxy] && fProxy == NULL)
        fFlags.clearBit(kHasProxy);
    prc->startTag("ControlParams");
    prc->writeParam("TagID", fTagID);
    prc->writeParam("Visible", fVisible);
    prc->endTag(true);
    pfGUICtrlProcWriteableObject::PrcWrite(prc, fHandler);

    prc->writeSimpleTag("DynTextMap");
    fDynTextLayer->prcWrite(prc);
    fDynTextMap->prcWrite(prc);
    prc->closeTag();

    if (fColorScheme != NULL) {
        fColorScheme->prcWrite(prc);
    } else {
        prc->startTag("pfGUIColorScheme");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }

    prc->writeSimpleTag("SoundIndices");
    for (size_t i=0; i<fSoundIndices.getSize(); i++) {
        prc->startTag("SoundIndex");
        prc->writeParam("value", fSoundIndices[i]);
        prc->endTag(true);
    }
    prc->closeTag();

    if (fFlags[kHasProxy]) {
        prc->writeSimpleTag("Proxy");
        fProxy->prcWrite(prc);
        prc->closeTag();
    }
    prc->writeSimpleTag("Skin");
    fSkin->prcWrite(prc);
    prc->closeTag();
}
