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

#include "plGameMarkerModifier.h"

void plGameMarkerModifier::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    fGreenAnimKey = mgr->readKey(S);
    fRedAnimKey = mgr->readKey(S);
    fOpenAnimKey = mgr->readKey(S);
    fBounceAnimKey = mgr->readKey(S);
    fPlaceSoundIdx = S->readShort();
    fHitSoundIdx = S->readShort();
}

void plGameMarkerModifier::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    mgr->writeKey(S, fGreenAnimKey);
    mgr->writeKey(S, fRedAnimKey);
    mgr->writeKey(S, fOpenAnimKey);
    mgr->writeKey(S, fBounceAnimKey);
    S->writeShort(fPlaceSoundIdx);
    S->writeShort(fHitSoundIdx);
}

void plGameMarkerModifier::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->writeSimpleTag("GreenAnim");
    plResManager::PrcWriteKey(prc, fGreenAnimKey);
    prc->closeTag();

    prc->writeSimpleTag("RedAnim");
    plResManager::PrcWriteKey(prc, fRedAnimKey);
    prc->closeTag();

    prc->writeSimpleTag("OpenAnim");
    plResManager::PrcWriteKey(prc, fOpenAnimKey);
    prc->closeTag();

    prc->writeSimpleTag("BounceAnim");
    plResManager::PrcWriteKey(prc, fBounceAnimKey);
    prc->closeTag();

    prc->startTag("SoundIndices");
    prc->writeParam("Place", fPlaceSoundIdx);
    prc->writeParam("Hit", fHitSoundIdx);
    prc->endTag(true);
}

void plGameMarkerModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "GreenAnim") {
        if (tag->hasChildren())
            fGreenAnimKey = mgr->prcParseKey(tag);
    } else if (tag->getName() == "RedAnim") {
        if (tag->hasChildren())
            fRedAnimKey = mgr->prcParseKey(tag);
    } else if (tag->getName() == "OpenAnim") {
        if (tag->hasChildren())
            fOpenAnimKey = mgr->prcParseKey(tag);
    } else if (tag->getName() == "BounceAnim") {
        if (tag->hasChildren())
            fBounceAnimKey = mgr->prcParseKey(tag);
    } else if (tag->getName() == "SoundIndices") {
        fPlaceSoundIdx = tag->getParam("Place", "0").to_uint();
        fHitSoundIdx = tag->getParam("Hit", "0").to_uint();
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
