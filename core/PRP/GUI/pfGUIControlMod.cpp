/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "pfGUIControlMod.h"

/* pfGUIColorScheme */
void pfGUIColorScheme::IReset()
{
    fForeColor.set(1.0f, 1.0f, 1.0f, 1.0f);
    fBackColor.set(0.0f, 0.0f, 0.0f, 1.0f);
    fSelForeColor.set(1.0f, 1.0f, 1.0f, 1.0f);
    fSelBackColor.set(0.0f, 0.0f, 1.0f, 1.0f);
    fTransparent = 0;
    fFontFace = "Times New Roman";
    fFontSize = 10;
    fFontFlags = 0;
}

void pfGUIColorScheme::read(hsStream* S)
{
    fForeColor.read(S);
    fBackColor.read(S);
    fSelForeColor.read(S);
    fSelBackColor.read(S);
    fTransparent = S->readInt();
    fFontFace = S->readSafeStr();
    fFontSize = S->readByte();
    fFontFlags = S->readByte();
}

void pfGUIColorScheme::write(hsStream* S)
{
    fForeColor.write(S);
    fBackColor.write(S);
    fSelForeColor.write(S);
    fSelBackColor.write(S);
    S->writeInt(fTransparent);
    S->writeSafeStr(fFontFace);
    S->writeByte(fFontSize);
    S->writeByte(fFontFlags);
}

void pfGUIColorScheme::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("pfGUIColorScheme");
    prc->writeParam("Face", fFontFace);
    prc->writeParam("Size", fFontSize);
    prc->writeParam("transparent", fTransparent);
    prc->writeParamHex("flags", fFontFlags);
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

void pfGUIColorScheme::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "pfGUIColorScheme")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fFontFace = tag->getParam("Face", "");
    fFontSize = tag->getParam("Size", "0").to_uint();
    fTransparent = tag->getParam("transparent", "0").to_int();
    fFontFlags = tag->getParam("flags", "0").to_uint();

    const pfPrcTag* child = tag->getFirstChild();
    while (child) {
        if (child->getName() == "Foreground") {
            if (child->hasChildren())
                fForeColor.prcParse(child->getFirstChild());
        } else if (child->getName() == "Background") {
            if (child->hasChildren())
                fBackColor.prcParse(child->getFirstChild());
        } else if (child->getName() == "SelForeground") {
            if (child->hasChildren())
                fSelForeColor.prcParse(child->getFirstChild());
        } else if (child->getName() == "SelBackground") {
            if (child->hasChildren())
                fSelBackColor.prcParse(child->getFirstChild());
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}


/* pfGUIControlMod */
pfGUIControlMod::pfGUIControlMod()
    : fTagID(), fVisible(true), fHandler(), fColorScheme()
{
    fFlags.setName(kWantsInterest, "kWantsInterest");
    fFlags.setName(kInheritProcFromDlg, "kInheritProcFromDlg");
    fFlags.setName(kIntangible, "kIntangible");
    fFlags.setName(kXparentBgnd, "kXparentBgnd");
    fFlags.setName(kScaleTextWithResolution, "kScaleTextWithResolution");
    fFlags.setName(kTakesSpecialKeys, "kTakesSpecialKeys");
    fFlags.setName(kHasProxy, "kHasProxy");
    fFlags.setName(kBetterHitTesting, "kBetterHitTesting");
}

pfGUIControlMod::~pfGUIControlMod()
{
    delete fHandler;
    delete fColorScheme;
}

void pfGUIControlMod::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    fTagID = S->readInt();
    fVisible = S->readBool();
    setHandler(pfGUICtrlProcWriteableObject::Read(S));

    if (S->readBool()) {
        fDynTextLayer = mgr->readKey(S);
        fDynTextMap = mgr->readKey(S);
    }

    if (S->readBool()) {
        setColorScheme(new pfGUIColorScheme());
        fColorScheme->read(S);
    } else {
        setColorScheme(nullptr);
    }

    fSoundIndices.resize(S->readByte());
    for (size_t i=0; i<fSoundIndices.size(); i++)
        fSoundIndices[i] = S->readInt();

    if (fFlags[kHasProxy])
        fProxy = mgr->readKey(S);
    fSkin = mgr->readKey(S);
}

