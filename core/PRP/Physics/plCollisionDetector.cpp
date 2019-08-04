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

#include "plCollisionDetector.h"

/* plCollisionDetector */
void plCollisionDetector::read(hsStream* S, plResManager* mgr)
{
    plDetectorModifier::read(S, mgr);
    fType = S->readByte();
}

void plCollisionDetector::write(hsStream* S, plResManager* mgr)
{
    plDetectorModifier::write(S, mgr);
    S->writeByte(fType);
}

void plCollisionDetector::IPrcWrite(pfPrcHelper* prc)
{
    plDetectorModifier::IPrcWrite(prc);

    prc->startTag("CollisionType");
    prc->writeParam("value", fType);
    prc->endTag(true);
}

void plCollisionDetector::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "CollisionType") {
        fType = tag->getParam("value", "0").to_uint();
    } else {
        plDetectorModifier::IPrcParse(tag, mgr);
    }
}


/* plSubworldRegionDetector */
void plSubworldRegionDetector::read(hsStream* S, plResManager* mgr)
{
    plDetectorModifier::read(S, mgr);   // <-- Not a bug
    fSub = mgr->readKey(S);
    fOnExit = S->readBool();
}

void plSubworldRegionDetector::write(hsStream* S, plResManager* mgr)
{
    plDetectorModifier::write(S, mgr);  // <-- Not a bug
    mgr->writeKey(S, fSub);
    S->writeBool(fOnExit);
}

void plSubworldRegionDetector::IPrcWrite(pfPrcHelper* prc)
{
    plDetectorModifier::IPrcWrite(prc); // <-- Not a bug

    prc->startTag("SubworldParams");
    prc->writeParam("OnExit", fOnExit);
    prc->endTag(true);

    prc->writeSimpleTag("Subworld");
    plResManager::PrcWriteKey(prc, fSub);
    prc->closeTag();
}

void plSubworldRegionDetector::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SubworldParams") {
        fOnExit = tag->getParam("OnExit", "false").to_bool();
    } else if (tag->getName() == "Subworld") {
        if (tag->hasChildren())
            fSub = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plDetectorModifier::IPrcParse(tag, mgr);    // <-- Not a bug
    }
}


/* plPanicLinkRegion */
void plPanicLinkRegion::read(hsStream* S, plResManager* mgr)
{
    plCollisionDetector::read(S, mgr);
    fPlayLinkOutAnim = S->readBool();
}

void plPanicLinkRegion::write(hsStream* S, plResManager* mgr)
{
    plCollisionDetector::write(S, mgr);
    S->writeBool(fPlayLinkOutAnim);
}

void plPanicLinkRegion::IPrcWrite(pfPrcHelper* prc)
{
    plCollisionDetector::IPrcWrite(prc);

    prc->startTag("PanicLinkParams");
    prc->writeParam("PlayLinkOutAnim", fPlayLinkOutAnim);
    prc->endTag(true);
}

void plPanicLinkRegion::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "PanicLinkParams") {
        fPlayLinkOutAnim = tag->getParam("PlayLinkOutAnim", "true").to_bool();
    } else {
        plCollisionDetector::IPrcParse(tag, mgr);
    }
}
