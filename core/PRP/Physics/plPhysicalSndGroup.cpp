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

void plPhysicalSndGroup::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);

    fGroup = S->readInt();
    fImpactSounds.resize(S->readInt());
    for (size_t i=0; i<fImpactSounds.size(); i++)
        fImpactSounds[i] = mgr->readKey(S);
    fSlideSounds.resize(S->readInt());
    for (size_t i=0; i<fSlideSounds.size(); i++)
        fSlideSounds[i] = mgr->readKey(S);
}

void plPhysicalSndGroup::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);

    S->writeInt(fGroup);
    S->writeInt(fImpactSounds.size());
    for (size_t i=0; i<fImpactSounds.size(); i++)
        mgr->writeKey(S, fImpactSounds[i]);
    S->writeInt(fSlideSounds.size());
    for (size_t i=0; i<fSlideSounds.size(); i++)
        mgr->writeKey(S, fSlideSounds[i]);
}

void plPhysicalSndGroup::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);

    prc->startTag("SoundGroupParams");
    prc->writeParam("Group", fGroup);
    prc->endTag(true);

    prc->writeSimpleTag("ImpactSounds");
    for (size_t i=0; i<fImpactSounds.size(); i++)
        plResManager::PrcWriteKey(prc, fImpactSounds[i]);
    prc->closeTag();

    prc->writeSimpleTag("SlideSounds");
    for (size_t i=0; i<fSlideSounds.size(); i++)
        plResManager::PrcWriteKey(prc, fSlideSounds[i]);
    prc->closeTag();
}

void plPhysicalSndGroup::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SoundGroupParams") {
        fGroup = tag->getParam("Group", "0").to_uint();
    } else if (tag->getName() == "ImpactSounds") {
        fImpactSounds.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fImpactSounds.size(); i++) {
            fImpactSounds[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "SlideSounds") {
        fSlideSounds.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSlideSounds.size(); i++) {
            fSlideSounds[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
