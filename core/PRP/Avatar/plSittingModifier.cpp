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

#include "plSittingModifier.h"

void plSittingModifier::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    fMiscFlags = S->readByte();
    fNotifyKeys.resize(S->readInt());
    for (size_t i=0; i<fNotifyKeys.size(); i++)
        fNotifyKeys[i] = mgr->readKey(S);
}

void plSittingModifier::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    S->writeByte(fMiscFlags);
    S->writeInt(fNotifyKeys.size());
    for (size_t i=0; i<fNotifyKeys.size(); i++)
        mgr->writeKey(S, fNotifyKeys[i]);
}

void plSittingModifier::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("SittingModParams");
    prc->writeParamHex("MiscFlags", fMiscFlags);
    prc->endTag(true);

    prc->writeSimpleTag("NotifyKeys");
    for (size_t i=0; i<fNotifyKeys.size(); i++)
        plResManager::PrcWriteKey(prc, fNotifyKeys[i]);
    prc->closeTag();
}

void plSittingModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SittingModParams") {
        fMiscFlags = tag->getParam("MiscFlags", "0").to_uint();
    } else if (tag->getName() == "NotifyKeys") {
        fNotifyKeys.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fNotifyKeys.size(); i++) {
            fNotifyKeys[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
