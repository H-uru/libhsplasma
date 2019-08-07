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

#include "plAnimTimeConvert.h"

/* plAnimTimeConvert */
plAnimTimeConvert::~plAnimTimeConvert()
{
    delete fEaseInCurve;
    delete fEaseOutCurve;
    delete fSpeedEaseCurve;

    for (auto msg = fCallbackMsgs.begin(); msg != fCallbackMsgs.end(); ++msg)
        delete *msg;
}

void plAnimTimeConvert::read(hsStream* S, plResManager* mgr)
{
    fFlags = S->readInt();
    fBegin = S->readFloat();
    fEnd = S->readFloat();
    fLoopEnd = S->readFloat();
    fLoopBegin = S->readFloat();
    fSpeed = S->readFloat();

    setEaseInCurve(mgr->ReadCreatableC<plATCEaseCurve>(S));
    setEaseOutCurve(mgr->ReadCreatableC<plATCEaseCurve>(S));
    setSpeedEaseCurve(mgr->ReadCreatableC<plATCEaseCurve>(S));
    fCurrentAnimTime = S->readFloat();
    fLastEvalWorldTime = S->readDouble();

    for (auto msg = fCallbackMsgs.begin(); msg != fCallbackMsgs.end(); ++msg)
        delete *msg;
    fCallbackMsgs.resize(S->readInt());
    for (size_t i=0; i<fCallbackMsgs.size(); i++)
        fCallbackMsgs[i] = mgr->ReadCreatableC<plEventCallbackMsg>(S);

    fStopPoints.resize(S->readInt());
    for (size_t i=0; i<fStopPoints.size(); i++)
        fStopPoints[i] = S->readFloat();
}

void plAnimTimeConvert::write(hsStream* S, plResManager* mgr)
{
    S->writeInt(fFlags);
    S->writeFloat(fBegin);
    S->writeFloat(fEnd);
    S->writeFloat(fLoopEnd);
    S->writeFloat(fLoopBegin);
    S->writeFloat(fSpeed);

    mgr->WriteCreatable(S, fEaseInCurve);
    mgr->WriteCreatable(S, fEaseOutCurve);
    mgr->WriteCreatable(S, fSpeedEaseCurve);
    S->writeFloat(fCurrentAnimTime);
    S->writeDouble(fLastEvalWorldTime);

    S->writeInt(fCallbackMsgs.size());
    for (size_t i=0; i<fCallbackMsgs.size(); i++)
        mgr->WriteCreatable(S, fCallbackMsgs[i]);

    S->writeInt(fStopPoints.size());
    for (size_t i=0; i<fStopPoints.size(); i++)
        S->writeFloat(fStopPoints[i]);
}

void plAnimTimeConvert::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("Params");
    prc->writeParamHex("Flags", fFlags);
    prc->writeParam("Begin", fBegin);
    prc->writeParam("End", fEnd);
    prc->writeParam("LoopBegin", fLoopBegin);
    prc->writeParam("LoopEnd", fLoopEnd);
    prc->writeParam("Speed", fSpeed);
    prc->endTag(true);

    if (fEaseInCurve) {
        prc->writeSimpleTag("EaseInCurve");
        fEaseInCurve->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("EaseInCurve");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    if (fEaseOutCurve) {
        prc->writeSimpleTag("EaseOutCurve");
        fEaseOutCurve->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("EaseOutCurve");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    if (fSpeedEaseCurve) {
        prc->writeSimpleTag("SpeedEaseCurve");
        fSpeedEaseCurve->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("SpeedEaseCurve");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }

    prc->startTag("Times");
    prc->writeParam("CurrentAnimTime", fCurrentAnimTime);
    prc->writeParam("LastEvalWorldTime", fLastEvalWorldTime);
    prc->endTag(true);

    prc->writeSimpleTag("Callbacks");
    for (size_t i=0; i<fCallbackMsgs.size(); i++)
        fCallbackMsgs[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("StopPoints");
    for (size_t i=0; i<fStopPoints.size(); i++) {
        prc->startTag("StopPoint");
        prc->writeParam("value", fStopPoints[i]);
        prc->endTag(true);
    }
    prc->closeTag();
}

void plAnimTimeConvert::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Params") {
        fFlags = tag->getParam("Flags", "0").to_uint();
        fBegin = tag->getParam("Begin", "0").to_float();
        fEnd = tag->getParam("End", "0").to_float();
        fLoopBegin = tag->getParam("LoopBegin", "0").to_float();
        fLoopEnd = tag->getParam("LoopEnd", "0").to_float();
        fSpeed = tag->getParam("Speed", "0").to_float();
    } else if (tag->getName() == "EaseInCurve") {
        if (!tag->getParam("NULL", "false").to_bool() && tag->hasChildren())
            setSpeedEaseCurve(mgr->prcParseCreatableC<plATCEaseCurve>(tag->getFirstChild()));
    } else if (tag->getName() == "EaseOutCurve") {
        if (!tag->getParam("NULL", "false").to_bool() && tag->hasChildren())
            setSpeedEaseCurve(mgr->prcParseCreatableC<plATCEaseCurve>(tag->getFirstChild()));
    } else if (tag->getName() == "SpeedEaseCurve") {
        if (!tag->getParam("NULL", "false").to_bool() && tag->hasChildren())
            setSpeedEaseCurve(mgr->prcParseCreatableC<plATCEaseCurve>(tag->getFirstChild()));
    } else if (tag->getName() == "Times") {
        fCurrentAnimTime = tag->getParam("CurrentAnimTime", "0").to_float();
        fLastEvalWorldTime = tag->getParam("LastEvalWorldTime", "0").to_float();
    } else if (tag->getName() == "Callbacks") {
        for (auto msg = fCallbackMsgs.begin(); msg != fCallbackMsgs.end(); ++msg)
            delete *msg;
        fCallbackMsgs.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fCallbackMsgs.size(); i++) {
            fCallbackMsgs[i] = mgr->prcParseCreatableC<plEventCallbackMsg>(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "StopPoints") {
        fStopPoints.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fStopPoints.size(); i++) {
            if (child->getName() != "StopPoint")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fStopPoints[i] = child->getParam("value", "0").to_float();
            child = child->getNextSibling();
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plAnimTimeConvert::setEaseInCurve(plATCEaseCurve* curve)
{
    delete fEaseInCurve;
    fEaseInCurve = curve;
}

void plAnimTimeConvert::setEaseOutCurve(plATCEaseCurve* curve)
{
    delete fEaseOutCurve;
    fEaseOutCurve = curve;
}

void plAnimTimeConvert::setSpeedEaseCurve(plATCEaseCurve* curve)
{
    delete fSpeedEaseCurve;
    fSpeedEaseCurve = curve;
}

void plAnimTimeConvert::delCallback(size_t idx)
{
    delete fCallbackMsgs[idx];
    fCallbackMsgs.erase(fCallbackMsgs.begin() + idx);
}

void plAnimTimeConvert::clearCallbacks()
{
    for (auto msg = fCallbackMsgs.begin(); msg != fCallbackMsgs.end(); ++msg)
        delete *msg;
    fCallbackMsgs.clear();
}
