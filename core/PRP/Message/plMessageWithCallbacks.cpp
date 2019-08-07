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

#include "plMessageWithCallbacks.h"

plMessageWithCallbacks::~plMessageWithCallbacks()
{
    for (auto cback = fCallbacks.begin(); cback != fCallbacks.end(); ++cback)
        delete *cback;
}

void plMessageWithCallbacks::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);

    clearCallbacks();
    fCallbacks.resize(S->readInt());
    for (size_t i=0; i<fCallbacks.size(); i++) {
        fCallbacks[i] = mgr->ReadCreatableC<plMessage>(S);
        if (fCallbacks[i] == nullptr)
            throw hsNotImplementedException(__FILE__, __LINE__, "Callback Message");
    }
}

void plMessageWithCallbacks::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);

    S->writeInt(fCallbacks.size());
    for (size_t i=0; i<fCallbacks.size(); i++)
        mgr->WriteCreatable(S, fCallbacks[i]);
}

void plMessageWithCallbacks::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);

    prc->writeSimpleTag("Callbacks");
    for (size_t i=0; i<fCallbacks.size(); i++)
        fCallbacks[i]->prcWrite(prc);
    prc->closeTag();
}

void plMessageWithCallbacks::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Callbacks") {
        clearCallbacks();
        fCallbacks.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fCallbacks.size(); i++) {
            fCallbacks[i] = mgr->prcParseCreatableC<plMessage>(child);
            child = child->getNextSibling();
        }
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}

void plMessageWithCallbacks::delCallback(size_t idx)
{
    delete fCallbacks[idx];
    fCallbacks.erase(fCallbacks.begin() + idx);
}

void plMessageWithCallbacks::clearCallbacks()
{
    for (auto cback = fCallbacks.begin(); cback != fCallbacks.end(); ++cback)
        delete *cback;
    fCallbacks.clear();
}
