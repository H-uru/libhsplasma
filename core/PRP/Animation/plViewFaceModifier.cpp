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

#include "plViewFaceModifier.h"

void plViewFaceModifier::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    fScale.read(S);
    fLocalToParent.read(S);
    fParentToLocal.read(S);
    if (fFlags[kFaceObj])
        fFaceObj = mgr->readKey(S);
    fOffset.read(S);
    if (fFlags[kMaxBounds])
        fMaxBounds.read(S);
}

void plViewFaceModifier::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    fScale.write(S);
    fLocalToParent.write(S);
    fParentToLocal.write(S);
    if (fFlags[kFaceObj])
        mgr->writeKey(S, fFaceObj);
    fOffset.write(S);
    if (fFlags[kMaxBounds])
        fMaxBounds.write(S);
}

void plViewFaceModifier::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Scale");
    fScale.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("LocalToParent");
    fLocalToParent.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("ParentToLocal");
    fParentToLocal.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Offset");
    fOffset.prcWrite(prc);
    prc->closeTag();

    if (fFlags[kFaceObj]) {
        prc->writeSimpleTag("FaceObj");
        plResManager::PrcWriteKey(prc, fFaceObj);
        prc->closeTag();
    }

    if (fFlags[kMaxBounds]) {
        prc->writeSimpleTag("MaxBounds");
        fMaxBounds.prcWrite(prc);
        prc->closeTag();
    }
}

void plViewFaceModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Scale") {
        if (tag->hasChildren())
            fScale.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "LocalToParent") {
        if (tag->hasChildren())
            fLocalToParent.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "ParentToLocal") {
        if (tag->hasChildren())
            fParentToLocal.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Offset") {
        if (tag->hasChildren())
            fOffset.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "FaceObj") {
        if (tag->hasChildren())
            fFaceObj = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "MaxBounds") {
        if (tag->hasChildren())
            fMaxBounds.prcParse(tag->getFirstChild());
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
