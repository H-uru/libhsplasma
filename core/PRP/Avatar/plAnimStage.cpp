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

#include "plAnimStage.h"

void plAnimStage::read(hsStream* S, plResManager* )
{
    fAnimName = S->readSafeStr();
    fNotify = S->readByte();
    fForwardType = (PlayType)S->readInt();
    fBackType = (PlayType)S->readInt();
    fAdvanceType = (AdvanceType)S->readInt();
    fRegressType = (AdvanceType)S->readInt();
    fLoops = S->readInt();
    fDoAdvanceTo = S->readBool();
    fAdvanceTo = S->readInt();
    fDoRegressTo = S->readBool();
    fRegressTo = S->readInt();
}

void plAnimStage::write(hsStream* S, plResManager* )
{
    S->writeSafeStr(fAnimName);
    S->writeByte(fNotify);
    S->writeInt((uint32_t)fForwardType);
    S->writeInt((uint32_t)fBackType);
    S->writeInt((uint32_t)fAdvanceType);
    S->writeInt((uint32_t)fRegressType);
    S->writeInt(fLoops);
    S->writeBool(fDoAdvanceTo);
    S->writeInt(fAdvanceTo);
    S->writeBool(fDoRegressTo);
    S->writeInt(fRegressTo);
}

void plAnimStage::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("Animation");
    prc->writeParam("Name", fAnimName);
    prc->writeParam("Loops", fLoops);
    prc->endTag(true);

    prc->startTag("StageTypes");
    prc->writeParam("Notify", fNotify);
    prc->writeParam("ForwardType", fForwardType);
    prc->writeParam("BackwardType", fBackType);
    prc->writeParam("AdvanceType", fAdvanceType);
    prc->writeParam("RegressType", fRegressType);
    prc->endTag(true);

    prc->startTag("AdvanceTo");
    prc->writeParam("enabled", fDoAdvanceTo);
    prc->writeParam("value", fAdvanceTo);
    prc->endTag(true);

    prc->startTag("RegressTo");
    prc->writeParam("enabled", fDoRegressTo);
    prc->writeParam("value", fRegressTo);
    prc->endTag(true);
}

void plAnimStage::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Animation") {
        fAnimName = tag->getParam("Name", "");
        fLoops = tag->getParam("Loops", "0").to_int();
    } else if (tag->getName() == "StageTypes") {
        fNotify = tag->getParam("Notify", "0").to_uint();
        fForwardType = (PlayType)tag->getParam("ForwardType", "0").to_int();
        fBackType = (PlayType)tag->getParam("BackwardType", "0").to_int();
        fAdvanceType = (AdvanceType)tag->getParam("AdvanceType", "0").to_int();
        fRegressType = (AdvanceType)tag->getParam("RegressType", "0").to_int();
    } else if (tag->getName() == "AdvanceTo") {
        fDoAdvanceTo = tag->getParam("enabled", "true").to_bool();
        fAdvanceTo = tag->getParam("value", "0").to_uint();
    } else if (tag->getName() == "RegressTo") {
        fDoRegressTo = tag->getParam("enabled", "true").to_bool();
        fRegressTo = tag->getParam("value", "0").to_uint();
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plAnimStage::readAux(hsStream* S)
{
    fLocalTime = S->readFloat();
    fLength = S->readFloat();
    fCurLoop = S->readInt();
    fAttached = S->readBool();
}

void plAnimStage::writeAux(hsStream* S)
{
    S->writeFloat(fLocalTime);
    S->writeFloat(fLength);
    S->writeInt(fCurLoop);
    S->writeBool(fAttached);
}

void plAnimStage::prcWriteAux(pfPrcHelper* prc)
{
    prc->startTag("plAnimStage_Aux");
    prc->writeParam("LocalTime", fLocalTime);
    prc->writeParam("Length", fLength);
    prc->writeParam("CurLoop", fCurLoop);
    prc->writeParam("Attached", fAttached);
    prc->endTag(true);
}

void plAnimStage::prcParseAux(const pfPrcTag* tag)
{
    if (tag->getName() != "plAnimStage_Aux")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fLocalTime = tag->getParam("LocalTime", "0").to_float();
    fLength = tag->getParam("Length", "0").to_float();
    fCurLoop = tag->getParam("CurLoop", "0").to_int();
    fAttached = tag->getParam("Attached", "False").to_bool();
}
