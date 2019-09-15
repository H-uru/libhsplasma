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

#include "plAvTask.h"

/* plAvAnimTask */
void plAvAnimTask::read(hsStream* S, plResManager* /*mgr*/)
{
    fAnimName = S->readSafeStr();
    fInitialBlend = S->readFloat();
    fTargetBlend = S->readFloat();
    fFadeSpeed = S->readFloat();
    fSetTime = S->readFloat();
    fStart = S->readBool();
    fLoop = S->readBool();
    fAttach = S->readBool();
}

void plAvAnimTask::write(hsStream* S, plResManager* /*mgr*/)
{
    S->writeSafeStr(fAnimName);
    S->writeFloat(fInitialBlend);
    S->writeFloat(fTargetBlend);
    S->writeFloat(fFadeSpeed);
    S->writeFloat(fSetTime);
    S->writeBool(fStart);
    S->writeBool(fLoop);
    S->writeBool(fAttach);
}

void plAvAnimTask::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("AnimTaskParams");
    prc->writeParam("AnimName", fAnimName);
    prc->writeParam("InitialBlend", fInitialBlend);
    prc->writeParam("TargetBlend", fTargetBlend);
    prc->writeParam("FadeSpeed", fFadeSpeed);
    prc->writeParam("SetTime", fSetTime);
    prc->writeParam("Start", fStart);
    prc->writeParam("Loop", fLoop);
    prc->writeParam("Attach", fAttach);
    prc->endTag(true);
}

void plAvAnimTask::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "AnimTaskParams") {
        fAnimName = tag->getParam("AnimName", "");
        fInitialBlend = tag->getParam("InitialBlend", "0").to_float();
        fTargetBlend = tag->getParam("TargetBlend", "0").to_float();
        fFadeSpeed = tag->getParam("FadeSpeed", "0").to_float();
        fSetTime = tag->getParam("SetTime", "0").to_float();
        fStart = tag->getParam("Start", "false").to_bool();
        fLoop = tag->getParam("Loop", "false").to_bool();
        fAttach = tag->getParam("Attach", "false").to_bool();
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}


/* plAvOneShotLinkTask */
void plAvOneShotLinkTask::read(hsStream* S, plResManager* /*mgr*/)
{
    fAnimName = S->readSafeStr();
    fMarkerName = S->readSafeStr();
}

void plAvOneShotLinkTask::write(hsStream* S, plResManager* /*mgr*/)
{
    S->writeSafeStr(fAnimName);
    S->writeSafeStr(fMarkerName);
}

void plAvOneShotLinkTask::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("OneShotLinkParams");
    prc->writeParam("AnimName", fAnimName);
    prc->writeParam("MarkerName", fMarkerName);
    prc->endTag(true);
}

void plAvOneShotLinkTask::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "OneShotLinkParams") {
        fAnimName = tag->getParam("AnimName", "");
        fMarkerName = tag->getParam("MarkerName", "");
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}


/* plAvTaskBrain */
plAvTaskBrain::~plAvTaskBrain()
{
    delete fBrain;
}

void plAvTaskBrain::read(hsStream* S, plResManager* mgr)
{
    setBrain(mgr->ReadCreatableC<plArmatureBrain>(S));
}

void plAvTaskBrain::write(hsStream* S, plResManager* mgr)
{
    mgr->WriteCreatable(S, fBrain);
}

void plAvTaskBrain::IPrcWrite(pfPrcHelper* prc)
{
    if (fBrain) {
        prc->writeSimpleTag("Brain");
        fBrain->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("Brain");
        prc->writeParam("NULL", true);
        prc->closeTag();
    }
}

void plAvTaskBrain::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Brain") {
        if (tag->getParam("NULL", "false").to_bool())
            setBrain(nullptr);
        else if (tag->hasChildren())
            setBrain(mgr->prcParseCreatableC<plArmatureBrain>(tag->getFirstChild()));
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plAvTaskBrain::setBrain(plArmatureBrain* brain)
{
    delete fBrain;
    fBrain = brain;
}
