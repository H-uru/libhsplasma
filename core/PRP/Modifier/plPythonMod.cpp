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

#include "plPythonMod.h"

/* plPythonMod */
plPythonMod::~plPythonMod()
{
    delete[] fPythonCode;
}

void plPythonMod::read(hsStream* S, plResManager* mgr)
{
    plMultiModifier::read(S, mgr);

    delete[] fPythonCode;
    fPythonSize = S->readInt();
    fPythonCode = new unsigned char[fPythonSize];
    S->read(fPythonSize, fPythonCode);

    fReceivers.resize(S->readInt());
    for (size_t i=0; i<fReceivers.size(); i++)
        fReceivers[i] = mgr->readKey(S);

    fAnimNotetracks.resize(S->readInt());
    for (size_t i=0; i<fAnimNotetracks.size(); i++) {
        fAnimNotetracks[i].objKey = mgr->readKey(S);
        int size = S->readInt();
        fAnimNotetracks[i].note_name = S->readStr(size);
        S->readByte();  // Terminating 0
        fAnimNotetracks[i].modKey = mgr->readKey(S);
    }

    fSoundName2Idx.resize(S->readInt());
    for (size_t i=0; i<fSoundName2Idx.size(); i++) {
        int size = S->readInt();
        fSoundName2Idx[i].sound_name = S->readStr(size);
        S->readByte();  // Terminating 0
        fSoundName2Idx[i].sound_index = S->readInt();
    }

    fMaterialAnim.resize(S->readInt());
    for (size_t i=0; i<fMaterialAnim.size(); i++) {
        int size = S->readInt();
        fMaterialAnim[i].material_name = S->readStr(size);
        S->readByte();  // Terminating 0
        size = S->readInt();
        fMaterialAnim[i].note_name = S->readStr(size);
        S->readByte();  // Terminating 0
        fMaterialAnim[i].modKey = mgr->readKey(S);
    }
}

void plPythonMod::write(hsStream* S, plResManager* mgr)
{
    plMultiModifier::write(S, mgr);

    S->writeInt(fPythonSize);
    S->write(fPythonSize, fPythonCode);

    S->writeInt(fReceivers.size());
    for (size_t i=0; i<fReceivers.size(); i++)
        mgr->writeKey(S, fReceivers[i]);

    S->writeInt(fAnimNotetracks.size());
    for (size_t i=0; i<fAnimNotetracks.size(); i++) {
        mgr->writeKey(S, fAnimNotetracks[i].objKey);
        S->writeInt(fAnimNotetracks[i].note_name.size());
        S->writeStr(fAnimNotetracks[i].note_name);
        S->writeByte(0);
        mgr->writeKey(S, fAnimNotetracks[i].modKey);
    }

    S->writeInt(fSoundName2Idx.size());
    for (size_t i=0; i<fSoundName2Idx.size(); i++) {
        S->writeInt(fSoundName2Idx[i].sound_name.size());
        S->writeStr(fSoundName2Idx[i].sound_name);
        S->writeByte(0);
        S->writeInt(fSoundName2Idx[i].sound_index);
    }

    S->writeInt(fMaterialAnim.size());
    for (size_t i=0; i<fMaterialAnim.size(); i++) {
        S->writeInt(fMaterialAnim[i].material_name.size());
        S->writeStr(fMaterialAnim[i].material_name);
        S->writeByte(0);
        S->writeInt(fMaterialAnim[i].note_name.size());
        S->writeStr(fMaterialAnim[i].note_name);
        S->writeByte(0);
        mgr->writeKey(S, fMaterialAnim[i].modKey);
    }
}

