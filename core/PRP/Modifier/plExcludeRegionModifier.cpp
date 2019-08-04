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

#include "plExcludeRegionModifier.h"

void plExcludeRegionModifier::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    fSafePoints.resize(S->readInt());
    for (size_t i=0; i<fSafePoints.size(); i++)
        fSafePoints[i] = mgr->readKey(S);
    fSeek = S->readBool();
    fSeekTime = S->readFloat();
}

void plExcludeRegionModifier::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    S->writeInt(fSafePoints.size());
    for (size_t i=0; i<fSafePoints.size(); i++)
        mgr->writeKey(S, fSafePoints[i]);
    S->writeBool(fSeek);
    S->writeFloat(fSeekTime);
}

void plExcludeRegionModifier::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("ExcludeRegionParams");
    prc->writeParam("Seek", fSeek);
    prc->writeParam("SeekTime", fSeekTime);
    prc->endTag(true);

    prc->writeSimpleTag("SafePoints");
    for (size_t i=0; i<fSafePoints.size(); i++)
        plResManager::PrcWriteKey(prc, fSafePoints[i]);
    prc->closeTag();
}

void plExcludeRegionModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ExcludeRegionParams") {
        fSeek = tag->getParam("Seek", "false").to_bool();
        fSeekTime = tag->getParam("SeekTime", "0").to_float();
    } else if (tag->getName() == "SafePoints") {
        fSafePoints.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSafePoints.size(); i++) {
            fSafePoints[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
