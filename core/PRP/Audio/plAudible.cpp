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

#include "plAudible.h"

/* plWinAudible */
void plWinAudible::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);

    fSoundObjs.resize(S->readInt());
    for (size_t i=0; i<fSoundObjs.size(); i++)
        fSoundObjs[i] = mgr->readKey(S);
    fSceneNode = mgr->readKey(S);
}

void plWinAudible::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);

    S->writeInt(fSoundObjs.size());
    for (size_t i=0; i<fSoundObjs.size(); i++)
        mgr->writeKey(S, fSoundObjs[i]);
    mgr->writeKey(S, fSceneNode);
}

void plWinAudible::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("SoundObjects");
    for (size_t i=0; i<fSoundObjs.size(); i++)
        plResManager::PrcWriteKey(prc, fSoundObjs[i]);
    prc->closeTag();
    prc->writeSimpleTag("SceneNode");
    plResManager::PrcWriteKey(prc, fSceneNode);
    prc->closeTag();
}

void plWinAudible::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SoundObjects") {
        fSoundObjs.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSoundObjs.size(); i++) {
            fSoundObjs[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "SceneNode") {
        if (tag->hasChildren())
            fSceneNode = mgr->prcParseKey(tag->getFirstChild());
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