void plPythonMod::IPrcWrite(pfPrcHelper* prc)
{
    plMultiModifier::IPrcWrite(prc);

    prc->writeSimpleTag("PythonCode");
    prc->writeHexStream(fPythonSize, fPythonCode);
    prc->closeTag();

    prc->writeSimpleTag("Receivers");
    for (size_t i=0; i<fReceivers.size(); i++)
        plResManager::PrcWriteKey(prc, fReceivers[i]);
    prc->closeTag();

    prc->writeSimpleTag("NotetrackRecs");
    for (size_t i=0; i<fAnimNotetracks.size(); i++) {
        prc->startTag("PythonAnimNotetrack");
        prc->writeParam("NoteName", fAnimNotetracks[i].note_name);
        prc->endTag();

        prc->writeSimpleTag("ObjKey");
        plResManager::PrcWriteKey(prc, fAnimNotetracks[i].objKey);
        prc->closeTag();

        prc->writeSimpleTag("ModKey");
        plResManager::PrcWriteKey(prc, fAnimNotetracks[i].modKey);
        prc->closeTag();

        prc->closeTag();
    }
    prc->closeTag();

    prc->writeSimpleTag("SoundIdxRecs");
    for (size_t i=0; i<fSoundName2Idx.size(); i++) {
        prc->startTag("PythonSound2Index");
        prc->writeParam("SoundName", fSoundName2Idx[i].sound_name);
        prc->writeParam("SoundIndex", fSoundName2Idx[i].sound_index);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->writeSimpleTag("MaterialAnims");
    for (size_t i=0; i<fMaterialAnim.size(); i++) {
        prc->startTag("MaterialAnim");
        prc->writeParam("MaterialName", fMaterialAnim[i].material_name);
        prc->writeParam("NoteName", fMaterialAnim[i].note_name);
        prc->endTag();

        prc->writeSimpleTag("ModKey");
        plResManager::PrcWriteKey(prc, fMaterialAnim[i].modKey);
        prc->closeTag();

        prc->closeTag();
    }
    prc->closeTag();
}

void plPythonMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "PythonCode") {
        delete[] fPythonCode;
        fPythonSize = tag->getContents().size();
        fPythonCode = new unsigned char[fPythonSize];
        tag->readHexStream(fPythonSize, fPythonCode);
    } else if (tag->getName() == "Receivers") {
        fReceivers.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fReceivers.size(); i++) {
            fReceivers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "NotetrackRecs") {
        fAnimNotetracks.resize(tag->countChildren());
        const pfPrcTag* rec = tag->getFirstChild();
        for (size_t i=0; i<fAnimNotetracks.size(); i++) {
            if (rec->getName() != "PythonAnimNotetrack")
                throw pfPrcTagException(__FILE__, __LINE__, rec->getName());

            fAnimNotetracks[i].note_name = rec->getParam("NoteName", "");
            const pfPrcTag* child = rec->getFirstChild();
            while (child) {
                if (child->getName() == "ObjKey") {
                    if (child->hasChildren())
                        fAnimNotetracks[i].objKey = mgr->prcParseKey(child->getFirstChild());
                } else if (child->getName() == "ModKey") {
                    if (child->hasChildren())
                        fAnimNotetracks[i].modKey = mgr->prcParseKey(child->getFirstChild());
                } else {
                    throw pfPrcTagException(__FILE__, __LINE__, child->getName());
                }
                child = child->getNextSibling();
            }
            rec = rec->getNextSibling();
        }
    } else if (tag->getName() == "SoundIdxRecs") {
        fSoundName2Idx.resize(tag->countChildren());
        const pfPrcTag* rec = tag->getFirstChild();
        for (size_t i=0; i<fSoundName2Idx.size(); i++) {
            if (rec->getName() != "PythonSound2Index")
                throw pfPrcTagException(__FILE__, __LINE__, rec->getName());

            fSoundName2Idx[i].sound_name = rec->getParam("SoundName", "");
            fSoundName2Idx[i].sound_index = rec->getParam("SoundIndex", "").to_int();
            rec = rec->getNextSibling();
        }
    } else if (tag->getName() == "MaterialAnims") {
        fMaterialAnim.resize(tag->countChildren());
        const pfPrcTag* rec = tag->getFirstChild();
        for (size_t i=0; i<fMaterialAnim.size(); i++) {
            if (rec->getName() != "MaterialAnim")
                throw pfPrcTagException(__FILE__, __LINE__, rec->getName());

            fMaterialAnim[i].material_name = rec->getParam("MaterialName", "");
            fMaterialAnim[i].note_name = rec->getParam("NoteName", "");
            const pfPrcTag* child = rec->getFirstChild();
            while (child) {
                if (child->getName() == "ModKey") {
                    if (child->hasChildren())
                        fMaterialAnim[i].modKey = mgr->prcParseKey(child->getFirstChild());
                } else {
                    throw pfPrcTagException(__FILE__, __LINE__, child->getName());
                }
                child = child->getNextSibling();
            }
            rec = rec->getNextSibling();
        }
    } else {
        plMultiModifier::IPrcParse(tag, mgr);
    }
}
