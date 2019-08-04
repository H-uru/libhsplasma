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

#include "plActivatorConditionalObject.h"

/* plActivatorConditionalObject */
void plActivatorConditionalObject::read(hsStream* S, plResManager* mgr)
{
    plConditionalObject::read(S, mgr);
    fActivators.resize(S->readInt());
    for (size_t i=0; i<fActivators.size(); i++)
        fActivators[i] = mgr->readKey(S);
}

void plActivatorConditionalObject::write(hsStream* S, plResManager* mgr)
{
    plConditionalObject::write(S, mgr);
    S->writeInt(fActivators.size());
    for (size_t i=0; i<fActivators.size(); i++)
        mgr->writeKey(S, fActivators[i]);
}

void plActivatorConditionalObject::IPrcWrite(pfPrcHelper* prc)
{
    plConditionalObject::IPrcWrite(prc);
    prc->writeSimpleTag("Activators");
    for (size_t i=0; i<fActivators.size(); i++)
        plResManager::PrcWriteKey(prc, fActivators[i]);
    prc->closeTag();
}

void plActivatorConditionalObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Activators") {
        fActivators.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fActivators.size(); i++) {
            fActivators[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plConditionalObject::IPrcParse(tag, mgr);
    }
}
