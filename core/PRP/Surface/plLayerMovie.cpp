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

#include "plLayerMovie.h"

/* plLayerMovie */
void plLayerMovie::read(hsStream* S, plResManager* mgr)
{
    plLayerAnimation::read(S, mgr);

    int len = S->readInt();
    fMovieName = S->readStr(len);

    if (S->getVer().isNewPlasma()) {
        fEoaKey1 = mgr->readKey(S);
        fEoaKey2 = mgr->readKey(S);

        fEoaInt = S->readInt();
    }
}

void plLayerMovie::write(hsStream* S, plResManager* mgr)
{
    plLayerAnimation::write(S, mgr);

    S->writeInt(fMovieName.size());
    S->writeStr(fMovieName);

    if (S->getVer().isNewPlasma()) {
        mgr->writeKey(S, fEoaKey1);
        mgr->writeKey(S, fEoaKey2);

        S->writeInt(fEoaInt);
    }
}

void plLayerMovie::IPrcWrite(pfPrcHelper* prc)
{
    plLayerAnimation::IPrcWrite(prc);

    prc->startTag("Movie");
    prc->writeParam("Name", fMovieName);
    prc->endTag(true);

    prc->writeSimpleTag("EoaKey1");
    plResManager::PrcWriteKey(prc, fEoaKey1);
    prc->closeTag();

    prc->writeSimpleTag("EoaKey2");
    plResManager::PrcWriteKey(prc, fEoaKey2);
    prc->closeTag();

    prc->startTag("EoaInt");
    prc->writeParam("Value", fEoaInt);
    prc->endTag(true);
}

void plLayerMovie::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Movie") {
        fMovieName = tag->getParam("Name", "");
    } else if (tag->getName() == "EoaKey1") {
        if (tag->hasChildren())
            fEoaKey1 = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "EoaKey2") {
        if (tag->hasChildren())
            fEoaKey2 = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "EoaInt") {
        fEoaInt = tag->getParam("Value", "0").to_uint();
    } else {
        plLayerAnimation::IPrcParse(tag, mgr);
    }
}
