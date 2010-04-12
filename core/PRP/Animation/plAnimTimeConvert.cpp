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
plAnimTimeConvert::plAnimTimeConvert()
                 : fFlags(0), fBegin(0.0f), fEnd(0.0f), fLoopBegin(0.0f),
                   fLoopEnd(0.0f), fSpeed(1.0f), fCurrentAnimTime(0.0f),
                   fLastEvalWorldTime(0.0), fEaseInCurve(NULL),
                   fEaseOutCurve(NULL), fSpeedEaseCurve(NULL) { }

plAnimTimeConvert::~plAnimTimeConvert() {
    delete fEaseInCurve;
    delete fEaseOutCurve;
    delete fSpeedEaseCurve;

    for (size_t i=0; i<fCallbackMsgs.getSize(); i++)
        delete fCallbackMsgs[i];
}

void plAnimTimeConvert::read(hsStream* S, plResManager* mgr) {
    fFlags = S->readInt();
    fBegin = S->readFloat();
    fEnd = S->readFloat();
    fLoopEnd = S->readFloat();
    fLoopBegin = S->readFloat();
    fSpeed = S->readFloat();

    setEaseInCurve(plATCEaseCurve::Convert(mgr->ReadCreatable(S)));
    setEaseOutCurve(plATCEaseCurve::Convert(mgr->ReadCreatable(S)));
    setSpeedEaseCurve(plATCEaseCurve::Convert(mgr->ReadCreatable(S)));
    fCurrentAnimTime = S->readFloat();
    fLastEvalWorldTime = S->readDouble();

    for (size_t i=0; i<fCallbackMsgs.getSize(); i++)
        delete fCallbackMsgs[i];
    fCallbackMsgs.setSizeNull(S->readInt());
    for (size_t i=0; i<fCallbackMsgs.getSize(); i++)
        fCallbackMsgs[i] = plEventCallbackMsg::Convert(mgr->ReadCreatable(S));

    fStopPoints.setSizeNull(S->readInt());
    for (size_t i=0; i<fStopPoints.getSize(); i++)
        fStopPoints[i] = S->readFloat();
}

void plAnimTimeConvert::write(hsStream* S, plResManager* mgr) {
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

    S->writeInt(fCallbackMsgs.getSize());
    for (size_t i=0; i<fCallbackMsgs.getSize(); i++)
        mgr->WriteCreatable(S, fCallbackMsgs[i]);

    S->writeInt(fStopPoints.getSize());
    for (size_t i=0; i<fStopPoints.getSize(); i++)
        S->writeFloat(fStopPoints[i]);
}

void plAnimTimeConvert::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Params");
    prc->writeParamHex("Flags", fFlags);
    prc->writeParam("Begin", fBegin);
    prc->writeParam("End", fEnd);
    prc->writeParam("LoopBegin", fLoopBegin);
    prc->writeParam("LoopEnd", fLoopEnd);
    prc->writeParam("Speed", fSpeed);
    prc->endTag(true);

    if (fEaseInCurve != NULL) {
        prc->writeSimpleTag("EaseInCurve");
        fEaseInCurve->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("EaseInCurve");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    if (fEaseOutCurve != NULL) {
        prc->writeSimpleTag("EaseOutCurve");
        fEaseOutCurve->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("EaseOutCurve");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    if (fSpeedEaseCurve != NULL) {
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
    for (size_t i=0; i<fCallbackMsgs.getSize(); i++)
        fCallbackMsgs[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("StopPoints");
    for (size_t i=0; i<fStopPoints.getSize(); i++) {
        prc->startTag("StopPoint");
        prc->writeParam("value", fStopPoints[i]);
        prc->endTag(true);
    }
    prc->closeTag();
}

void plAnimTimeConvert::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Params") {
        fFlags = tag->getParam("Flags", "0").toUint();
        fBegin = tag->getParam("Begin", "0").toFloat();
        fEnd = tag->getParam("End", "0").toFloat();
        fLoopBegin = tag->getParam("LoopBegin", "0").toFloat();
        fLoopEnd = tag->getParam("LoopEnd", "0").toFloat();
        fSpeed = tag->getParam("Speed", "0").toFloat();
    } else if (tag->getName() == "EaseInCurve") {
        if (!tag->getParam("NULL", "false").toBool() && tag->hasChildren())
            setSpeedEaseCurve(plATCEaseCurve::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "EaseOutCurve") {
        if (!tag->getParam("NULL", "false").toBool() && tag->hasChildren())
            setSpeedEaseCurve(plATCEaseCurve::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "SpeedEaseCurve") {
        if (!tag->getParam("NULL", "false").toBool() && tag->hasChildren())
            setSpeedEaseCurve(plATCEaseCurve::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "Times") {
        fCurrentAnimTime = tag->getParam("CurrentAnimTime", "0").toFloat();
        fLastEvalWorldTime = tag->getParam("LastEvalWorldTime", "0").toFloat();
    } else if (tag->getName() == "Callbacks") {
        for (size_t i=0; i<fCallbackMsgs.getSize(); i++)
            delete fCallbackMsgs[i];
        fCallbackMsgs.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fCallbackMsgs.getSize(); i++) {
            fCallbackMsgs[i] = plEventCallbackMsg::Convert(mgr->prcParseCreatable(child));
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "StopPoints") {
        fStopPoints.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fStopPoints.getSize(); i++) {
            if (child->getName() != "StopPoint")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fStopPoints[i] = child->getParam("value", "0").toFloat();
            child = child->getNextSibling();
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plAnimTimeConvert::setEaseInCurve(plATCEaseCurve* curve) {
    delete fEaseInCurve;
    fEaseInCurve = curve;
}

void plAnimTimeConvert::setEaseOutCurve(plATCEaseCurve* curve) {
    delete fEaseOutCurve;
    fEaseOutCurve = curve;
}

void plAnimTimeConvert::setSpeedEaseCurve(plATCEaseCurve* curve) {
    delete fSpeedEaseCurve;
    fSpeedEaseCurve = curve;
}

void plAnimTimeConvert::delCallback(size_t idx) {
    delete fCallbackMsgs[idx];
    fCallbackMsgs.remove(idx);
}

void plAnimTimeConvert::clearCallbacks() {
    for (size_t i=0; i<fCallbackMsgs.getSize(); i++)
        delete fCallbackMsgs[i];
    fCallbackMsgs.clear();
}
