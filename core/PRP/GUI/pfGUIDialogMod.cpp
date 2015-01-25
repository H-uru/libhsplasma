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

#include "pfGUIDialogMod.h"

pfGUIDialogMod::pfGUIDialogMod() : fTagID(0), fVersion(0) {
    memset(fName, 0, 128);
    fFlags.setName(kModal, "kModal");
}

void pfGUIDialogMod::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fRenderMod = mgr->readKey(S);
    S->read(128, fName);

    fControls.resize(S->readInt());
    for (size_t i=0; i<fControls.size(); i++)
        fControls[i] = mgr->readKey(S);

    fTagID = S->readInt();
    fProcReceiver = mgr->readKey(S);

    fVersion = S->readInt();
    fColorScheme.read(S);
    fSceneNode = mgr->readKey(S);
}

void pfGUIDialogMod::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    mgr->writeKey(S, fRenderMod);
    S->write(128, fName);

    S->writeInt(fControls.size());
    for (size_t i=0; i<fControls.size(); i++)
        mgr->writeKey(S, fControls[i]);

    S->writeInt(fTagID);
    mgr->writeKey(S, fProcReceiver);
    S->writeInt(fVersion);
    fColorScheme.write(S);
    mgr->writeKey(S, fSceneNode);
}

void pfGUIDialogMod::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("DialogParams");
    prc->writeParam("Name", fName);
    prc->writeParam("TagID", fTagID);
    prc->writeParam("Version", fVersion);
    prc->endTag(true);

    prc->writeSimpleTag("RenderMod");
    plResManager::PrcWriteKey(prc, fRenderMod);
    prc->closeTag();

    prc->writeSimpleTag("Controls");
    for (size_t i=0; i<fControls.size(); i++)
        plResManager::PrcWriteKey(prc, fControls[i]);
    prc->closeTag();

    prc->writeSimpleTag("ProcReceiver");
    plResManager::PrcWriteKey(prc, fProcReceiver);
    prc->closeTag();
    fColorScheme.prcWrite(prc);
    prc->writeSimpleTag("SceneNode");
    plResManager::PrcWriteKey(prc, fSceneNode);
    prc->closeTag();
}

void pfGUIDialogMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "DialogParams") {
        plString tmp = tag->getParam("Name", "");
        strncpy(fName, tmp.cstr(), 128);
        fTagID = tag->getParam("TagID", "0").toUint();
        fVersion = tag->getParam("Version", "0").toUint();
    } else if (tag->getName() == "RenderMod") {
        if (tag->hasChildren())
            fRenderMod = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Controls") {
        fControls.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fControls.size(); i++) {
            fControls[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "ProcReceiver") {
        if (tag->hasChildren())
            fProcReceiver = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "SceneNode") {
        if (tag->hasChildren())
            fSceneNode = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "pfGUIColorScheme") {
        fColorScheme.prcParse(tag);
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
