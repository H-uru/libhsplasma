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

#include "plPhysicalSndGroup.h"

void plPhysicalSndGroup::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fGroup = S->readInt();
    fImpactSounds.setSize(S->readInt());
    for (size_t i=0; i<fImpactSounds.getSize(); i++)
        fImpactSounds[i] = mgr->readKey(S);
    fSlideSounds.setSize(S->readInt());
    for (size_t i=0; i<fSlideSounds.getSize(); i++)
        fSlideSounds[i] = mgr->readKey(S);
}

void plPhysicalSndGroup::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    S->writeInt(fGroup);
    S->writeInt(fImpactSounds.getSize());
    for (size_t i=0; i<fImpactSounds.getSize(); i++)
        mgr->writeKey(S, fImpactSounds[i]);
    S->writeInt(fSlideSounds.getSize());
    for (size_t i=0; i<fSlideSounds.getSize(); i++)
        mgr->writeKey(S, fSlideSounds[i]);
}

void plPhysicalSndGroup::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    prc->startTag("SoundGroupParams");
    prc->writeParam("Group", fGroup);
    prc->endTag(true);

    prc->writeSimpleTag("ImpactSounds");
    for (size_t i=0; i<fImpactSounds.getSize(); i++)
        fImpactSounds[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SlideSounds");
    for (size_t i=0; i<fSlideSounds.getSize(); i++)
        fSlideSounds[i]->prcWrite(prc);
    prc->closeTag();
}

void plPhysicalSndGroup::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SoundGroupParams") {
        fGroup = tag->getParam("Group", "0").toUint();
    } else if (tag->getName() == "ImpactSounds") {
        fImpactSounds.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fImpactSounds.getSize(); i++) {
            fImpactSounds[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "SlideSounds") {
        fSlideSounds.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSlideSounds.getSize(); i++) {
            fSlideSounds[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
