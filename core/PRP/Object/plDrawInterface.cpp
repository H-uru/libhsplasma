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

#include "plDrawInterface.h"

/* plDrawInterface */
void plDrawInterface::read(hsStream* S, plResManager* mgr)
{
    plObjInterface::read(S, mgr);

    fDrawables.resize(S->readInt());
    fDrawableKeys.resize(fDrawables.size());
    for (size_t i=0; i<fDrawables.size(); i++) {
        fDrawableKeys[i] = S->readInt();
        fDrawables[i] = mgr->readKey(S);
    }
    fRegions.resize(S->readInt());
    for (size_t i=0; i<fRegions.size(); i++)
        fRegions[i] = mgr->readKey(S);
}

void plDrawInterface::write(hsStream* S, plResManager* mgr)
{
    plObjInterface::write(S, mgr);

    S->writeInt(fDrawables.size());
    for (size_t i=0; i<fDrawables.size(); i++) {
        S->writeInt(fDrawableKeys[i]);
        mgr->writeKey(S, fDrawables[i]);
    }
    S->writeInt(fRegions.size());
    for (size_t i=0; i<fRegions.size(); i++)
        mgr->writeKey(S, fRegions[i]);
}

void plDrawInterface::IPrcWrite(pfPrcHelper* prc)
{
    plObjInterface::IPrcWrite(prc);

    prc->writeSimpleTag("Drawables");
    for (size_t i=0; i<fDrawables.size(); i++) {
        prc->startTag("Drawable");
        prc->writeParam("key", fDrawableKeys[i]);
        prc->endTag();
        plResManager::PrcWriteKey(prc, fDrawables[i]);
        prc->closeTag();
    }
    prc->closeTag();
    prc->writeSimpleTag("Regions");
    for (size_t i=0; i<fRegions.size(); i++)
        plResManager::PrcWriteKey(prc, fRegions[i]);
    prc->closeTag();
}

void plDrawInterface::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Drawables") {
        fDrawables.resize(tag->countChildren());
        fDrawableKeys.resize(fDrawables.size());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fDrawables.size(); i++) {
            if (child->getName() != "Drawable")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fDrawableKeys[i] = child->getParam("key", "0").to_int();
            if (child->hasChildren())
                fDrawables[i] = mgr->prcParseKey(child->getFirstChild());
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Regions") {
        fRegions.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fRegions.size(); i++) {
            fRegions[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}

void plDrawInterface::clearDrawables()
{
    fDrawables.clear();
    fDrawableKeys.clear();
}

void plDrawInterface::addDrawable(plKey draw, int key)
{
    fDrawables.emplace_back(std::move(draw));
    fDrawableKeys.push_back(key);
}

void plDrawInterface::delDrawable(size_t idx)
{
    fDrawables.erase(fDrawables.begin() + idx);
    fDrawableKeys.erase(fDrawableKeys.begin() + idx);
}


/* plInstanceDrawInterface */
void plInstanceDrawInterface::read(hsStream* S, plResManager* mgr)
{
    plDrawInterface::read(S, mgr);

    fTargetID = S->readInt();
    fDrawable = mgr->readKey(S);
}

void plInstanceDrawInterface::write(hsStream* S, plResManager* mgr)
{
    plDrawInterface::write(S, mgr);

    S->writeInt(fTargetID);
    mgr->writeKey(S, fDrawable);
}

void plInstanceDrawInterface::IPrcWrite(pfPrcHelper* prc)
{
    plDrawInterface::IPrcWrite(prc);

    prc->startTag("Target");
    prc->writeParam("ID", fTargetID);
    prc->endTag();
    plResManager::PrcWriteKey(prc, fDrawable);
    prc->closeTag();
}

void plInstanceDrawInterface::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Target") {
        fTargetID = tag->getParam("ID", "0").to_uint();
        if (tag->hasChildren())
            fDrawable = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plDrawInterface::IPrcParse(tag, mgr);
    }
}