void pfGUIControlMod::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    if (fFlags[kHasProxy] && !fProxy.Exists())
        fFlags[kHasProxy] = false;
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

    if (fColorScheme) {
        S->writeBool(true);
        fColorScheme->write(S);
    } else {
        S->writeBool(false);
    }

    S->writeByte(fSoundIndices.size());
    for (size_t i=0; i<fSoundIndices.size(); i++)
        S->writeInt(fSoundIndices[i]);

    if (fFlags[kHasProxy])
        mgr->writeKey(S, fProxy);
    mgr->writeKey(S, fSkin);
}

void pfGUIControlMod::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    if (fFlags[kHasProxy] && !fProxy.Exists())
        fFlags[kHasProxy] = false;
    prc->startTag("ControlParams");
    prc->writeParam("TagID", fTagID);
    prc->writeParam("Visible", fVisible);
    prc->endTag(true);

    prc->writeSimpleTag("Handler");
    pfGUICtrlProcWriteableObject::PrcWrite(prc, fHandler);
    prc->closeTag();

    prc->writeSimpleTag("DynTextLayer");
    plResManager::PrcWriteKey(prc, fDynTextLayer);
    prc->closeTag();
    prc->writeSimpleTag("DynTextMap");
    plResManager::PrcWriteKey(prc, fDynTextMap);
    prc->closeTag();

    if (fColorScheme) {
        fColorScheme->prcWrite(prc);
    } else {
        prc->startTag("pfGUIColorScheme");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }

    prc->writeSimpleTag("SoundIndices");
    for (size_t i=0; i<fSoundIndices.size(); i++) {
        prc->startTag("SoundIndex");
        prc->writeParam("value", fSoundIndices[i]);
        prc->endTag(true);
    }
    prc->closeTag();

    if (fFlags[kHasProxy]) {
        prc->writeSimpleTag("Proxy");
        plResManager::PrcWriteKey(prc, fProxy);
        prc->closeTag();
    }
    prc->writeSimpleTag("Skin");
    plResManager::PrcWriteKey(prc, fSkin);
    prc->closeTag();
}

void pfGUIControlMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ControlParams") {
        fTagID = tag->getParam("TagID", "0").to_uint();
        fVisible = tag->getParam("Visible", "true").to_bool();
    } else if (tag->getName() == "Handler") {
        if (tag->hasChildren())
            setHandler(pfGUICtrlProcWriteableObject::PrcParse(tag->getFirstChild()));
        else
            setHandler(nullptr);
    } else if (tag->getName() == "DynTextLayer") {
        if (tag->hasChildren())
            fDynTextLayer = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "DynTextMap") {
        if (tag->hasChildren())
            fDynTextMap = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "pfGUIColorScheme") {
        if (tag->getParam("NULL", "false").to_bool()) {
            setColorScheme(nullptr);
        } else {
            setColorScheme(new pfGUIColorScheme());
            fColorScheme->prcParse(tag);
        }
    } else if (tag->getName() == "SoundIndices") {
        fSoundIndices.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSoundIndices.size(); i++) {
            if (child->getName() != "SoundIndex")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fSoundIndices[i] = child->getParam("value", "0").to_int();
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Proxy") {
        if (tag->hasChildren())
            fProxy = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Skin") {
        if (tag->hasChildren())
            fSkin = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}

void pfGUIControlMod::setHandler(pfGUICtrlProcWriteableObject* handler)
{
    delete fHandler;
    fHandler = handler;
}

void pfGUIControlMod::setColorScheme(pfGUIColorScheme* scheme)
{
    delete fColorScheme;
    fColorScheme = scheme;
}
