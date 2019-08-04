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

#include "plRandomSoundMod.h"

/* plRandomSoundModGroup */
void plRandomSoundModGroup::read(hsStream* S)
{
    fIndices.resize(S->readShort());
    fGroupedIdx = S->readShort();

    for (size_t i=0; i<fIndices.size(); i++)
        fIndices[i] = S->readShort();
}

void plRandomSoundModGroup::write(hsStream* S)
{
    S->writeShort(fIndices.size());
    S->writeShort(fGroupedIdx);

    for (size_t i=0; i<fIndices.size(); i++)
        S->writeShort(fIndices[i]);
}

void plRandomSoundModGroup::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("plRandomSoundModGroup");
    prc->writeParam("GroupedIdx", fGroupedIdx);
    prc->endTag();

    for (size_t i=0; i<fIndices.size(); i++) {
        prc->startTag("Sound");
        prc->writeParam("Index", fIndices[i]);
        prc->endTag(true);
    }

    prc->closeTag();
}

void plRandomSoundModGroup::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "plRandomSoundModGroup")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fGroupedIdx = tag->getParam("GroupedIdx", "0").to_int();
    fIndices.resize(tag->countChildren());
    const pfPrcTag* child = tag->getFirstChild();
    for (size_t i=0; i<fIndices.size(); i++) {
        if (child->getName() != "Sound")
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        fIndices[i] = child->getParam("Index", "0").to_uint();
        child = child->getNextSibling();
    }
}


/* plRandomSoundMod */
void plRandomSoundMod::read(hsStream* S, plResManager* mgr)
{
    plRandomCommandMod::read(S, mgr);

    fGroups.resize(S->readShort());
    for (size_t i=0; i<fGroups.size(); i++)
        fGroups[i].read(S);
}

void plRandomSoundMod::write(hsStream* S, plResManager* mgr)
{
    plRandomCommandMod::write(S, mgr);

    S->writeShort(fGroups.size());
    for (size_t i=0; i<fGroups.size(); i++)
        fGroups[i].write(S);
}

void plRandomSoundMod::IPrcWrite(pfPrcHelper* prc)
{
    plRandomCommandMod::IPrcWrite(prc);

    prc->writeSimpleTag("Groups");
    for (size_t i=0; i<fGroups.size(); i++)
        fGroups[i].prcWrite(prc);
    prc->closeTag();
}

void plRandomSoundMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Groups") {
        fGroups.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fGroups.size(); i++) {
            fGroups[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        plRandomCommandMod::IPrcParse(tag, mgr);
    }
}
