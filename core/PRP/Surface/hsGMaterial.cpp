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

#include "hsGMaterial.h"

void hsGMaterial::read(hsStream* S, plResManager* mgr)
{
    plSynchedObject::read(S, mgr);

    fLoadFlags = S->readInt();
    fCompFlags = S->readInt();
    fLayers.resize(S->readInt());
    fPiggyBacks.resize(S->readInt());

    for (size_t i=0; i<fLayers.size(); i++)
        fLayers[i] = mgr->readKey(S);
    for (size_t i=0; i<fPiggyBacks.size(); i++)
        fPiggyBacks[i] = mgr->readKey(S);
}

void hsGMaterial::write(hsStream* S, plResManager* mgr)
{
    plSynchedObject::write(S, mgr);

    S->writeInt(fLoadFlags);
    S->writeInt(fCompFlags);
    S->writeInt(fLayers.size());
    S->writeInt(fPiggyBacks.size());

    for (size_t i=0; i<fLayers.size(); i++)
        mgr->writeKey(S, fLayers[i]);
    for (size_t i=0; i<fPiggyBacks.size(); i++)
        mgr->writeKey(S, fPiggyBacks[i]);
}

void hsGMaterial::IPrcWrite(pfPrcHelper* prc)
{
    plSynchedObject::IPrcWrite(prc);

    prc->startTag("MaterialParams");
    prc->writeParamHex("LoadFlags", fLoadFlags);
    prc->writeParamHex("CompFlags", fCompFlags);
    prc->endTag(true);

    prc->writeSimpleTag("Layers");
    for (size_t i=0; i<fLayers.size(); i++)
        plResManager::PrcWriteKey(prc, fLayers[i]);
    prc->closeTag();
    prc->writeSimpleTag("PiggyBacks");
    for (size_t i=0; i<fPiggyBacks.size(); i++)
        plResManager::PrcWriteKey(prc, fPiggyBacks[i]);
    prc->closeTag();
}

void hsGMaterial::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "MaterialParams") {
        fLoadFlags = tag->getParam("LoadFlags", "0").to_uint();
        fCompFlags = tag->getParam("CompFlags", "0").to_uint();
    } else if (tag->getName() == "Layers") {
        fLayers.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fLayers.size(); i++) {
            fLayers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "PiggyBacks") {
        fPiggyBacks.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fPiggyBacks.size(); i++) {
            fPiggyBacks[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSynchedObject::IPrcParse(tag, mgr);
    }
}
