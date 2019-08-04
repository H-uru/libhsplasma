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

#include "plLadderModifier.h"

/* plAvLadderMod */
void plAvLadderMod::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    fType = S->readInt();
    fLoops = S->readInt();
    fGoingUp = S->readBool();
    fEnabled = S->readBool();
    fLadderView.read(S);
}

void plAvLadderMod::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    S->writeInt(fType);
    S->writeInt(fLoops);
    S->writeBool(fGoingUp);
    S->writeBool(fEnabled);
    fLadderView.write(S);
}

void plAvLadderMod::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("LadderParams");
    prc->writeParam("Type", fType);
    prc->writeParam("Loops", fLoops);
    prc->writeParam("GoingUp", fGoingUp);
    prc->writeParam("Enabled", fEnabled);
    prc->endTag(true);

    prc->writeSimpleTag("LadderView");
    fLadderView.prcWrite(prc);
    prc->closeTag();
}

void plAvLadderMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "LadderParams") {
        fType = tag->getParam("Type", "0").to_int();
        fLoops = tag->getParam("Loops", "0").to_int();
        fGoingUp = tag->getParam("GoingUp", "false").to_bool();
        fEnabled = tag->getParam("Enabled", "true").to_bool();
    } else if (tag->getName() == "LadderView") {
        if (tag->hasChildren())
            fLadderView.prcParse(tag->getFirstChild());
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}


/* plLadderModifier */
void plLadderModifier::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    fTopLogic = mgr->readKey(S);
    fBottomLogic = mgr->readKey(S);
    fMainLogic = mgr->readKey(S);

    fExitTop = mgr->readKey(S);
    fExitBottom = mgr->readKey(S);
    fTopPos = mgr->readKey(S);
    fBottomPos = mgr->readKey(S);
}

void plLadderModifier::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    mgr->writeKey(S, fTopLogic);
    mgr->writeKey(S, fBottomLogic);
    mgr->writeKey(S, fMainLogic);

    mgr->writeKey(S, fExitTop);
    mgr->writeKey(S, fExitBottom);
    mgr->writeKey(S, fTopPos);
    mgr->writeKey(S, fBottomPos);
}

void plLadderModifier::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->writeSimpleTag("TopLogic");
    plResManager::PrcWriteKey(prc, fTopLogic);
    prc->closeTag();

    prc->writeSimpleTag("BottomLogic");
    plResManager::PrcWriteKey(prc, fBottomLogic);
    prc->closeTag();

    prc->writeSimpleTag("MainLogic");
    plResManager::PrcWriteKey(prc, fMainLogic);
    prc->closeTag();

    prc->writeSimpleTag("ExitTop");
    plResManager::PrcWriteKey(prc, fExitTop);
    prc->closeTag();

    prc->writeSimpleTag("ExitBottom");
    plResManager::PrcWriteKey(prc, fExitBottom);
    prc->closeTag();

    prc->writeSimpleTag("TopPos");
    plResManager::PrcWriteKey(prc, fTopPos);
    prc->closeTag();

    prc->writeSimpleTag("BottomPos");
    plResManager::PrcWriteKey(prc, fBottomPos);
    prc->closeTag();
}

void plLadderModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "TopLogic") {
        if (tag->hasChildren())
            fTopLogic = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "BottomLogic") {
        if (tag->hasChildren())
            fBottomLogic = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "MainLogic") {
        if (tag->hasChildren())
            fMainLogic = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "ExitTop") {
        if (tag->hasChildren())
            fExitTop = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "ExitBottom") {
        if (tag->hasChildren())
            fExitBottom = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "TopPos") {
        if (tag->hasChildren())
            fTopPos = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "BottomPos") {
        if (tag->hasChildren())
            fBottomPos = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
