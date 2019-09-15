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

#include "plLineFollowMod.h"

/* plLineFollowMod */
plLineFollowMod::~plLineFollowMod()
{
    delete fPath;
}

void plLineFollowMod::read(hsStream* S, plResManager* mgr)
{
    plMultiModifier::read(S, mgr);

    setPath(mgr->ReadCreatableC<plAnimPath>(S));
    fPathParent = mgr->readKey(S);
    fRefObj = mgr->readKey(S);

    fStereizers.resize(S->readInt());
    for (size_t i=0; i<fStereizers.size(); i++)
        fStereizers[i] = mgr->readKey(S);

    unsigned int modeFlags = S->readInt();
    fFollowMode = (FollowMode)(modeFlags & 0xFFFF);
    fFollowFlags = modeFlags >> 16;
    if (fFollowFlags & kOffset)
        fOffset = S->readFloat();
    if (fFollowFlags & kOffsetClamp)
        fOffsetClamp = S->readFloat();
    if (fFollowFlags & kSpeedClamp)
        fSpeedClamp = S->readFloat();
}

void plLineFollowMod::write(hsStream* S, plResManager* mgr)
{
    plMultiModifier::write(S, mgr);

    mgr->WriteCreatable(S, fPath);
    mgr->writeKey(S, fPathParent);
    mgr->writeKey(S, fRefObj);

    S->writeInt(fStereizers.size());
    for (size_t i=0; i<fStereizers.size(); i++)
        mgr->writeKey(S, fStereizers[i]);

    S->writeInt((fFollowFlags << 16) | fFollowMode);
    if (fFollowFlags & kOffset)
        S->writeFloat(fOffset);
    if (fFollowFlags & kOffsetClamp)
        S->writeFloat(fOffsetClamp);
    if (fFollowFlags & kSpeedClamp)
        S->writeFloat(fSpeedClamp);
}

void plLineFollowMod::IPrcWrite(pfPrcHelper* prc)
{
    plMultiModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Path");
      fPath->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Parent");
      plResManager::PrcWriteKey(prc, fPathParent);
    prc->closeTag();
    prc->writeSimpleTag("RefObj");
      plResManager::PrcWriteKey(prc, fRefObj);
    prc->closeTag();

    prc->writeSimpleTag("Stereizers");
    for (size_t i=0; i<fStereizers.size(); i++)
        plResManager::PrcWriteKey(prc, fStereizers[i]);
    prc->closeTag();

    prc->startTag("LineFollowParams");
      prc->writeParamHex("FollowFlags", fFollowFlags);
      prc->writeParam("FollowMode", fFollowMode);
      if (fFollowFlags & kOffset)
        prc->writeParam("Offset", fOffset);
      if (fFollowFlags & kOffsetClamp)
        prc->writeParam("OffsetClamp", fOffsetClamp);
      if (fFollowFlags & kSpeedClamp)
        prc->writeParam("SpeedClamp", fSpeedClamp);
    prc->endTag(true);
}

void plLineFollowMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Path") {
        if (tag->hasChildren())
            setPath(mgr->prcParseCreatableC<plAnimPath>(tag->getFirstChild()));
    } else if (tag->getName() == "Parent") {
        if (tag->hasChildren())
            fPathParent = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "RefObj") {
        if (tag->hasChildren())
            fRefObj = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Stereizers") {
        fStereizers.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fStereizers.size(); i++) {
            fStereizers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "LineFollowParams") {
        fFollowFlags = tag->getParam("FollowFlags", "0").to_uint();
        fFollowMode = (FollowMode)tag->getParam("FollowMode", "0").to_int();
        fOffset = tag->getParam("Offset", "0").to_float();
        fOffsetClamp = tag->getParam("OffsetClamp", "0").to_float();
        fSpeedClamp = tag->getParam("SpeedClamp", "0").to_float();
    } else {
        plMultiModifier::IPrcParse(tag, mgr);
    }
}

void plLineFollowMod::setPath(plAnimPath* path)
{
    delete fPath;
    fPath = path;
}
