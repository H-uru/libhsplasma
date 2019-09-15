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

#include "plSimpleRegionSensor.h"

/* plSimpleRegionSensor */
plSimpleRegionSensor::~plSimpleRegionSensor()
{
    delete fEnterMsg;
    delete fExitMsg;
}

void plSimpleRegionSensor::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    setEnterMsg(S->readBool() ? mgr->ReadCreatableC<plMessage>(S) : nullptr);
    setExitMsg(S->readBool() ? mgr->ReadCreatableC<plMessage>(S) : nullptr);
}

void plSimpleRegionSensor::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    if (fEnterMsg) {
        S->writeBool(true);
        mgr->WriteCreatable(S, fEnterMsg);
    } else {
        S->writeBool(false);
    }
    if (fExitMsg) {
        S->writeBool(true);
        mgr->WriteCreatable(S, fExitMsg);
    } else {
        S->writeBool(false);
    }
}

void plSimpleRegionSensor::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("EnterMsg");
    if (fEnterMsg) {
        prc->endTag(false);
        fEnterMsg->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    prc->startTag("ExitMsg");
    if (fExitMsg) {
        prc->endTag(false);
        fExitMsg->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
}

void plSimpleRegionSensor::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "EnterMsg") {
        if (tag->getParam("NULL", "false").to_bool())
            setEnterMsg(nullptr);
        else if (tag->hasChildren())
            setEnterMsg(mgr->prcParseCreatableC<plMessage>(tag->getFirstChild()));
    } else if (tag->getName() == "ExitMsg") {
        if (tag->getParam("NULL", "false").to_bool())
            setExitMsg(nullptr);
        else if (tag->hasChildren())
            setExitMsg(mgr->prcParseCreatableC<plMessage>(tag->getFirstChild()));
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}

void plSimpleRegionSensor::setEnterMsg(plMessage* msg)
{
    delete fEnterMsg;
    fEnterMsg = msg;
}

void plSimpleRegionSensor::setExitMsg(plMessage* msg)
{
    delete fExitMsg;
    fExitMsg = msg;
}


/* plSwimDetector */
void plSwimDetector::read(hsStream* S, plResManager* mgr)
{
    plSimpleRegionSensor::read(S, mgr);
    S->readByte();
    S->readFloat();
    S->readFloat();
}

void plSwimDetector::write(hsStream* S, plResManager* mgr)
{
    plSimpleRegionSensor::write(S, mgr);
    S->writeByte(0);
    S->writeFloat(0.0f);
    S->writeFloat(0.0f);
}


/* plAutoWalkRegion */
void plAutoWalkRegion::read(hsStream* S, plResManager* mgr)
{
    plSimpleRegionSensor::read(S, mgr);
    fUnknown = S->readInt();
}

void plAutoWalkRegion::write(hsStream* S, plResManager* mgr)
{
    plSimpleRegionSensor::write(S, mgr);
    S->writeInt(fUnknown);
}

void plAutoWalkRegion::IPrcWrite(pfPrcHelper* prc)
{
    plSimpleRegionSensor::IPrcWrite(prc);

    prc->startTag("AutoWalkParams");
    prc->writeParam("Unknown", fUnknown);
    prc->endTag(true);
}

void plAutoWalkRegion::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "AutoWalkParams") {
        fUnknown = tag->getParam("Unknown", "0").to_uint();
    } else {
        plSimpleRegionSensor::IPrcParse(tag, mgr);
    }
}
